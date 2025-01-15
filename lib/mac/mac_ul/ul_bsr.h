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

#include "srsran/adt/byte_buffer.h"
#include "srsran/adt/expected.h"
#include "srsran/adt/span.h"
#include "srsran/adt/static_vector.h"
#include "srsran/adt/to_array.h"
#include "srsran/mac/bsr_config.h"

namespace srsran {

/// UL BSR Report for a single Logical Channel Group
struct lcg_bsr_report {
  lcg_id_t lcg_id;
  uint8_t  buffer_size;
};

/// List of reported UL BSRs
using lcg_bsr_report_list = static_vector<lcg_bsr_report, MAX_NOF_LCGS>;

/// Decode Short BSR
inline lcg_bsr_report decode_sbsr(byte_buffer_view payload)
{
  srsran_sanity_check(not payload.empty(), "Trying to decode SBSR but payload is empty.");
  lcg_bsr_report sbsr = {};
  sbsr.lcg_id         = uint_to_lcg_id((payload[0] & 0xe0U) >> 5U);
  sbsr.buffer_size    = payload[0] & 0x1fU;
  return sbsr;
}

struct long_bsr_report {
  lcg_bsr_report_list list; /// one entry for each reported LCG
};

/// Decode Long BSR
expected<long_bsr_report> decode_lbsr(bsr_format format, byte_buffer_view payload);

/// Converts the buffer size field of a BSR (5 or 8-bit Buffer Size field) into Nof Bytes.
/// \param buff_size_index The buffer size field contained in the MAC PDU.
/// \param format The BSR format that determines the buffer size field length.
/// \return The actual buffer size level in Bytes.
uint32_t buff_size_field_to_bytes(size_t buff_size_index, bsr_format format);

} // namespace srsran
