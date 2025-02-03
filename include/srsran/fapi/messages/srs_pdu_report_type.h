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

#include <cstdint>

namespace srsran {
namespace fapi {

/// Describes the SRS report type.
enum class srs_report_type : uint8_t {
  per_prg_and_symbol_snr = 0,
  normalized_channel_iq_matrix,
  channel_svd,
  positioning,
  su_mimo_codebook,
  channel_2d_dft,
  su_mimo_codebook_v2,
  per_prg_ni_and_rsrp,
  last,
  no_report = 255
};

/// Converts a SRS report type to unsigned.
constexpr unsigned to_value(srs_report_type value)
{
  return static_cast<unsigned>(value);
}

/// Converts the given SRS report type to a string.
constexpr const char* to_string(srs_report_type value)
{
  switch (value) {
    case srs_report_type::normalized_channel_iq_matrix:
      return "normalized_channel_iq_matrix";
    case srs_report_type::channel_2d_dft:
      return "channel_2d_dft";
    case srs_report_type::channel_svd:
      return "channel_svd";
    case srs_report_type::per_prg_and_symbol_snr:
      return "per_prg_and_symbol_snr";
    case srs_report_type::per_prg_ni_and_rsrp:
      return "per_prg_ni_and_rsrp";
    case srs_report_type::positioning:
      return "positioning";
    case srs_report_type::su_mimo_codebook:
      return "su_mimo_codebook";
    case srs_report_type::su_mimo_codebook_v2:
      return "su_mimo_codebook_v2";
    default:
      break;
  }
  return "no_report";
}

} // namespace fapi
} // namespace srsran
