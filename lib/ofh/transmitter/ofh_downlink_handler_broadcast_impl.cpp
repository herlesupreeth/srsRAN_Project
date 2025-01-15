/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ofh_downlink_handler_broadcast_impl.h"
#include "helpers.h"
#include "srsran/instrumentation/traces/ofh_traces.h"
#include "srsran/ofh/ofh_error_notifier.h"
#include "srsran/phy/support/resource_grid_context.h"
#include "srsran/phy/support/resource_grid_reader.h"
#include "srsran/phy/support/shared_resource_grid.h"

using namespace srsran;
using namespace ofh;

namespace {

/// Open Fronthaul error notifier dummy implementation.
class error_notifier_dummy : public error_notifier
{
public:
  void on_late_downlink_message(const error_context& context) override {}
};

} // namespace

/// Dummy error notifier for the downlink handler construction.
static error_notifier_dummy dummy_err_notifier;

downlink_handler_broadcast_impl::downlink_handler_broadcast_impl(
    const downlink_handler_broadcast_impl_config&  config,
    downlink_handler_broadcast_impl_dependencies&& dependencies) :
  sector_id(config.sector),
  logger(*dependencies.logger),
  cp(config.cp),
  tdd_config(config.tdd_config),
  dl_eaxc(config.dl_eaxc.begin(), config.dl_eaxc.end()),
  data_flow_cplane(std::move(dependencies.data_flow_cplane)),
  data_flow_uplane(std::move(dependencies.data_flow_uplane)),
  window_checker(
      *dependencies.logger,
      config.sector,
      calculate_nof_symbols_before_ota(config.cp, config.scs, config.dl_processing_time, config.tx_timing_params),
      get_nsymb_per_slot(config.cp),
      to_numerology_value(config.scs)),
  frame_pool(std::move(dependencies.frame_pool)),
  err_notifier(dummy_err_notifier)
{
  srsran_assert(data_flow_cplane, "Invalid Control-Plane data flow");
  srsran_assert(data_flow_uplane, "Invalid User-Plane data flow");
  srsran_assert(frame_pool, "Invalid frame pool");
}

void downlink_handler_broadcast_impl::handle_dl_data(const resource_grid_context& context,
                                                     const shared_resource_grid&  grid)
{
  const resource_grid_reader& reader = grid.get_reader();
  trace_point                 tp     = ofh_tracer.now();

  // Clear any stale buffers associated with the context slot.
  frame_pool->clear_downlink_slot(context.slot, context.sector, logger);

  if (window_checker.is_late(context.slot)) {
    err_notifier.get().on_late_downlink_message({context.slot, sector_id});
    logger.warning("Sector#{}: dropped late downlink resource grid in slot '{}' and sector#{}. No OFH data will be "
                   "transmitted for this slot",
                   sector_id,
                   context.slot,
                   context.sector);
    ofh_tracer << trace_event("ofh_handle_dl_late", tp);

    return;
  }

  data_flow_cplane_type_1_context cplane_context;
  cplane_context.slot         = context.slot;
  cplane_context.filter_type  = filter_index_type::standard_channel_filter;
  cplane_context.direction    = data_direction::downlink;
  cplane_context.symbol_range = tdd_config
                                    ? get_active_tdd_dl_symbols(tdd_config.value(), context.slot.slot_index(), cp)
                                    : ofdm_symbol_range(0, reader.get_nof_symbols());

  data_flow_uplane_resource_grid_context uplane_context;
  uplane_context.slot         = context.slot;
  uplane_context.sector       = context.sector;
  uplane_context.symbol_range = cplane_context.symbol_range;
  uplane_context.port         = 0;

  for (auto eaxc : dl_eaxc) {
    cplane_context.eaxc = eaxc;
    // Control-Plane data flow.
    data_flow_cplane->enqueue_section_type_1_message(cplane_context);

    // User-Plane data flow.
    uplane_context.eaxc = eaxc;
    data_flow_uplane->enqueue_section_type_1_message(uplane_context, grid);
  }
  ofh_tracer << trace_event("ofh_handle_downlink", tp);
}
