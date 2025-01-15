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

#include "apps/units/application_unit.h"
#include "apps/units/o_cu_up/o_cu_up_builder.h"
#include <yaml-cpp/node/node.h>

namespace srsran {

struct o_cu_up_unit_config;
struct worker_manager_config;

/// O-RAN CU-UP application unit interface.
class o_cu_up_application_unit : public application_unit
{
public:
  virtual ~o_cu_up_application_unit() = default;

  /// Creates an O-RAN CU-UP using the given dependencies.
  virtual o_cu_up_unit create_o_cu_up_unit(const o_cu_up_unit_dependencies& dependencies) = 0;

  /// Returns the O-RAN CU-UP unit configuration of this O-RAN CU-UP application unit.
  virtual o_cu_up_unit_config&       get_o_cu_up_unit_config()       = 0;
  virtual const o_cu_up_unit_config& get_o_cu_up_unit_config() const = 0;

  /// Dumps the O-RAN CU-UP configuration into the given YAML node.
  virtual void dump_config(YAML::Node& node) const = 0;

  /// Fills the given worker manager configuration with the O-RAN CU-UP parameters.
  virtual void fill_worker_manager_config(worker_manager_config& config) = 0;
};

/// Creates an O-RAN CU-UP application unit.
std::unique_ptr<o_cu_up_application_unit> create_o_cu_up_application_unit(std::string_view app_name);

} // namespace srsran
