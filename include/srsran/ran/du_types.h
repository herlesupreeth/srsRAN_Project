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

#include "srsran/ran/gnb_constants.h"
#include <cstdint>
#include <type_traits>

namespace srsran {

/// Maximum number of UEs supported by DU (implementation-defined).
enum du_ue_index_t : uint16_t {
  MIN_DU_UE_INDEX     = 0,
  MAX_DU_UE_INDEX     = 1023,
  MAX_NOF_DU_UES      = 1024,
  INVALID_DU_UE_INDEX = 1024
};

/// Maximum number of cells supported by DU (implementation-defined).
enum du_cell_index_t : uint16_t {
  MIN_DU_CELL_INDEX     = 0,
  MAX_DU_CELL_INDEX     = MAX_CELLS_PER_DU - 1,
  MAX_NOF_DU_CELLS      = MAX_CELLS_PER_DU,
  INVALID_DU_CELL_INDEX = MAX_NOF_DU_CELLS
};

/// Convert integer to DU UE index type.
constexpr du_ue_index_t to_du_ue_index(std::underlying_type_t<du_ue_index_t> idx)
{
  return static_cast<du_ue_index_t>(idx);
}

constexpr bool is_du_ue_index_valid(du_ue_index_t ue_idx)
{
  return ue_idx < MAX_NOF_DU_UES;
}

/// Convert integer to DU cell index type.
constexpr du_cell_index_t to_du_cell_index(std::underlying_type_t<du_cell_index_t> idx)
{
  return static_cast<du_cell_index_t>(idx);
}

/// Maximum number of cells supported by a single UE.
enum ue_cell_index_t : uint16_t {
  PCELL_INDEX           = 0,
  MAX_UE_SCELL_INDEX    = 15,
  MAX_NOF_SCELL_INDEXES = 16,
  INVALID_UE_CELL_INDEX = MAX_NOF_SCELL_INDEXES
};

constexpr ue_cell_index_t to_ue_cell_index(std::underlying_type_t<ue_cell_index_t> idx)
{
  return static_cast<ue_cell_index_t>(idx);
}

/// \brief DU-specific index to group of cells that might be aggregated into a UE-specific CellGroup, if the UE
/// is CA-capable.
enum du_cell_group_index_t : uint16_t {
  MAX_DU_CELL_GROUPS          = du_cell_index_t::MAX_NOF_DU_CELLS,
  INVALID_DU_CELL_GROUP_INDEX = MAX_DU_CELL_GROUPS
};

} // namespace srsran
