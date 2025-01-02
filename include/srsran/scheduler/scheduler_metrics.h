/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/adt/span.h"
#include "srsran/ran/pci.h"
#include "srsran/ran/phy_time_unit.h"
#include "srsran/ran/rnti.h"
#include "srsran/ran/sch/sch_mcs.h"
#include "srsran/ran/slot_point.h"
#include "srsran/support/math/stats.h"
#include <optional>

namespace srsran {

/// \brief Snapshot of the metrics for a UE.
struct scheduler_ue_metrics {
  pci_t                pci;
  rnti_t               rnti;
  sch_mcs_index        dl_mcs;
  unsigned             tot_dl_prbs_used;
  double               dl_brate_kbps;
  unsigned             dl_nof_ok;
  unsigned             dl_nof_nok;
  float                pusch_snr_db;
  float                pusch_rsrp_db;
  float                pucch_snr_db;
  sch_mcs_index        ul_mcs;
  unsigned             tot_ul_prbs_used;
  double               ul_brate_kbps;
  double               crc_delay_ms;
  unsigned             ul_nof_ok;
  unsigned             ul_nof_nok;
  unsigned             bsr;
  unsigned             sr_count;
  unsigned             dl_bs;
  std::optional<float> last_dl_olla;
  std::optional<float> last_ul_olla;
  std::optional<int>   last_phr;
  std::optional<float> mean_ce_delay_msec;
  /// Time advance statistics in seconds.
  sample_statistics<float> ta_stats;
  sample_statistics<float> pusch_ta_stats;
  sample_statistics<float> pucch_ta_stats;
  sample_statistics<float> srs_ta_stats;
  /// CQI statistics over the metrics report interval.
  sample_statistics<unsigned> cqi_stats;
  /// RI statistics over the metrics report interval.
  sample_statistics<unsigned> ri_stats;
};

/// \brief Event that occurred in the cell of the scheduler.
struct scheduler_cell_event {
  enum class event_type { ue_add, ue_reconf, ue_rem };

  slot_point slot;
  rnti_t     rnti = rnti_t::INVALID_RNTI;
  event_type type;
};

inline const char* sched_event_to_string(scheduler_cell_event::event_type ev)
{
  std::array<const char*, 3> names = {"ue_add", "ue_reconf", "ue_rem"};
  return names[std::min(static_cast<size_t>(ev), names.size() - 1)];
}

/// \brief Snapshot of the metrics for a cell and its UEs.
struct scheduler_cell_metrics {
  /// Latency histogram number of bins.
  static constexpr unsigned latency_hist_bins = 10;
  /// Distance between histogram bins.
  static constexpr unsigned nof_usec_per_bin = 50;
  /// Number of cell PRBs.
  unsigned nof_prbs = 0;
  /// Number of full downlink slots.
  unsigned nof_dl_slots = 0;
  /// Number of full uplink slots.
  unsigned nof_ul_slots = 0;
  /// Number of PRACH preambles detected.
  unsigned nof_prach_preambles = 0;

  unsigned                                nof_error_indications = 0;
  std::chrono::microseconds               average_decision_latency{0};
  std::array<unsigned, latency_hist_bins> latency_histogram{0};
  std::vector<scheduler_cell_event>       events;
  std::vector<scheduler_ue_metrics>       ue_metrics;
};

/// \brief Notifier interface used by scheduler to report metrics.
class scheduler_metrics_notifier
{
public:
  virtual ~scheduler_metrics_notifier() = default;

  /// \brief This method will be called periodically by the scheduler to report the latest UE metrics statistics.
  virtual void report_metrics(const scheduler_cell_metrics& report) = 0;
};

} // namespace srsran
