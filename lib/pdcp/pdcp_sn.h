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

#include "srsran/pdcp/pdcp_config.h"
#include "srsran/support/srsran_assert.h"

namespace srsran {

constexpr uint32_t pdcp_compute_sn(uint32_t count, pdcp_sn_size sn_size)
{
  return count & (0xffffffffU >> (32U - pdcp_sn_size_to_uint(sn_size)));
}

constexpr uint32_t pdcp_compute_hfn(uint32_t count, pdcp_sn_size sn_size)
{
  return (count >> pdcp_sn_size_to_uint(sn_size));
}

constexpr uint32_t pdcp_compute_count(uint32_t hfn, uint32_t sn, pdcp_sn_size sn_size)
{
  return (hfn << pdcp_sn_size_to_uint(sn_size)) | sn;
}

constexpr uint32_t pdcp_sn_cardinality(pdcp_sn_size sn_size)
{
  uint16_t sn_size_num = pdcp_sn_size_to_uint(sn_size);
  srsgnb_assert(sn_size_num < 32, "Cardinality of sn_size={} exceeds return type 'uint32_t'", sn_size_num);
  return (1 << sn_size_num);
}

} // namespace srsran
