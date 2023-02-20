/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/phy/upper/channel_processors/ulsch_demultiplex.h"

namespace srsran {

class ulsch_demultiplex_impl : public ulsch_demultiplex
{
public:
  // See interface for documentation.
  void demultiplex(span<log_likelihood_ratio>       sch_data,
                   span<log_likelihood_ratio>       harq_ack,
                   span<log_likelihood_ratio>       csi_part1,
                   span<log_likelihood_ratio>       csi_part2,
                   span<const log_likelihood_ratio> input,
                   const configuration&             config) override;

  // See interface for documentation.
  ulsch_placeholder_list get_placeholders(const message_information& uci_message_info,
                                          const configuration&       config) override;
};

} // namespace srsran
