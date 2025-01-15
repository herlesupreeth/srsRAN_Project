/*
 *
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/f1u/du/f1u_gateway.h"
#include "srsran/gtpu/gtpu_demux.h"
#include "srsran/gtpu/gtpu_gateway.h"
#include "srsran/pcap/dlt_pcap.h"
#include <cstdint>

namespace srsran::srs_du {

struct f1u_du_split_gateway_creation_msg {
  gtpu_gateway* udp_gw;
  gtpu_demux*   demux;
  dlt_pcap&     gtpu_pcap;
  uint16_t      peer_port;
  std::string   f1u_ext_addr = "auto";
};

std::unique_ptr<f1u_du_udp_gateway> create_split_f1u_gw(f1u_du_split_gateway_creation_msg msg);

} // namespace srsran::srs_du
