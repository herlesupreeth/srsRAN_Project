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
#include <optional>
#include <utility>

namespace srsran {

/// Collects transmit or receive signal statistics.
struct lower_phy_baseband_metrics {
  /// Average power.
  float avg_power;
  /// Peak power.
  float peak_power;
  /// \brief Clipping event counters.
  ///
  /// It comprises of the number of clipped samples and the total number of processed samples.
  std::optional<std::pair<uint64_t, uint64_t>> clipping;
};

} // namespace srsran
