/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "apps/cu/cu_appconfig_cli11_schema.h"
#include "apps/services/application_message_banners.h"
#include "apps/services/application_tracer.h"
#include "apps/services/buffer_pool/buffer_pool_manager.h"
#include "apps/services/metrics/metrics_manager.h"
#include "apps/services/metrics/metrics_notifier_proxy.h"
#include "apps/services/stdin_command_dispatcher.h"
#include "apps/services/worker_manager/worker_manager.h"
#include "apps/services/worker_manager/worker_manager_config.h"
#include "apps/units/o_cu_cp/o_cu_cp_application_unit.h"
#include "apps/units/o_cu_cp/o_cu_cp_unit_config.h"
#include "apps/units/o_cu_cp/pcap_factory.h"
#include "apps/units/o_cu_up/o_cu_up_application_unit.h"
#include "apps/units/o_cu_up/o_cu_up_unit_config.h"
#include "apps/units/o_cu_up/pcap_factory.h"
#include "cu_appconfig.h"
#include "cu_appconfig_validator.h"
#include "cu_appconfig_yaml_writer.h"
#include "srsran/cu_cp/cu_cp_operation_controller.h"
#include "srsran/e1ap/gateways/e1_local_connector_factory.h"
#include "srsran/e2/e2ap_config_translators.h"
#include "srsran/f1ap/gateways/f1c_network_server_factory.h"
#include "srsran/f1u/cu_up/f1u_session_manager_factory.h"
#include "srsran/f1u/cu_up/split_connector/f1u_split_connector_factory.h"
#include "srsran/gateways/udp_network_gateway.h"
#include "srsran/gtpu/gtpu_config.h"
#include "srsran/gtpu/gtpu_demux_factory.h"
#include "srsran/gtpu/gtpu_gateway.h"
#include "srsran/support/backtrace.h"
#include "srsran/support/config_parsers.h"
#include "srsran/support/cpu_features.h"
#include "srsran/support/error_handling.h"
#include "srsran/support/io/io_broker.h"
#include "srsran/support/io/io_broker_factory.h"
#include "srsran/support/io/io_timer_source.h"
#include "srsran/support/signal_handling.h"
#include "srsran/support/signal_observer.h"
#include "srsran/support/sysinfo.h"
#include "srsran/support/timers.h"
#include "srsran/support/tracing/event_tracing.h"
#include "srsran/support/versioning/build_info.h"
#include "srsran/support/versioning/version.h"
#include <atomic>
#include <thread>

using namespace srsran;

/// \file
/// \brief Application of a Central Unit (CU) with combined CU control-plane (CU-CP) and CU user-plane (CU-UP).
///
/// This application runs a CU without the E1 connection between the CU-CP and CU-UP going over a real SCTP
/// connection. However, its does expose the F1, N2 and N3 interface to the DU, AMF and UPF over the standard
/// UDP/SCTP ports.
///
/// The app serves as an example for an all-integrated CU.

static std::string config_file;

/// Flag that indicates if the application is running or being shutdown.
static std::atomic<bool> is_app_running = {true};
/// Maximum number of configuration files allowed to be concatenated in the command line.
static constexpr unsigned MAX_CONFIG_FILES = 10;

static void populate_cli11_generic_args(CLI::App& app)
{
  fmt::memory_buffer buffer;
  format_to(std::back_inserter(buffer), "srsRAN 5G CU version {} ({})", get_version(), get_build_hash());
  app.set_version_flag("-v,--version", srsran::to_c_str(buffer));
  app.set_config("-c,", config_file, "Read config from file", false)->expected(1, MAX_CONFIG_FILES);
}

/// Function to call when the application is interrupted.
static void interrupt_signal_handler(int signal)
{
  is_app_running = false;
}

static signal_dispatcher cleanup_signal_dispatcher;

/// Function to call when the application is going to be forcefully shutdown.
static void cleanup_signal_handler(int signal)
{
  cleanup_signal_dispatcher.notify_signal(signal);
  srslog::flush();
}

/// Function to call when an error is reported by the application.
static void app_error_report_handler()
{
  srslog::flush();
}

static void initialize_log(const std::string& filename)
{
  srslog::sink* log_sink = (filename == "stdout") ? srslog::create_stdout_sink() : srslog::create_file_sink(filename);
  if (log_sink == nullptr) {
    report_error("Could not create application main log sink.\n");
  }
  srslog::set_default_sink(*log_sink);
  srslog::init();
}

