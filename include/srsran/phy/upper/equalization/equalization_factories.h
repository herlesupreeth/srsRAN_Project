
/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

/// \file
/// \brief Channel equalization factories.

#pragma once

#include "srsran/phy/upper/equalization/channel_equalizer.h"
#include "srsran/phy/upper/equalization/channel_equalizer_algorithm_type.h"

namespace srsran {

/// Describes a channel equalizer factory.
class channel_equalizer_factory
{
public:
  /// Default destructor.
  virtual ~channel_equalizer_factory() = default;

  /// \brief Creates a channel equalizer.
  /// \return A unique pointer to a channel equalizer instance.
  virtual std::unique_ptr<channel_equalizer> create() = 0;
};

/// \brief Creates a generic channel equalizer factory.
/// \param[in] type Selects the channel equalizer algorithm type.
/// \return A generic channel equalizer factory.
std::shared_ptr<channel_equalizer_factory>
create_channel_equalizer_generic_factory(channel_equalizer_algorithm_type type = channel_equalizer_algorithm_type::zf);

} // namespace srsran
