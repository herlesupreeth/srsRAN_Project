/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "pusch_tpmi_select_test_data.h"
#include "srsran/ran/pusch/pusch_tpmi_select.h"
#include "srsran/ran/srs/srs_channel_matrix_formatters.h"
#include <cstdlib>
#include <fmt/ostream.h>
#include <gtest/gtest.h>

namespace fmt {

/// \brief Custom formatter for \c pusch_tpmi_select_info
template <>
struct formatter<srsran::pusch_tpmi_select_info> {
  /// Default constructor.
  formatter() = default;

  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const srsran::pusch_tpmi_select_info& info, FormatContext& ctx) const
  {
    unsigned max_nof_layers = info.get_max_nof_layers();

    format_to(ctx.out(), "[");
    for (unsigned nof_layers = 1; nof_layers <= max_nof_layers; ++nof_layers) {
      if (nof_layers != 1) {
        format_to(ctx.out(), ",");
      }

      auto layer_info = info.get_tpmi_select(nof_layers);

      format_to(ctx.out(), "{{{}, {:+.1f}dB}}", layer_info.tpmi, layer_info.sinr_dB);
    }

    format_to(ctx.out(), "]");

    return ctx.out();
  }
};

} // namespace fmt

namespace srsran {

std::ostream& operator<<(std::ostream& os, const test_case_t& test_case)
{
  fmt::print(os,
             "channel={}; noise_variance={}; info={};",
             test_case.channel_matrix,
             test_case.noise_variance,
             test_case.info);
  return os;
}

std::ostream& operator<<(std::ostream& os, const pusch_tpmi_select_info& info)
{
  fmt::print(os, "{}", info);
  return os;
}

bool operator==(const pusch_tpmi_select_info& left, const pusch_tpmi_select_info& right)
{
  // Extract maximum number of layers.
  unsigned max_nof_layers = left.get_max_nof_layers();
  if (max_nof_layers != right.get_max_nof_layers()) {
    return false;
  }

  // Iterate all number of layers.
  for (unsigned nof_layers = 1; nof_layers <= max_nof_layers; ++nof_layers) {
    auto layer_info_left  = left.get_tpmi_select(nof_layers);
    auto layer_info_right = right.get_tpmi_select(nof_layers);

    if (layer_info_left.tpmi != layer_info_right.tpmi) {
      return false;
    }

    if (std::abs(layer_info_left.sinr_dB - layer_info_right.sinr_dB) > 1.0F) {
      return false;
    }
  }

  return true;
}

} // namespace srsran

using namespace srsran;

class PuschTpmiSelectFixture : public ::testing::TestWithParam<test_case_t>
{};

TEST_P(PuschTpmiSelectFixture, VectorTest)
{
  // Get combined parameter.
  const test_case_t& test_case = GetParam();

  unsigned nof_tx_ports   = test_case.channel_matrix.get_nof_tx_ports();
  unsigned nof_rx_ports   = test_case.channel_matrix.get_nof_rx_ports();
  unsigned max_nof_layers = std::min(nof_tx_ports, nof_rx_ports);

  // Get UL-SCH information parameters.
  pusch_tpmi_select_info info = get_tpmi_select_info(
      test_case.channel_matrix, test_case.noise_variance, max_nof_layers, test_case.codebook_subset);

  // Compare with expected.
  ASSERT_EQ(info, test_case.info);
}

INSTANTIATE_TEST_SUITE_P(UlschInfo, PuschTpmiSelectFixture, ::testing::ValuesIn(pusch_tpmi_select_test_data));
