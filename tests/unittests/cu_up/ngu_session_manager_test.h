/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "cu_up_test_helpers.h"
#include <gtest/gtest.h>

namespace srsran::srs_cu_up {

/// Fixture base class for PDU session manager tests
class ngu_session_manager_test : public ::testing::Test
{
  void init()
  {
    srslog::fetch_basic_logger("TEST").set_level(srslog::basic_levels::debug);
    srslog::init();
    auto ngu_gw = std::make_unique<dummy_ngu_gateway>();
    ngu_gws.push_back(std::move(ngu_gw));

    // todo init ngu session manager
  }

  void finish()
  {
    ngu_gws.clear();
    // flush logger after each test
    srslog::flush();
  }

  std::vector<std::unique_ptr<gtpu_tnl_pdu_session>> ngu_gws;
};

} // namespace srsran::srs_cu_up
