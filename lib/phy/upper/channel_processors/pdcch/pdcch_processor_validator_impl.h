/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/phy/upper/channel_processors/pdcch/pdcch_processor.h"
#include "srsran/ran/pdcch/pdcch_constants.h"

namespace srsran {

/// Implements a parameter validator for \ref pdcch_processor_impl.
class pdcch_processor_validator_impl : public pdcch_pdu_validator
{
public:
  // See interface for documentation.
  error_type<std::string> is_valid(const pdcch_processor::pdu_t& pdu) const override;
};

} // namespace srsran