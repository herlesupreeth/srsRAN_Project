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

#include "srsran/ran/du_types.h"
#include "srsran/ran/rnti.h"

namespace srsran {

struct mac_log_prefix {
  mac_log_prefix(du_ue_index_t ue_idx, rnti_t rnti_, const char* proc_name_) :
    ue_index(ue_idx), rnti(rnti_), proc_name(proc_name_)
  {
  }

  du_ue_index_t ue_index  = INVALID_DU_UE_INDEX;
  rnti_t        rnti      = rnti_t::INVALID_RNTI;
  const char*   proc_name = nullptr;
};

} // namespace srsran

namespace fmt {

template <>
struct formatter<srsran::mac_log_prefix> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const srsran::mac_log_prefix& prefix, FormatContext& ctx) const
  {
    bool first_id = true;
    auto get_sep  = [&first_id]() { return std::exchange(first_id, false) ? "" : " "; };
    if (prefix.ue_index != srsran::INVALID_DU_UE_INDEX) {
      format_to(ctx.out(), "{}ue={}", get_sep(), fmt::underlying(prefix.ue_index));
    }
    if (prefix.rnti != srsran::rnti_t::INVALID_RNTI) {
      format_to(ctx.out(), "{}crnti={}", get_sep(), prefix.rnti);
    }
    format_to(ctx.out(), "{}proc=\"{}\"", get_sep(), prefix.proc_name);
    return ctx.out();
  }
};

} // namespace fmt
