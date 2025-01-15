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

#include "srsran/du/du.h"

namespace srsran {

class du_operation_controller;

namespace srs_du {

class o_du_high;
class o_du_low;

/// O-RAN Distributed Unit interface. Includes the O-RAN DU high, O-RAN DU low and a DU operation controller in an
/// object.
class o_du
{
public:
  virtual ~o_du() = default;

  /// Returns the operation controller of this O-RAN DU.
  virtual du_operation_controller& get_operation_controller() = 0;

  /// Returns the O-RAN DU high of this O-RAN DU.
  virtual o_du_high& get_o_du_high() = 0;

  /// Returns the O-RAN DU low of this O-RAN DU.
  virtual o_du_low& get_o_du_low() = 0;
};

} // namespace srs_du
} // namespace srsran
