/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "pusch_codeblock_decoder.h"

using namespace srsran;

void pusch_codeblock_decoder::rate_match(span<log_likelihood_ratio>       rm_buffer,
                                         span<const log_likelihood_ratio> cb_llrs,
                                         bool                             new_data,
                                         const codeblock_metadata&        metadata)
{
  dematcher->rate_dematch(rm_buffer, cb_llrs, new_data, metadata);
}

std::optional<unsigned> pusch_codeblock_decoder::decode(bit_buffer                       cb_data,
                                                        span<log_likelihood_ratio>       rm_buffer,
                                                        span<const log_likelihood_ratio> cb_llrs,
                                                        bool                             new_data,
                                                        srsran::crc_generator_poly       crc_poly,
                                                        bool                             use_early_stop,
                                                        unsigned                         nof_ldpc_iterations,
                                                        const codeblock_metadata&        metadata)
{
  rate_match(rm_buffer, cb_llrs, new_data, metadata);

  // Prepare LDPC decoder configuration.
  ldpc_decoder::configuration decoder_config;
  decoder_config.block_conf                    = metadata;
  decoder_config.algorithm_conf.max_iterations = nof_ldpc_iterations;
  // As for the other algorithm_details, we use the default values.

  // Select CRC calculator.
  crc_calculator* crc = select_crc(crc_poly);
  srsran_assert(crc != nullptr, "Invalid CRC calculator.");

  // Decode with early stop.
  if (use_early_stop) {
    return decoder->decode(cb_data, rm_buffer, crc, decoder_config);
  }

  // Without early stop, first decode and then check the CRC.
  decoder->decode(cb_data, rm_buffer, nullptr, decoder_config);

  // Discard filler bits for the CRC.
  unsigned nof_significant_bits = cb_data.size() - metadata.cb_specific.nof_filler_bits;
  if (crc->calculate(cb_data.first(nof_significant_bits)) == 0) {
    return nof_ldpc_iterations;
  }

  return std::nullopt;
}
