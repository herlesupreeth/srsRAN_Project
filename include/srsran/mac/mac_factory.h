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

#include "srsran/du/du_high/du_high_executor_mapper.h"
#include "srsran/mac/mac.h"
#include "srsran/mac/mac_cell_result.h"
#include "srsran/mac/mac_config.h"
#include "srsran/scheduler/config/scheduler_expert_config.h"
#include <memory>

namespace srsran {

std::unique_ptr<mac_interface> create_mac(const mac_config& mac_cfg);

} // namespace srsran
