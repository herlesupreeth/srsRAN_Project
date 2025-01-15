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

#include <string>

namespace srsran {

/// HAL configuration of the application.
struct hal_appconfig {
  /// EAL configuration arguments.
  std::string eal_args;
};

} // namespace srsran
