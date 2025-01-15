/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "../message_builder_helpers.h"
#include "helpers.h"
#include "srsran/fapi/message_validators.h"

using namespace srsran;
using namespace fapi;
using namespace unittest;

class validate_ul_dci_request_field
  : public validate_fapi_message<ul_dci_request_message>,
    public testing::TestWithParam<std::tuple<pdu_field_data<ul_dci_request_message>, test_case_data>>
{};

TEST_P(validate_ul_dci_request_field, with_value)
{
  auto params = GetParam();

  execute_test(std::get<0>(params),
               std::get<1>(params),
               build_valid_ul_dci_request,
               validate_ul_dci_request,
               srsran::fapi::message_type_id::ul_dci_request);
}

INSTANTIATE_TEST_SUITE_P(sfn,
                         validate_ul_dci_request_field,
                         testing::Combine(testing::Values(pdu_field_data<ul_dci_request_message>{
                                              "sfn",
                                              [](ul_dci_request_message& msg, int value) { msg.sfn = value; }}),
                                          testing::Values(test_case_data{0, true},
                                                          test_case_data{512, true},
                                                          test_case_data{1023, true},
                                                          test_case_data{1024, false})));

INSTANTIATE_TEST_SUITE_P(slot,
                         validate_ul_dci_request_field,
                         testing::Combine(testing::Values(pdu_field_data<ul_dci_request_message>{
                                              "slot",
                                              [](ul_dci_request_message& msg, int value) { msg.slot = value; }}),
                                          testing::Values(test_case_data{0, true},
                                                          test_case_data{80, true},
                                                          test_case_data{159, true},
                                                          test_case_data{160, false})));

/// Tests that a valid UL_DCI.request message validates correctly.
TEST(validate_ul_tti_request, valid_request_passes)
{
  const auto& msg = build_valid_ul_dci_request();

  const auto& result = validate_ul_dci_request(msg);

  ASSERT_TRUE(result);
}

/// Tests that a UL_TTI.request message which contains errors in some properties fails to validate.
TEST(validate_ul_tti_request, invalid_request_fails)
{
  auto msg = build_valid_ul_dci_request();

  // Set some errors.
  msg.sfn                          = 2000U;
  msg.slot                         = 1000U;
  msg.pdus[0].pdu.coreset_bwp_size = 2000U;

  const auto& result = validate_ul_dci_request(msg);

  ASSERT_FALSE(result);

  const auto& report = result.error();
  // Check that the 3 errors are reported.
  ASSERT_EQ(report.reports.size(), 3u);
}
