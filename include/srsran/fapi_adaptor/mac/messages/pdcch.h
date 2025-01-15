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

#include "srsran/fapi/message_builders.h"
#include "srsran/scheduler/result/pdcch_info.h"

namespace srsran {
namespace fapi_adaptor {

class precoding_matrix_mapper;

/// Collection of downlink DCIs that share the same BWP, CORESET and starting symbol.
struct mac_pdcch_pdu {
  /// Groups the DCI information.
  struct dci_info {
    dci_info(const dci_context_information* info_, const dci_payload* payload_) : info(info_), payload(payload_) {}
    const dci_context_information* info;
    const dci_payload*             payload;
  };

  const bwp_configuration*                                  bwp_cfg;
  const coreset_configuration*                              coreset_cfg;
  unsigned                                                  start_symbol;
  static_vector<dci_info, fapi::MAX_NUM_DCIS_PER_PDCCH_PDU> dcis;
};

/// \brief Helper function that converts from a PDCCH MAC PDU to a PDCCH FAPI PDU.
///
/// \param[out] fapi_pdu PDCCH FAPI PDU that will store the converted data.
/// \param[in] mac_pdu  MAC PDCCH PDU to convert to FAPI.
/// \param[in] pm_mapper Precoding matrix mapper.
/// \param[in] cell_nof_prbs Cell number of PRBs.
void convert_pdcch_mac_to_fapi(fapi::dl_pdcch_pdu&            fapi_pdu,
                               const mac_pdcch_pdu&           mac_pdu,
                               const precoding_matrix_mapper& pm_mapper,
                               unsigned                       cell_nof_prbs);

/// \brief Helper function that converts from a PDCCH MAC PDU to a PDCCH FAPI PDU.
///
/// \param[out] builder PDCCH FAPI builder that helps to fill the PDU.
/// \param[in] mac_pdu  MAC PDCCH PDU to convert to FAPI.
/// \param[in] pm_mapper Precoding matrix mapper.
/// \param[in] cell_nof_prbs Cell number of PRBs.
void convert_pdcch_mac_to_fapi(fapi::dl_pdcch_pdu_builder&    builder,
                               const mac_pdcch_pdu&           mac_pdu,
                               const precoding_matrix_mapper& pm_mapper,
                               unsigned                       cell_nof_prbs);

} // namespace fapi_adaptor
} // namespace srsran
