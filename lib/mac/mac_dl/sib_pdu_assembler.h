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

#include "srsran/mac/mac_cell_manager.h"
#include "srsran/scheduler/scheduler_slot_handler.h"

namespace srsran {

/// Class that manages the encoding of BCCH-DL-SCH messages to be fit in a Transport Block.
class sib_pdu_assembler
{
public:
  explicit sib_pdu_assembler(const byte_buffer& bcch_dl_sch_payload) : min_payload_size(bcch_dl_sch_payload.length())
  {
    // Number of padding bytes to prereserve. This value is implementation-defined.
    static constexpr unsigned MAX_PADDING_BYTES_LEN = 64;
    // Note: Resizing the bcch_payload after the ctor is forbidden, to avoid vector memory relocations and invalidation
    // of pointers passed to the lower layers. For this reason, we pre-reserve any potential padding bytes.
    bcch_payload.resize(min_payload_size + MAX_PADDING_BYTES_LEN, 0);
    bcch_payload.assign(bcch_dl_sch_payload.begin(), bcch_dl_sch_payload.end());
  }

  span<const uint8_t> encode_sib_pdu(unsigned tbs_bytes) const
  {
    srsgnb_assert(tbs_bytes >= min_payload_size, "The TBS for SIB1 cannot be smaller than the SIB1 payload");
    srsgnb_assert(tbs_bytes <= bcch_payload.capacity(),
                  "Memory rellocations of the SIB1 payload not allowed. Consider reserving more bytes for PADDING");
    return span<const uint8_t>(bcch_payload.data(), tbs_bytes);
  }

private:
  /// Holds the original BCCH-DL-SCH message, defined in the MAC cell configuration, plus extra padding bytes.
  std::vector<uint8_t> bcch_payload;
  /// Length of the original BCCH-DL-SCH message, without padding, defined in the MAC cell configuration.
  unsigned min_payload_size;
};

} // namespace srsran
