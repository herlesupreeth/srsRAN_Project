/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/gateways/udp_network_gateway.h"
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace srsran {

constexpr uint32_t network_gateway_udp_max_len = 9100;

class udp_network_gateway_impl final : public udp_network_gateway
{
public:
  explicit udp_network_gateway_impl(udp_network_gateway_config config_, network_gateway_data_notifier& data_notifier_);
  ~udp_network_gateway_impl() override { close_socket(); }

private:
  bool is_initialized();
  bool set_sockopts();

  // udp_network_gateway_data_handler interface
  void handle_pdu(const byte_buffer& pdu, const ::sockaddr* dest_addr, ::socklen_t dest_len) override;

  // udp_network_gateway_controller interface
  bool create_and_bind() override;
  void receive() override;
  int  get_socket_fd() override;
  bool get_bind_port(uint16_t& port) override;
  bool get_bind_address(std::string& ip_address) override;

  // socket helpers
  bool set_non_blocking();
  bool set_receive_timeout(unsigned rx_timeout_sec);
  bool set_reuse_addr();
  bool close_socket();

  udp_network_gateway_config     config; // configuration
  network_gateway_data_notifier& data_notifier;
  srslog::basic_logger&          logger;

  int sock_fd = -1;

  sockaddr_storage local_addr        = {}; // the local address
  socklen_t        local_addrlen     = 0;
  int              local_ai_family   = 0;
  int              local_ai_socktype = 0;
  int              local_ai_protocol = 0;
};

} // namespace srsran
