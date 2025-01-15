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

#include "srsran/support/memory_pool/concurrent_thread_local_object_pool.h"

namespace srsran {

/// Concurrent PUCCH processor pool.
class pucch_processor_pool : public pucch_processor
{
public:
  /// Creates a PUCCH processor pool from a list of processors. Ownership is transferred to the pool.
  explicit pucch_processor_pool(std::vector<std::unique_ptr<pucch_processor>> processors_) :
    processors(std::move(processors_))
  {
  }

  // See interface for documentation.
  pucch_processor_result process(const resource_grid_reader& grid, const format0_configuration& config) override
  {
    pucch_processor& processor = processors.get();
    return processor.process(grid, config);
  }

  // See interface for documentation.
  pucch_processor_result process(const resource_grid_reader& grid, const format1_configuration& config) override
  {
    pucch_processor& processor = processors.get();
    return processor.process(grid, config);
  }

  // See interface for documentation.
  pucch_processor_result process(const resource_grid_reader& grid, const format2_configuration& config) override
  {
    pucch_processor& processor = processors.get();
    return processor.process(grid, config);
  }

  // See interface for documentation.
  pucch_processor_result process(const resource_grid_reader& grid, const format3_configuration& config) override
  {
    pucch_processor& processor = processors.get();
    return processor.process(grid, config);
  }

  // See interface for documentation.
  pucch_processor_result process(const resource_grid_reader& grid, const format4_configuration& config) override
  {
    pucch_processor& processor = processors.get();
    return processor.process(grid, config);
  }

private:
  concurrent_thread_local_object_pool<pucch_processor> processors;
};

} // namespace srsran