static void register_app_logs(const logger_appconfig&   log_cfg,
                              o_cu_cp_application_unit& cu_cp_app_unit,
                              o_cu_up_application_unit& cu_up_app_unit)
{
  // Set log-level of app and all non-layer specific components to app level.
  for (const auto& id : {"ALL", "SCTP-GW", "IO-EPOLL", "UDP-GW", "PCAP"}) {
    auto& logger = srslog::fetch_basic_logger(id, false);
    logger.set_level(log_cfg.lib_level);
    logger.set_hex_dump_max_size(log_cfg.hex_max_size);
  }

  auto& app_logger = srslog::fetch_basic_logger("CU", false);
  app_logger.set_level(srslog::basic_levels::info);
  app_services::application_message_banners::log_build_info(app_logger);
  app_logger.set_level(log_cfg.config_level);
  app_logger.set_hex_dump_max_size(log_cfg.hex_max_size);

  auto& config_logger = srslog::fetch_basic_logger("CONFIG", false);
  config_logger.set_level(log_cfg.config_level);
  config_logger.set_hex_dump_max_size(log_cfg.hex_max_size);

  auto& metrics_logger = srslog::fetch_basic_logger("METRICS", false);
  metrics_logger.set_level(log_cfg.metrics_level.level);
  metrics_logger.set_hex_dump_max_size(log_cfg.metrics_level.hex_max_size);

  // Register units logs.
  cu_cp_app_unit.on_loggers_registration();
  cu_up_app_unit.on_loggers_registration();
}

static void fill_cu_worker_manager_config(worker_manager_config& config, const cu_appconfig& unit_cfg)
{
  config.nof_low_prio_threads     = unit_cfg.expert_execution_cfg.threads.non_rt_threads.nof_non_rt_threads;
  config.low_prio_task_queue_size = unit_cfg.expert_execution_cfg.threads.non_rt_threads.non_rt_task_queue_size;
  config.low_prio_sched_config    = unit_cfg.expert_execution_cfg.affinities.low_priority_cpu_cfg;
}

static void autoderive_cu_up_parameters_after_parsing(cu_appconfig&            cu_config,
                                                      o_cu_up_unit_config&     o_cu_up_cfg,
                                                      const cu_cp_unit_config& cu_cp_cfg)
{
  // If no UPF is configured, we set the UPF configuration from the CU-CP AMF configuration.
  if (o_cu_up_cfg.cu_up_cfg.ngu_cfg.ngu_socket_cfg.empty()) {
    cu_up_unit_ngu_socket_config sock_cfg;
    sock_cfg.bind_addr = cu_cp_cfg.amf_config.amf.bind_addr;
    o_cu_up_cfg.cu_up_cfg.ngu_cfg.ngu_socket_cfg.push_back(sock_cfg);
  }
  // If no F1-U socket configuration is derived, we set a default configuration.
  if (cu_config.f1u_cfg.f1u_socket_cfg.empty()) {
    srs_cu::cu_f1u_socket_appconfig sock_cfg;
    cu_config.f1u_cfg.f1u_socket_cfg.push_back(sock_cfg);
  }
}

