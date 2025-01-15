/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ofh_data_flow_uplane_uplink_data_impl.h"
#include "srsran/instrumentation/traces/ofh_traces.h"
#include "srsran/ofh/serdes/ofh_message_decoder_properties.h"

using namespace srsran;
using namespace ofh;

data_flow_uplane_uplink_data_impl::data_flow_uplane_uplink_data_impl(
    const data_flow_uplane_uplink_data_impl_config&  config,
    data_flow_uplane_uplink_data_impl_dependencies&& dependencies) :
  logger(*dependencies.logger),
  ul_cplane_context_repo(std::move(dependencies.ul_cplane_context_repo)),
  uplane_decoder(std::move(dependencies.uplane_decoder)),
  rx_symbol_writer(config.ul_eaxc, config.sector, *dependencies.logger, dependencies.ul_context_repo),
  notification_sender(*dependencies.logger, dependencies.ul_context_repo, dependencies.notifier),
  sector_id(config.sector)
{
  srsran_assert(ul_cplane_context_repo, "Invalid control plane repository");
  srsran_assert(uplane_decoder, "Invalid User-Plane decoder");
}

void data_flow_uplane_uplink_data_impl::decode_type1_message(unsigned eaxc, span<const uint8_t> message)
{
  trace_point decode_tp = ofh_tracer.now();

  uplane_message_decoder_results results;
  if (!uplane_decoder->decode(results, message)) {
    return;
  }
  ofh_tracer << trace_event("ofh_receiver_uplane_decode", decode_tp);

  if (should_uplane_packet_be_filtered(eaxc, results)) {
    return;
  }

  rx_symbol_writer.write_to_resource_grid(eaxc, results);
  notification_sender.notify_received_symbol(results.params.slot, results.params.symbol_id);
}

bool data_flow_uplane_uplink_data_impl::should_uplane_packet_be_filtered(
    unsigned                              eaxc,
    const uplane_message_decoder_results& results) const
{
  if (results.params.filter_index == filter_index_type::reserved || is_a_prach_message(results.params.filter_index)) {
    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet for slot '{}' and symbol '{}' as decoded "
                "filter  index value '{}' is not valid",
                sector_id,
                results.params.slot,
                results.params.symbol_id,
                to_value(results.params.filter_index));

    return true;
  }

  const uplane_message_params& params = results.params;
  expected<ul_cplane_context>  ex_cp_context =
      ul_cplane_context_repo->get(params.slot, params.symbol_id, params.filter_index, eaxc);

  if (!ex_cp_context) {
    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as no data was expected for slot '{}', "
                "symbol '{}' and eAxC '{}'",
                sector_id,
                params.slot,
                params.symbol_id,
                eaxc);

    return true;
  }

  // Check the PRBs.
  const ul_cplane_context& cp_context = ex_cp_context.value();

  return std::any_of(
      results.sections.begin(), results.sections.end(), [&cp_context, this](const uplane_section_params& up_section) {
        if (!up_section.is_every_rb_used) {
          logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as 'every other resource block is "
                      "used' mode is not supported",
                      sector_id);

          return true;
        }

        if (!up_section.use_current_symbol_number) {
          logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as 'increment the current symbol "
                      "number and use that' mode is not supported",
                      sector_id);

          return true;
        }

        bool is_up_section_not_found_in_cp_section =
            (up_section.start_prb < cp_context.prb_start ||
             (up_section.start_prb + up_section.nof_prbs) > (cp_context.prb_start + cp_context.nof_prb));

        if (is_up_section_not_found_in_cp_section) {
          logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as PRB index range '{}:{}' does "
                      "not match the expected range '{}:{}'",
                      sector_id,
                      up_section.start_prb,
                      up_section.nof_prbs,
                      cp_context.prb_start,
                      cp_context.nof_prb);
        }

        return is_up_section_not_found_in_cp_section;
      });
}
