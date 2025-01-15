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

#include "apps/units/flexible_o_du/o_du_high/o_du_high_unit_config.h"

namespace srsran {
/// O-RAN DU Split 6 unit configuration.
struct split6_o_du_unit_config {
  /// O-DU high configuration.
  o_du_high_unit_config odu_high_cfg;
};

} // namespace srsran
