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

#include "srsran/ofh/ethernet/dpdk/dpdk_ethernet_port_context.h"
#include "srsran/ofh/ethernet/ethernet_frame_notifier.h"
#include "srsran/ofh/ethernet/ethernet_gateway.h"
#include "srsran/ofh/ethernet/ethernet_gw_config.h"
#include "srsran/ofh/ethernet/ethernet_properties.h"
#include "srsran/ofh/ethernet/ethernet_receiver.h"
#include "srsran/srslog/logger.h"
#include "srsran/support/executors/task_executor.h"

namespace srsran {

/// Encapsulates Ethernet transmitter and receiver functionalities used by the RU emulator.
class ru_emulator_transceiver : public ether::gateway, public ether::receiver
{
public:
  /// Default destructor.
  virtual ~ru_emulator_transceiver() = default;
};

/// Ethernet transceiver implementation based on DPDK library.
class dpdk_transceiver : public ru_emulator_transceiver
{
  enum class status { idle, running, stop_requested, stopped };

public:
  dpdk_transceiver(srslog::basic_logger&                     logger_,
                   task_executor&                            executor_,
                   std::shared_ptr<ether::dpdk_port_context> port_ctx_ptr_) :
    logger(logger_), executor(executor_), port_ctx_ptr(port_ctx_ptr_), port_ctx(*port_ctx_ptr)
  {
    srsran_assert(port_ctx_ptr, "Invalid port context");
  }

  // See interface for documentation.
  void start(ether::frame_notifier& notifier_) override;

  // See interface for documentation.
  void stop() override;

  // See interface for documentation.
  void send(span<span<const uint8_t>> frames) override;

protected:
  /// Main receiving loop.
  void receive_loop();

  /// Receives new Ethernet frames from the socket.
  void receive();

private:
  srslog::basic_logger&                     logger;
  task_executor&                            executor;
  std::shared_ptr<ether::dpdk_port_context> port_ctx_ptr;
  ether::dpdk_port_context&                 port_ctx;
  ether::frame_notifier*                    notifier;
  std::atomic<status>                       trx_status{status::idle};
};

/// Ethernet transceiver implementation based on regular UNIX sockets.
class socket_transceiver : public ru_emulator_transceiver
{
public:
  socket_transceiver(srslog::basic_logger& logger_, task_executor& executor_, const ether::gw_config& cfg);

  // See interface for documentation.
  void start(ether::frame_notifier& notifier_) override;

  // See interface for documentation.
  void stop() override;

  // See interface for documentation.
  void send(span<span<const uint8_t>> frames) override;

private:
  std::unique_ptr<ether::gateway>  transmitter;
  std::unique_ptr<ether::receiver> receiver;
};

} // namespace srsran
