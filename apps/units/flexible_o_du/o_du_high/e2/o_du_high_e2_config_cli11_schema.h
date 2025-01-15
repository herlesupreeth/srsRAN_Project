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

#include "CLI/CLI11.hpp"

namespace srsran {

struct o_du_high_e2_config;

/// Configures the given CLI11 application with the O-RAN DU high E2 configuration schema.
void configure_cli11_with_o_du_high_e2_config_schema(CLI::App& app, o_du_high_e2_config& config);

/// Auto derive O-RAN DU high E2 parameters after the parsing.
void autoderive_o_du_high_e2_parameters_after_parsing(o_du_high_e2_config& unit_cfg);

} // namespace srsran
