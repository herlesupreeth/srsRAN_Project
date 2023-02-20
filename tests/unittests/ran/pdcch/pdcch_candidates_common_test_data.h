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

// This file was generated using the following MATLAB class:
//   + "srsPDCCHCandidatesCommonUnittest.m"

#include "srsran/ran/pdcch/pdcch_candidates.h"

namespace srsran {

struct test_case_t {
  pdcch_candidates_common_ss_configuration config;
  pdcch_candidate_list                     candidates;
};

static const std::vector<test_case_t> pdcch_candidates_common_test_data = {
    // clang-format off
  {{aggregation_level::n1, 0, 24}, {}},
  {{aggregation_level::n1, 1, 24}, {0}},
  {{aggregation_level::n2, 1, 24}, {0}},
  {{aggregation_level::n4, 1, 24}, {0}},
  {{aggregation_level::n8, 1, 24}, {0}},
  {{aggregation_level::n16, 1, 24}, {0}},
  {{aggregation_level::n1, 2, 24}, {0, 12}},
  {{aggregation_level::n2, 2, 24}, {0, 12}},
  {{aggregation_level::n4, 2, 24}, {0, 12}},
  {{aggregation_level::n8, 2, 24}, {0, 8}},
  {{aggregation_level::n1, 3, 24}, {0, 8, 16}},
  {{aggregation_level::n2, 3, 24}, {0, 8, 16}},
  {{aggregation_level::n4, 3, 24}, {0, 8, 16}},
  {{aggregation_level::n8, 3, 24}, {0, 8, 16}},
  {{aggregation_level::n1, 4, 24}, {0,  6, 12, 18}},
  {{aggregation_level::n2, 4, 24}, {0,  6, 12, 18}},
  {{aggregation_level::n4, 4, 24}, {0,  4, 12, 16}},
  {{aggregation_level::n1, 5, 24}, {0,  4,  9, 14, 19}},
  {{aggregation_level::n2, 5, 24}, {0,  4,  8, 14, 18}},
  {{aggregation_level::n4, 5, 24}, {0,  4,  8, 12, 16}},
  {{aggregation_level::n1, 6, 24}, {0,  4,  8, 12, 16, 20}},
  {{aggregation_level::n2, 6, 24}, {0,  4,  8, 12, 16, 20}},
  {{aggregation_level::n4, 6, 24}, {0,  4,  8, 12, 16, 20}},
  {{aggregation_level::n1, 7, 24}, {0,  3,  6, 10, 13, 17, 20}},
  {{aggregation_level::n2, 7, 24}, {0,  2,  6, 10, 12, 16, 20}},
  {{aggregation_level::n1, 8, 24}, {0,  3,  6,  9, 12, 15, 18, 21}},
  {{aggregation_level::n2, 8, 24}, {0,  2,  6,  8, 12, 14, 18, 20}},
  {{aggregation_level::n1, 0, 48}, {}},
  {{aggregation_level::n1, 1, 48}, {0}},
  {{aggregation_level::n2, 1, 48}, {0}},
  {{aggregation_level::n4, 1, 48}, {0}},
  {{aggregation_level::n8, 1, 48}, {0}},
  {{aggregation_level::n16, 1, 48}, {0}},
  {{aggregation_level::n1, 2, 48}, {0, 24}},
  {{aggregation_level::n2, 2, 48}, {0, 24}},
  {{aggregation_level::n4, 2, 48}, {0, 24}},
  {{aggregation_level::n8, 2, 48}, {0, 24}},
  {{aggregation_level::n16, 2, 48}, {0, 16}},
  {{aggregation_level::n1, 3, 48}, {0, 16, 32}},
  {{aggregation_level::n2, 3, 48}, {0, 16, 32}},
  {{aggregation_level::n4, 3, 48}, {0, 16, 32}},
  {{aggregation_level::n8, 3, 48}, {0, 16, 32}},
  {{aggregation_level::n16, 3, 48}, {0, 16, 32}},
  {{aggregation_level::n1, 4, 48}, {0, 12, 24, 36}},
  {{aggregation_level::n2, 4, 48}, {0, 12, 24, 36}},
  {{aggregation_level::n4, 4, 48}, {0, 12, 24, 36}},
  {{aggregation_level::n8, 4, 48}, {0,  8, 24, 32}},
  {{aggregation_level::n1, 5, 48}, {0,  9, 19, 28, 38}},
  {{aggregation_level::n2, 5, 48}, {0,  8, 18, 28, 38}},
  {{aggregation_level::n4, 5, 48}, {0,  8, 16, 28, 36}},
  {{aggregation_level::n8, 5, 48}, {0,  8, 16, 24, 32}},
  {{aggregation_level::n1, 6, 48}, {0,  8, 16, 24, 32, 40}},
  {{aggregation_level::n2, 6, 48}, {0,  8, 16, 24, 32, 40}},
  {{aggregation_level::n4, 6, 48}, {0,  8, 16, 24, 32, 40}},
  {{aggregation_level::n8, 6, 48}, {0,  8, 16, 24, 32, 40}},
  {{aggregation_level::n1, 7, 48}, {0,  6, 13, 20, 27, 34, 41}},
  {{aggregation_level::n2, 7, 48}, {0,  6, 12, 20, 26, 34, 40}},
  {{aggregation_level::n4, 7, 48}, {0,  4, 12, 20, 24, 32, 40}},
  {{aggregation_level::n1, 8, 48}, {0,  6, 12, 18, 24, 30, 36, 42}},
  {{aggregation_level::n2, 8, 48}, {0,  6, 12, 18, 24, 30, 36, 42}},
  {{aggregation_level::n4, 8, 48}, {0,  4, 12, 16, 24, 28, 36, 40}},
  {{aggregation_level::n1, 0, 72}, {}},
  {{aggregation_level::n1, 1, 72}, {0}},
  {{aggregation_level::n2, 1, 72}, {0}},
  {{aggregation_level::n4, 1, 72}, {0}},
  {{aggregation_level::n8, 1, 72}, {0}},
  {{aggregation_level::n16, 1, 72}, {0}},
  {{aggregation_level::n1, 2, 72}, {0, 36}},
  {{aggregation_level::n2, 2, 72}, {0, 36}},
  {{aggregation_level::n4, 2, 72}, {0, 36}},
  {{aggregation_level::n8, 2, 72}, {0, 32}},
  {{aggregation_level::n16, 2, 72}, {0, 32}},
  {{aggregation_level::n1, 3, 72}, {0, 24, 48}},
  {{aggregation_level::n2, 3, 72}, {0, 24, 48}},
  {{aggregation_level::n4, 3, 72}, {0, 24, 48}},
  {{aggregation_level::n8, 3, 72}, {0, 24, 48}},
  {{aggregation_level::n16, 3, 72}, {0, 16, 48}},
  {{aggregation_level::n1, 4, 72}, {0, 18, 36, 54}},
  {{aggregation_level::n2, 4, 72}, {0, 18, 36, 54}},
  {{aggregation_level::n4, 4, 72}, {0, 16, 36, 52}},
  {{aggregation_level::n8, 4, 72}, {0, 16, 32, 48}},
  {{aggregation_level::n16, 4, 72}, {0, 16, 32, 48}},
  {{aggregation_level::n1, 5, 72}, {0, 14, 28, 43, 57}},
  {{aggregation_level::n2, 5, 72}, {0, 14, 28, 42, 56}},
  {{aggregation_level::n4, 5, 72}, {0, 12, 28, 40, 56}},
  {{aggregation_level::n8, 5, 72}, {0,  8, 24, 40, 56}},
  {{aggregation_level::n1, 6, 72}, {0, 12, 24, 36, 48, 60}},
  {{aggregation_level::n2, 6, 72}, {0, 12, 24, 36, 48, 60}},
  {{aggregation_level::n4, 6, 72}, {0, 12, 24, 36, 48, 60}},
  {{aggregation_level::n8, 6, 72}, {0,  8, 24, 32, 48, 56}},
  {{aggregation_level::n1, 7, 72}, {0, 10, 20, 30, 41, 51, 61}},
  {{aggregation_level::n2, 7, 72}, {0, 10, 20, 30, 40, 50, 60}},
  {{aggregation_level::n4, 7, 72}, {0,  8, 20, 28, 40, 48, 60}},
  {{aggregation_level::n8, 7, 72}, {0,  8, 16, 24, 40, 48, 56}},
  {{aggregation_level::n1, 8, 72}, {0,  9, 18, 27, 36, 45, 54, 63}},
  {{aggregation_level::n2, 8, 72}, {0,  8, 18, 26, 36, 44, 54, 62}},
  {{aggregation_level::n4, 8, 72}, {0,  8, 16, 24, 36, 44, 52, 60}},
  {{aggregation_level::n8, 8, 72}, {0,  8, 16, 24, 32, 40, 48, 56}},
  {{aggregation_level::n1, 0, 96}, {}},
  {{aggregation_level::n1, 1, 96}, {0}},
  {{aggregation_level::n2, 1, 96}, {0}},
  {{aggregation_level::n4, 1, 96}, {0}},
  {{aggregation_level::n8, 1, 96}, {0}},
  {{aggregation_level::n16, 1, 96}, {0}},
  {{aggregation_level::n1, 2, 96}, {0, 48}},
  {{aggregation_level::n2, 2, 96}, {0, 48}},
  {{aggregation_level::n4, 2, 96}, {0, 48}},
  {{aggregation_level::n8, 2, 96}, {0, 48}},
  {{aggregation_level::n16, 2, 96}, {0, 48}},
  {{aggregation_level::n1, 3, 96}, {0, 32, 64}},
  {{aggregation_level::n2, 3, 96}, {0, 32, 64}},
  {{aggregation_level::n4, 3, 96}, {0, 32, 64}},
  {{aggregation_level::n8, 3, 96}, {0, 32, 64}},
  {{aggregation_level::n16, 3, 96}, {0, 32, 64}},
  {{aggregation_level::n1, 4, 96}, {0, 24, 48, 72}},
  {{aggregation_level::n2, 4, 96}, {0, 24, 48, 72}},
  {{aggregation_level::n4, 4, 96}, {0, 24, 48, 72}},
  {{aggregation_level::n8, 4, 96}, {0, 24, 48, 72}},
  {{aggregation_level::n16, 4, 96}, {0, 16, 48, 64}},
  {{aggregation_level::n1, 5, 96}, {0, 19, 38, 57, 76}},
  {{aggregation_level::n2, 5, 96}, {0, 18, 38, 56, 76}},
  {{aggregation_level::n4, 5, 96}, {0, 16, 36, 56, 76}},
  {{aggregation_level::n8, 5, 96}, {0, 16, 32, 56, 72}},
  {{aggregation_level::n16, 5, 96}, {0, 16, 32, 48, 64}},
  {{aggregation_level::n1, 6, 96}, {0, 16, 32, 48, 64, 80}},
  {{aggregation_level::n2, 6, 96}, {0, 16, 32, 48, 64, 80}},
  {{aggregation_level::n4, 6, 96}, {0, 16, 32, 48, 64, 80}},
  {{aggregation_level::n8, 6, 96}, {0, 16, 32, 48, 64, 80}},
  {{aggregation_level::n16, 6, 96}, {0, 16, 32, 48, 64, 80}},
  {{aggregation_level::n1, 7, 96}, {0, 13, 27, 41, 54, 68, 82}},
  {{aggregation_level::n2, 7, 96}, {0, 12, 26, 40, 54, 68, 82}},
  {{aggregation_level::n4, 7, 96}, {0, 12, 24, 40, 52, 68, 80}},
  {{aggregation_level::n8, 7, 96}, {0,  8, 24, 40, 48, 64, 80}},
  {{aggregation_level::n1, 8, 96}, {0, 12, 24, 36, 48, 60, 72, 84}},
  {{aggregation_level::n2, 8, 96}, {0, 12, 24, 36, 48, 60, 72, 84}},
  {{aggregation_level::n4, 8, 96}, {0, 12, 24, 36, 48, 60, 72, 84}},
  {{aggregation_level::n8, 8, 96}, {0,  8, 24, 32, 48, 56, 72, 80}},
  {{aggregation_level::n1, 0, 120}, {}},
  {{aggregation_level::n1, 1, 120}, {0}},
  {{aggregation_level::n2, 1, 120}, {0}},
  {{aggregation_level::n4, 1, 120}, {0}},
  {{aggregation_level::n8, 1, 120}, {0}},
  {{aggregation_level::n16, 1, 120}, {0}},
  {{aggregation_level::n1, 2, 120}, {0, 60}},
  {{aggregation_level::n2, 2, 120}, {0, 60}},
  {{aggregation_level::n4, 2, 120}, {0, 60}},
  {{aggregation_level::n8, 2, 120}, {0, 56}},
  {{aggregation_level::n16, 2, 120}, {0, 48}},
  {{aggregation_level::n1, 3, 120}, {0, 40, 80}},
  {{aggregation_level::n2, 3, 120}, {0, 40, 80}},
  {{aggregation_level::n4, 3, 120}, {0, 40, 80}},
  {{aggregation_level::n8, 3, 120}, {0, 40, 80}},
  {{aggregation_level::n16, 3, 120}, {0, 32, 80}},
  {{aggregation_level::n1, 4, 120}, {0, 30, 60, 90}},
  {{aggregation_level::n2, 4, 120}, {0, 30, 60, 90}},
  {{aggregation_level::n4, 4, 120}, {0, 28, 60, 88}},
  {{aggregation_level::n8, 4, 120}, {0, 24, 56, 88}},
  {{aggregation_level::n16, 4, 120}, {0, 16, 48, 80}},
  {{aggregation_level::n1, 5, 120}, {0, 24, 48, 72, 96}},
  {{aggregation_level::n2, 5, 120}, {0, 24, 48, 72, 96}},
  {{aggregation_level::n4, 5, 120}, {0, 24, 48, 72, 96}},
  {{aggregation_level::n8, 5, 120}, {0, 24, 48, 72, 96}},
  {{aggregation_level::n16, 5, 120}, {0, 16, 48, 64, 96}},
  {{aggregation_level::n1, 6, 120}, {0, 20, 40, 60, 80, 100}},
  {{aggregation_level::n2, 6, 120}, {0, 20, 40, 60, 80, 100}},
  {{aggregation_level::n4, 6, 120}, {0, 20, 40, 60, 80, 100}},
  {{aggregation_level::n8, 6, 120}, {0, 16, 40, 56, 80, 96}},
  {{aggregation_level::n16, 6, 120}, {0, 16, 32, 48, 80, 96}},
  {{aggregation_level::n1, 7, 120}, {0, 17, 34, 51, 68, 85, 102}},
  {{aggregation_level::n2, 7, 120}, {0, 16, 34, 50, 68, 84, 102}},
  {{aggregation_level::n4, 7, 120}, {0, 16, 32, 48, 68, 84, 100}},
  {{aggregation_level::n8, 7, 120}, {0, 16, 32, 48, 64, 80, 96}},
  {{aggregation_level::n16, 7, 120}, {0, 16, 32, 48, 64, 80, 96}},
  {{aggregation_level::n1, 8, 120}, {0, 15, 30, 45, 60, 75, 90, 105}},
  {{aggregation_level::n2, 8, 120}, {0, 14, 30, 44, 60, 74, 90, 104}},
  {{aggregation_level::n4, 8, 120}, {0, 12, 28, 44, 60, 72, 88, 104}},
  {{aggregation_level::n8, 8, 120}, {0,  8, 24, 40, 56, 72, 88, 104}},
  {{aggregation_level::n1, 0, 144}, {}},
  {{aggregation_level::n1, 1, 144}, {0}},
  {{aggregation_level::n2, 1, 144}, {0}},
  {{aggregation_level::n4, 1, 144}, {0}},
  {{aggregation_level::n8, 1, 144}, {0}},
  {{aggregation_level::n16, 1, 144}, {0}},
  {{aggregation_level::n1, 2, 144}, {0, 72}},
  {{aggregation_level::n2, 2, 144}, {0, 72}},
  {{aggregation_level::n4, 2, 144}, {0, 72}},
  {{aggregation_level::n8, 2, 144}, {0, 72}},
  {{aggregation_level::n16, 2, 144}, {0, 64}},
  {{aggregation_level::n1, 3, 144}, {0, 48, 96}},
  {{aggregation_level::n2, 3, 144}, {0, 48, 96}},
  {{aggregation_level::n4, 3, 144}, {0, 48, 96}},
  {{aggregation_level::n8, 3, 144}, {0, 48, 96}},
  {{aggregation_level::n16, 3, 144}, {0, 48, 96}},
  {{aggregation_level::n1, 4, 144}, {0, 36, 72, 108}},
  {{aggregation_level::n2, 4, 144}, {0, 36, 72, 108}},
  {{aggregation_level::n4, 4, 144}, {0, 36, 72, 108}},
  {{aggregation_level::n8, 4, 144}, {0, 32, 72, 104}},
  {{aggregation_level::n16, 4, 144}, {0, 32, 64, 96}},
  {{aggregation_level::n1, 5, 144}, {0, 28, 57, 86, 115}},
  {{aggregation_level::n2, 5, 144}, {0, 28, 56, 86, 114}},
  {{aggregation_level::n4, 5, 144}, {0, 28, 56, 84, 112}},
  {{aggregation_level::n8, 5, 144}, {0, 24, 56, 80, 112}},
  {{aggregation_level::n16, 5, 144}, {0, 16, 48, 80, 112}},
  {{aggregation_level::n1, 6, 144}, {0, 24, 48, 72, 96, 120}},
  {{aggregation_level::n2, 6, 144}, {0, 24, 48, 72, 96, 120}},
  {{aggregation_level::n4, 6, 144}, {0, 24, 48, 72, 96, 120}},
  {{aggregation_level::n8, 6, 144}, {0, 24, 48, 72, 96, 120}},
  {{aggregation_level::n16, 6, 144}, {0, 16, 48, 64, 96, 112}},
  {{aggregation_level::n1, 7, 144}, {0,  20,  41,  61,  82, 102, 123}},
  {{aggregation_level::n2, 7, 144}, {0,  20,  40,  60,  82, 102, 122}},
  {{aggregation_level::n4, 7, 144}, {0,  20,  40,  60,  80, 100, 120}},
  {{aggregation_level::n8, 7, 144}, {0, 16, 40, 56, 80, 96, 120}},
  {{aggregation_level::n16, 7, 144}, {0, 16, 32, 48, 80, 96, 112}},
  {{aggregation_level::n1, 8, 144}, {0,  18,  36,  54,  72,  90, 108, 126}},
  {{aggregation_level::n2, 8, 144}, {0,  18,  36,  54,  72,  90, 108, 126}},
  {{aggregation_level::n4, 8, 144}, {0,  16,  36,  52,  72,  88, 108, 124}},
  {{aggregation_level::n8, 8, 144}, {0,  16,  32,  48,  72,  88, 104, 120}},
  {{aggregation_level::n16, 8, 144}, {0, 16, 32, 48, 64, 80, 96, 112}},
    // clang-format on
};

} // namespace srsran
