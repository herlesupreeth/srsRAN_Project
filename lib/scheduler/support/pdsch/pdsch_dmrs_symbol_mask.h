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

#include "srsran/scheduler/config/dmrs.h"

namespace srsran {

/// \brief Collects the necessary parameters to calculate the DMRS symbol mask for a TypeA PDSCH mapping and single
/// duration DMRS.
struct pdsch_dmrs_symbol_mask_mapping_type_A_single_configuration {
  /// \brief Indicates the first OFDM symbol within the slot carrying DMRS.
  ///
  /// This value is given by higher layer parameter \c dmrs-TypeA-Position. Possible values are {2, 3}.
  dmrs_typeA_position typeA_pos;
  /// \brief Indicates the number of additional DMRS positions in time domain.
  ///
  /// This value is given by higher layer parameter \c dmrs-AdditionalPosition. Possible values are {0...3}.
  dmrs_additional_positions additional_position;
  /// \brief Last OFDM symbol scheduled for PDSCH
  ///
  /// It indicates the number of symbols between the first OFDM symbol of the slot and the last OFDM symbol of the
  /// scheduled PDSCH resources in the slot for PDSCH in OFDM symbols. It corresponds to parameter \f$l_d\f$ as
  /// per TS38.211, Section 7.4.1.1.2.
  ///
  /// Possible values are {3, ..., 14}.
  bounded_integer<uint8_t, 3, 14> last_symbol;
  /// Indicates the higher layer parameter \c lte-CRS-ToMatchAround is configured.
  bool lte_crs_match_around;
  /// Indicates the UE has indicated it is capable of \c additionalDMRS-DL-Alt.
  bool ue_capable_additional_dmrs_dl_alt;
};

/// \brief Calculates the DMRS for PDSCH symbol mask for single duration.
///
/// It is implemented as per TS38.211 Table 5.1.2.1.1-2.
///
/// Any configuration that is not covered in the table triggers an assertion.
dmrs_symbol_mask pdsch_dmrs_symbol_mask_mapping_type_A_single_get(
    const pdsch_dmrs_symbol_mask_mapping_type_A_single_configuration& config);

} // namespace srsran