int main(int argc, char** argv)
{
  // Set the application error handler.
  set_error_handler(app_error_report_handler);

  static constexpr std::string_view app_name = "CU";
  app_services::application_message_banners::announce_app_and_version(app_name);

  // Set interrupt and cleanup signal handlers.
  register_interrupt_signal_handler(interrupt_signal_handler);
  register_cleanup_signal_handler(cleanup_signal_handler);

  // Enable backtrace.
  enable_backtrace();

  // Setup and configure config parsing.
  CLI::App app("srsCU application");
  app.config_formatter(create_yaml_config_parser());
  app.allow_config_extras(CLI::config_extras_mode::error);
  // Fill the generic application arguments to parse.
  populate_cli11_generic_args(app);

  // Configure CLI11 with the CU application configuration schema.
  cu_appconfig cu_cfg;
  configure_cli11_with_cu_appconfig_schema(app, cu_cfg);

  auto o_cu_cp_app_unit = create_o_cu_cp_application_unit("cu");
  o_cu_cp_app_unit->on_parsing_configuration_registration(app);

  auto o_cu_up_app_unit = create_o_cu_up_application_unit("cu");
  o_cu_up_app_unit->on_parsing_configuration_registration(app);

  // Set the callback for the app calling all the autoderivation functions.
  app.callback([&app, &cu_cfg, &o_cu_cp_app_unit, &o_cu_up_app_unit]() {
    o_cu_cp_app_unit->on_configuration_parameters_autoderivation(app);
    o_cu_up_app_unit->on_configuration_parameters_autoderivation(app);

    autoderive_cu_up_parameters_after_parsing(
        cu_cfg, o_cu_up_app_unit->get_o_cu_up_unit_config(), o_cu_cp_app_unit->get_o_cu_cp_unit_config().cucp_cfg);
  });

  // Parse arguments.
  CLI11_PARSE(app, argc, argv);

  // Check the modified configuration.
  if (!validate_cu_appconfig(cu_cfg) ||
      !o_cu_cp_app_unit->on_configuration_validation(os_sched_affinity_bitmask::available_cpus()) ||
      !o_cu_up_app_unit->on_configuration_validation(os_sched_affinity_bitmask::available_cpus())) {
    report_error("Invalid configuration detected.\n");
  }

  // Set up logging.
  initialize_log(cu_cfg.log_cfg.filename);
  register_app_logs(cu_cfg.log_cfg, *o_cu_cp_app_unit, *o_cu_up_app_unit);

  // Log input configuration.
  srslog::basic_logger& config_logger = srslog::fetch_basic_logger("CONFIG");
  if (config_logger.debug.enabled()) {
    YAML::Node node;
    fill_cu_appconfig_in_yaml_schema(node, cu_cfg);
    o_cu_cp_app_unit->dump_config(node);
    o_cu_up_app_unit->dump_config(node);
    config_logger.debug("Input configuration (all values): \n{}", YAML::Dump(node));
  } else {
    config_logger.info("Input configuration (only non-default values): \n{}", app.config_to_str(false, false));
  }

  srslog::basic_logger&            cu_logger = srslog::fetch_basic_logger("CU");
  app_services::application_tracer app_tracer;
  if (not cu_cfg.log_cfg.tracing_filename.empty()) {
    app_tracer.enable_tracer(cu_cfg.log_cfg.tracing_filename, cu_logger);
  }

  // configure cgroups
  // TODO

  // Setup size of byte buffer pool.
  app_services::buffer_pool_manager buffer_pool_service(cu_cfg.buffer_pool_config);

  // Log CPU architecture.
  // TODO

  // Check and log included CPU features and check support by current CPU
  if (cpu_supports_included_features()) {
    cu_logger.debug("Required CPU features: {}", get_cpu_feature_info());
  } else {
    // Quit here until we complete selection of the best matching implementation for the current CPU at runtime.
    cu_logger.error("The CPU does not support the required CPU features that were configured during compile time: {}",
                    get_cpu_feature_info());
    report_error("The CPU does not support the required CPU features that were configured during compile time: {}\n",
                 get_cpu_feature_info());
  }

  // Check some common causes of performance issues and print a warning if required.
  check_cpu_governor(cu_logger);
  check_drm_kms_polling(cu_logger);

  // Create manager of timers for CU-CP and CU-UP, which will be driven by the system timer slot ticks.
  timer_manager  app_timers{256};
  timer_manager* cu_timers = &app_timers;

  // Create worker manager.
  worker_manager_config worker_manager_cfg;
  fill_cu_worker_manager_config(worker_manager_cfg, cu_cfg);
  o_cu_cp_app_unit->fill_worker_manager_config(worker_manager_cfg);
  o_cu_up_app_unit->fill_worker_manager_config(worker_manager_cfg);
  worker_manager_cfg.app_timers = &app_timers;
  worker_manager workers{worker_manager_cfg};

  // Create layer specific PCAPs.
  o_cu_cp_dlt_pcaps cu_cp_dlt_pcaps = create_o_cu_cp_dlt_pcap(
      o_cu_cp_app_unit->get_o_cu_cp_unit_config(), *workers.get_executor_getter(), cleanup_signal_dispatcher);
  o_cu_up_dlt_pcaps cu_up_dlt_pcaps = create_o_cu_up_dlt_pcaps(
      o_cu_up_app_unit->get_o_cu_up_unit_config(), *workers.get_executor_getter(), cleanup_signal_dispatcher);

  // Create IO broker.
  const auto&                low_prio_cpu_mask = cu_cfg.expert_execution_cfg.affinities.low_priority_cpu_cfg.mask;
  io_broker_config           io_broker_cfg(low_prio_cpu_mask);
  std::unique_ptr<io_broker> epoll_broker = create_io_broker(io_broker_type::epoll, io_broker_cfg);

  // Create F1-C GW (TODO cleanup port and PPID args with factory)
  sctp_network_gateway_config f1c_sctp_cfg = {};
  f1c_sctp_cfg.if_name                     = "F1-C";
  f1c_sctp_cfg.bind_address                = cu_cfg.f1ap_cfg.bind_addr;
  f1c_sctp_cfg.bind_port                   = F1AP_PORT;
  f1c_sctp_cfg.ppid                        = F1AP_PPID;
  f1c_cu_sctp_gateway_config f1c_server_cfg(
      {f1c_sctp_cfg, *epoll_broker, *workers.non_rt_hi_prio_exec, *cu_cp_dlt_pcaps.f1ap});
  std::unique_ptr<srs_cu_cp::f1c_connection_server> cu_f1c_gw = srsran::create_f1c_gateway_server(f1c_server_cfg);

  // Create F1-U GW.
  // > Create GTP-U Demux.
  gtpu_demux_creation_request cu_f1u_gtpu_msg   = {};
  cu_f1u_gtpu_msg.cfg.warn_on_drop              = true;
  cu_f1u_gtpu_msg.gtpu_pcap                     = cu_up_dlt_pcaps.f1u.get();
  std::unique_ptr<gtpu_demux> cu_f1u_gtpu_demux = create_gtpu_demux(cu_f1u_gtpu_msg);
  // > Create UDP gateway(s).
  srs_cu_up::gtpu_gateway_maps f1u_gw_maps;
  for (const srs_cu::cu_f1u_socket_appconfig& sock_cfg : cu_cfg.f1u_cfg.f1u_socket_cfg) {
    udp_network_gateway_config cu_f1u_gw_config = {};
    cu_f1u_gw_config.bind_address               = sock_cfg.bind_addr;
    cu_f1u_gw_config.ext_bind_addr              = sock_cfg.udp_config.ext_addr;
    cu_f1u_gw_config.bind_port                  = GTPU_PORT;
    cu_f1u_gw_config.reuse_addr                 = false;
    cu_f1u_gw_config.pool_occupancy_threshold   = sock_cfg.udp_config.pool_threshold;
    cu_f1u_gw_config.rx_max_mmsg                = sock_cfg.udp_config.rx_max_msgs;
    cu_f1u_gw_config.dscp                       = sock_cfg.udp_config.dscp;
    std::unique_ptr<gtpu_gateway> cu_f1u_gw     = create_udp_gtpu_gateway(
        cu_f1u_gw_config, *epoll_broker, workers.cu_up_exec_mapper->io_ul_executor(), *workers.non_rt_low_prio_exec);
    if (not sock_cfg.five_qi.has_value()) {
      f1u_gw_maps.default_gws.push_back(std::move(cu_f1u_gw));
    } else {
      f1u_gw_maps.five_qi_gws[sock_cfg.five_qi.value()].push_back(std::move(cu_f1u_gw));
    }
  }
  std::unique_ptr<f1u_cu_up_udp_gateway> cu_f1u_conn =
      srs_cu_up::create_split_f1u_gw({f1u_gw_maps, *cu_f1u_gtpu_demux, *cu_up_dlt_pcaps.f1u, GTPU_PORT});

  // Create E1AP local connector
  std::unique_ptr<e1_local_connector> e1_gw =
      create_e1_local_connector(e1_local_connector_config{*cu_up_dlt_pcaps.e1ap});

  // Create time source that ticks the timers.
  std::optional<io_timer_source> time_source(
      std::in_place_t{}, app_timers, *epoll_broker, *workers.non_rt_hi_prio_exec, std::chrono::milliseconds{1});

  // Instantiate E2AP client gateway.
  std::unique_ptr<e2_connection_client> e2_gw_cu_cp = create_e2_gateway_client(
      generate_e2_client_gateway_config(o_cu_cp_app_unit->get_o_cu_cp_unit_config().e2_cfg.base_config,
                                        *epoll_broker,
                                        *workers.non_rt_hi_prio_exec,
                                        *cu_cp_dlt_pcaps.e2ap,
                                        E2_CP_PPID));
  std::unique_ptr<e2_connection_client> e2_gw_cu_up = create_e2_gateway_client(
      generate_e2_client_gateway_config(o_cu_up_app_unit->get_o_cu_up_unit_config().e2_cfg.base_config,
                                        *epoll_broker,
                                        *workers.non_rt_hi_prio_exec,
                                        *cu_up_dlt_pcaps.e2ap,
                                        E2_UP_PPID));

  app_services::metrics_notifier_proxy_impl metrics_notifier_forwarder;

  // Create O-CU-CP dependencies.
  o_cu_cp_unit_dependencies o_cucp_deps;
  o_cucp_deps.cu_cp_executor       = workers.cu_cp_exec;
  o_cucp_deps.cu_cp_n2_rx_executor = workers.non_rt_hi_prio_exec;
  o_cucp_deps.cu_cp_e2_exec        = workers.cu_e2_exec;
  o_cucp_deps.timers               = cu_timers;
  o_cucp_deps.ngap_pcap            = cu_cp_dlt_pcaps.ngap.get();
  o_cucp_deps.broker               = epoll_broker.get();
  o_cucp_deps.e2_gw                = e2_gw_cu_cp.get();
  o_cucp_deps.metrics_notifier     = &metrics_notifier_forwarder;

  // Create O-CU-CP.
  auto                o_cucp_unit = o_cu_cp_app_unit->create_o_cu_cp(o_cucp_deps);
  srs_cu_cp::o_cu_cp& o_cucp_obj  = *o_cucp_unit.unit;

  // Create console helper object for commands and metrics printing.
  app_services::stdin_command_dispatcher command_parser(
      *epoll_broker, *workers.non_rt_low_prio_exec, o_cucp_unit.commands);
  std::vector<app_services::metrics_config> metrics_configs = std::move(o_cucp_unit.metrics);

  // Connect E1AP to O-CU-CP.
  e1_gw->attach_cu_cp(o_cucp_obj.get_cu_cp().get_e1_handler());

  // start O-CU-CP
  cu_logger.info("Starting CU-CP...");
  o_cucp_obj.get_operation_controller().start();
  cu_logger.info("CU-CP started successfully");

  // Check connection to AMF
  if (not o_cucp_obj.get_cu_cp().get_ng_handler().amfs_are_connected()) {
    report_error("CU-CP failed to connect to AMF");
  }

  // Connect F1-C to O-CU-CP and start listening for new F1-C connection requests.
  cu_f1c_gw->attach_cu_cp(o_cucp_obj.get_cu_cp().get_f1c_handler());

  // Create and start O-CU-UP
  o_cu_up_unit_dependencies o_cuup_unit_deps;
  o_cuup_unit_deps.workers          = &workers;
  o_cuup_unit_deps.cu_up_e2_exec    = workers.cu_e2_exec;
  o_cuup_unit_deps.e1ap_conn_client = e1_gw.get();
  o_cuup_unit_deps.f1u_gateway      = cu_f1u_conn.get();
  o_cuup_unit_deps.gtpu_pcap        = cu_up_dlt_pcaps.n3.get();
  o_cuup_unit_deps.timers           = cu_timers;
  o_cuup_unit_deps.io_brk           = epoll_broker.get();
  o_cuup_unit_deps.e2_gw            = e2_gw_cu_up.get();
  o_cuup_unit_deps.metrics_notifier = &metrics_notifier_forwarder;

  auto o_cuup_unit = o_cu_up_app_unit->create_o_cu_up_unit(o_cuup_unit_deps);
  for (auto& metric : o_cuup_unit.metrics) {
    metrics_configs.push_back(std::move(metric));
  }
  app_services::metrics_manager metrics_mngr(
      srslog::fetch_basic_logger("CU"), *workers.metrics_hub_exec, metrics_configs);
  // Connect the forwarder to the metrics manager.
  metrics_notifier_forwarder.connect(metrics_mngr);

  o_cuup_unit.unit->get_operation_controller().start();
  {
    app_services::application_message_banners app_banner(app_name);

    while (is_app_running) {
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
  }

  // Stop O-CU-UP activity.
  o_cuup_unit.unit->get_operation_controller().stop();

  // Stop O-CU-CP activity.
  o_cucp_obj.get_operation_controller().stop();

  // Stop the timer source before stopping the workers.
  time_source.reset();

  // Close PCAPs
  cu_logger.info("Closing PCAP files...");
  cu_cp_dlt_pcaps.reset();
  cu_up_dlt_pcaps.reset();
  cu_logger.info("PCAP files successfully closed.");

  // Stop workers
  cu_logger.info("Stopping executors...");
  workers.stop();
  cu_logger.info("Executors closed successfully.");

  srslog::flush();

  return 0;
}
