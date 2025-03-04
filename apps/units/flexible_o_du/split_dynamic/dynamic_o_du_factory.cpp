/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "dynamic_o_du_factory.h"
#include "apps/services/worker_manager/worker_manager.h"
#include "apps/units/flexible_o_du/split_7_2/helpers/ru_ofh_factories.h"
#include "apps/units/flexible_o_du/split_8/helpers/ru_sdr_factories.h"
#include "dynamic_o_du_translators.h"
#include "srsran/ru/dummy/ru_dummy_factory.h"

using namespace srsran;

static std::unique_ptr<radio_unit> create_dummy_radio_unit(const ru_dummy_unit_config&          ru_cfg,
                                                           const flexible_o_du_ru_config&       ru_config,
                                                           const flexible_o_du_ru_dependencies& ru_dependencies)
{
  ru_dummy_dependencies dependencies{
      .logger          = srslog::fetch_basic_logger("RU", true),
      .executor        = ru_dependencies.workers.radio_exec,
      .symbol_notifier = ru_dependencies.symbol_notifier,
      .timing_notifier = ru_dependencies.timing_notifier,
      .error_notifier  = ru_dependencies.error_notifier,
  };

  return create_dummy_ru(
      generate_ru_dummy_config(ru_cfg, ru_config.du_cells, ru_config.max_processing_delay, ru_config.prach_nof_ports),
      dependencies);
}

std::unique_ptr<radio_unit>
dynamic_o_du_factory::create_radio_unit(const flexible_o_du_ru_config&       ru_config,
                                        const flexible_o_du_ru_dependencies& ru_dependencies)
{
  const auto& ru_cfg = unit_config.ru_cfg;
  if (const auto* cfg = std::get_if<ru_ofh_unit_parsed_config>(&ru_cfg)) {
    return create_ofh_radio_unit(cfg->config, ru_config, ru_dependencies);
  }

  if (const auto* cfg = std::get_if<ru_sdr_unit_config>(&ru_cfg)) {
    return create_sdr_radio_unit(*cfg, ru_config, ru_dependencies);
  }

  return create_dummy_radio_unit(std::get<ru_dummy_unit_config>(ru_cfg), ru_config, ru_dependencies);
}
