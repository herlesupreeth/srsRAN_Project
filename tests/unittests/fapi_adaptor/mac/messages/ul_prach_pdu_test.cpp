/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "helpers.h"
#include "srsran/fapi_adaptor/mac/messages/prach.h"
#include <gtest/gtest.h>

using namespace srsran;
using namespace fapi_adaptor;
using namespace unittests;

TEST(mac_fapi_ul_prach_pdu_conversor_test, valid_prach_pdu_should_pass)
{
  const prach_occasion_info& mac_pdu = build_valid_prach_occassion();
  fapi::ul_prach_pdu         fapi_pdu;

  convert_prach_mac_to_fapi(fapi_pdu, mac_pdu);

  ASSERT_EQ(static_cast<unsigned>(prach_format_type::one), static_cast<unsigned>(fapi_pdu.prach_format));
  ASSERT_EQ(is_long_preamble(mac_pdu.format) ? 1 : mac_pdu.nof_prach_occasions, fapi_pdu.num_prach_ocas);
  ASSERT_EQ(mac_pdu.index_fd_ra, fapi_pdu.index_fd_ra);
  ASSERT_EQ(mac_pdu.pci, fapi_pdu.phys_cell_id);
  ASSERT_EQ(mac_pdu.nof_fd_ra, fapi_pdu.maintenance_v3.num_fd_ra);
  ASSERT_EQ(mac_pdu.start_symbol, fapi_pdu.prach_start_symbol);
  ASSERT_EQ(mac_pdu.nof_cs, fapi_pdu.num_cs);
  ASSERT_EQ(0, fapi_pdu.maintenance_v3.prach_res_config_index);
  ASSERT_EQ(mac_pdu.start_preamble_index, fapi_pdu.maintenance_v3.start_preamble_index);
  ASSERT_EQ(mac_pdu.nof_preamble_indexes, fapi_pdu.maintenance_v3.num_preamble_indices);
  ASSERT_EQ(static_cast<unsigned>(fapi::prach_config_scope_type::phy_context),
            static_cast<unsigned>(fapi_pdu.maintenance_v3.prach_config_scope));
}
