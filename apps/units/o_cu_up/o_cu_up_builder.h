/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "apps/services/metrics/metrics_config.h"
#include "o_cu_up_unit_impl.h"
#include "srsran/support/timers.h"
#include <memory>

namespace srsran {
namespace app_services {
class metrics_notifier;
}

namespace srs_cu_up {
class e1_connection_client;
}

struct o_cu_up_unit_config;
class dlt_pcap;
class f1u_cu_up_gateway;
class io_broker;
struct worker_manager;
class e2_connection_client;

/// O-RAN CU-UP unit dependencies.
struct o_cu_up_unit_dependencies {
  worker_manager*                  workers;
  task_executor*                   cu_up_e2_exec    = nullptr;
  e2_connection_client*            e2_gw            = nullptr;
  app_services::metrics_notifier*  metrics_notifier = nullptr;
  srs_cu_up::e1_connection_client* e1ap_conn_client = nullptr;
  f1u_cu_up_gateway*               f1u_gateway      = nullptr;
  dlt_pcap*                        gtpu_pcap        = nullptr;
  timer_manager*                   timers           = nullptr;
  io_broker*                       io_brk           = nullptr;
};

/// O-RAN CU-CP unit.
struct o_cu_up_unit {
  std::unique_ptr<srs_cu_up::o_cu_up>       unit;
  std::vector<app_services::metrics_config> metrics;
};

/// Builds the O-RAN CU-UP unit using the given arguments.
o_cu_up_unit build_o_cu_up(const o_cu_up_unit_config& unit_cfg, const o_cu_up_unit_dependencies& dependencies);

} // namespace srsran
