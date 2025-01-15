/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/scheduler/scheduler_factory.h"
#include "scheduler_impl.h"

using namespace srsran;

std::unique_ptr<mac_scheduler> srsran::create_scheduler(const scheduler_config& sched_cfg)
{
  return std::make_unique<scheduler_impl>(sched_cfg);
}
