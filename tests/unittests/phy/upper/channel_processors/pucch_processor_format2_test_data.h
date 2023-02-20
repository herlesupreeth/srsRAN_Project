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

// This file was generated using the following MATLAB class on 10-02-2023:
//   + "srsPUCCHProcessorFormat2Unittest.m"

#include "../../support/resource_grid_test_doubles.h"
#include "srsran/phy/upper/channel_processors/pucch_processor.h"
#include "srsran/support/file_vector.h"

namespace srsran {

struct context_t {
  unsigned                               grid_nof_prb;
  unsigned                               grid_nof_symbols;
  pucch_processor::format2_configuration config;
};

struct test_case_t {
  context_t                                               context;
  file_vector<resource_grid_reader_spy::expected_entry_t> grid;
  file_vector<uint8_t>                                    harq_ack;
  file_vector<uint8_t>                                    sr;
  file_vector<uint8_t>                                    csi_part_1;
  file_vector<uint8_t>                                    csi_part_2;
};

static const std::vector<test_case_t> pucch_processor_format2_test_data = {
    // clang-format off
  {{105, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 70, 35, 5, {}, 3, 0, 1, 44852, 545, 13903, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols0.dat"}, {"test_data/pucch_processor_format2_test_harq0.dat"}, {"test_data/pucch_processor_format2_test_sr0.dat"}, {"test_data/pucch_processor_format2_test_csi10.dat"}, {"test_data/pucch_processor_format2_test_csi20.dat"}},
  {{253, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 48, 205, 19, {}, 2, 0, 1, 29435, 235, 51002, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols1.dat"}, {"test_data/pucch_processor_format2_test_harq1.dat"}, {"test_data/pucch_processor_format2_test_sr1.dat"}, {"test_data/pucch_processor_format2_test_csi11.dat"}, {"test_data/pucch_processor_format2_test_csi21.dat"}},
  {{193, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 66, 127, 51, {}, 1, 0, 1, 30143, 753, 54309, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols2.dat"}, {"test_data/pucch_processor_format2_test_harq2.dat"}, {"test_data/pucch_processor_format2_test_sr2.dat"}, {"test_data/pucch_processor_format2_test_csi12.dat"}, {"test_data/pucch_processor_format2_test_csi22.dat"}},
  {{171, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 87, 84, 4, {}, 1, 0, 1, 65245, 970, 46121, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols3.dat"}, {"test_data/pucch_processor_format2_test_harq3.dat"}, {"test_data/pucch_processor_format2_test_sr3.dat"}, {"test_data/pucch_processor_format2_test_csi13.dat"}, {"test_data/pucch_processor_format2_test_csi23.dat"}},
  {{258, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 75, 183, 4, {}, 1, 0, 1, 19194, 757, 57101, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols4.dat"}, {"test_data/pucch_processor_format2_test_harq4.dat"}, {"test_data/pucch_processor_format2_test_sr4.dat"}, {"test_data/pucch_processor_format2_test_csi14.dat"}, {"test_data/pucch_processor_format2_test_csi24.dat"}},
  {{275, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 7, 268, 0, {}, 1, 0, 1, 31911, 155, 22470, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols5.dat"}, {"test_data/pucch_processor_format2_test_harq5.dat"}, {"test_data/pucch_processor_format2_test_sr5.dat"}, {"test_data/pucch_processor_format2_test_csi15.dat"}, {"test_data/pucch_processor_format2_test_csi25.dat"}},
  {{232, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 10, 222, 3, {}, 6, 0, 1, 44020, 809, 61782, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols6.dat"}, {"test_data/pucch_processor_format2_test_harq6.dat"}, {"test_data/pucch_processor_format2_test_sr6.dat"}, {"test_data/pucch_processor_format2_test_csi16.dat"}, {"test_data/pucch_processor_format2_test_csi26.dat"}},
  {{74, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 71, 3, 43, {}, 3, 0, 1, 45235, 293, 28426, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols7.dat"}, {"test_data/pucch_processor_format2_test_harq7.dat"}, {"test_data/pucch_processor_format2_test_sr7.dat"}, {"test_data/pucch_processor_format2_test_csi17.dat"}, {"test_data/pucch_processor_format2_test_csi27.dat"}},
  {{128, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 10, 118, 4, {}, 2, 0, 1, 54367, 796, 6021, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols8.dat"}, {"test_data/pucch_processor_format2_test_harq8.dat"}, {"test_data/pucch_processor_format2_test_sr8.dat"}, {"test_data/pucch_processor_format2_test_csi18.dat"}, {"test_data/pucch_processor_format2_test_csi28.dat"}},
  {{230, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 196, 34, 14, {}, 2, 0, 1, 31805, 642, 41737, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols9.dat"}, {"test_data/pucch_processor_format2_test_harq9.dat"}, {"test_data/pucch_processor_format2_test_sr9.dat"}, {"test_data/pucch_processor_format2_test_csi19.dat"}, {"test_data/pucch_processor_format2_test_csi29.dat"}},
  {{86, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 19, 67, 0, {}, 1, 0, 1, 54100, 327, 17199, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols10.dat"}, {"test_data/pucch_processor_format2_test_harq10.dat"}, {"test_data/pucch_processor_format2_test_sr10.dat"}, {"test_data/pucch_processor_format2_test_csi110.dat"}, {"test_data/pucch_processor_format2_test_csi210.dat"}},
  {{199, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 76, 123, 34, {}, 1, 0, 1, 43263, 540, 37842, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols11.dat"}, {"test_data/pucch_processor_format2_test_harq11.dat"}, {"test_data/pucch_processor_format2_test_sr11.dat"}, {"test_data/pucch_processor_format2_test_csi111.dat"}, {"test_data/pucch_processor_format2_test_csi211.dat"}},
  {{246, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 48, 198, 39, {}, 4, 0, 1, 58253, 598, 30342, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols12.dat"}, {"test_data/pucch_processor_format2_test_harq12.dat"}, {"test_data/pucch_processor_format2_test_sr12.dat"}, {"test_data/pucch_processor_format2_test_csi112.dat"}, {"test_data/pucch_processor_format2_test_csi212.dat"}},
  {{242, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 40, 202, 7, {}, 2, 0, 1, 28444, 157, 62427, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols13.dat"}, {"test_data/pucch_processor_format2_test_harq13.dat"}, {"test_data/pucch_processor_format2_test_sr13.dat"}, {"test_data/pucch_processor_format2_test_csi113.dat"}, {"test_data/pucch_processor_format2_test_csi213.dat"}},
  {{239, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 91, 148, 59, {}, 1, 0, 1, 16238, 253, 34562, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols14.dat"}, {"test_data/pucch_processor_format2_test_harq14.dat"}, {"test_data/pucch_processor_format2_test_sr14.dat"}, {"test_data/pucch_processor_format2_test_csi114.dat"}, {"test_data/pucch_processor_format2_test_csi214.dat"}},
  {{177, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 30, 147, 17, {}, 1, 0, 1, 16651, 665, 2439, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols15.dat"}, {"test_data/pucch_processor_format2_test_harq15.dat"}, {"test_data/pucch_processor_format2_test_sr15.dat"}, {"test_data/pucch_processor_format2_test_csi115.dat"}, {"test_data/pucch_processor_format2_test_csi215.dat"}},
  {{245, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 6, 239, 0, {}, 1, 0, 1, 53348, 258, 64506, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols16.dat"}, {"test_data/pucch_processor_format2_test_harq16.dat"}, {"test_data/pucch_processor_format2_test_sr16.dat"}, {"test_data/pucch_processor_format2_test_csi116.dat"}, {"test_data/pucch_processor_format2_test_csi216.dat"}},
  {{126, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 95, 31, 84, {}, 1, 0, 1, 56449, 80, 33254, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols17.dat"}, {"test_data/pucch_processor_format2_test_harq17.dat"}, {"test_data/pucch_processor_format2_test_sr17.dat"}, {"test_data/pucch_processor_format2_test_csi117.dat"}, {"test_data/pucch_processor_format2_test_csi217.dat"}},
  {{242, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 140, 102, 28, {}, 7, 0, 1, 48381, 277, 23940, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols18.dat"}, {"test_data/pucch_processor_format2_test_harq18.dat"}, {"test_data/pucch_processor_format2_test_sr18.dat"}, {"test_data/pucch_processor_format2_test_csi118.dat"}, {"test_data/pucch_processor_format2_test_csi218.dat"}},
  {{267, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 71, 196, 11, {}, 4, 0, 1, 61941, 80, 56791, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols19.dat"}, {"test_data/pucch_processor_format2_test_harq19.dat"}, {"test_data/pucch_processor_format2_test_sr19.dat"}, {"test_data/pucch_processor_format2_test_csi119.dat"}, {"test_data/pucch_processor_format2_test_csi219.dat"}},
  {{238, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 41, 197, 36, {}, 2, 0, 1, 33414, 413, 14418, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols20.dat"}, {"test_data/pucch_processor_format2_test_harq20.dat"}, {"test_data/pucch_processor_format2_test_sr20.dat"}, {"test_data/pucch_processor_format2_test_csi120.dat"}, {"test_data/pucch_processor_format2_test_csi220.dat"}},
  {{149, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 9, 140, 2, {}, 2, 0, 1, 36780, 320, 41346, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols21.dat"}, {"test_data/pucch_processor_format2_test_harq21.dat"}, {"test_data/pucch_processor_format2_test_sr21.dat"}, {"test_data/pucch_processor_format2_test_csi121.dat"}, {"test_data/pucch_processor_format2_test_csi221.dat"}},
  {{164, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 48, 116, 17, {}, 2, 0, 1, 16470, 910, 35422, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols22.dat"}, {"test_data/pucch_processor_format2_test_harq22.dat"}, {"test_data/pucch_processor_format2_test_sr22.dat"}, {"test_data/pucch_processor_format2_test_csi122.dat"}, {"test_data/pucch_processor_format2_test_csi222.dat"}},
  {{269, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 152, 117, 125, {}, 1, 0, 1, 14798, 111, 25329, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols23.dat"}, {"test_data/pucch_processor_format2_test_harq23.dat"}, {"test_data/pucch_processor_format2_test_sr23.dat"}, {"test_data/pucch_processor_format2_test_csi123.dat"}, {"test_data/pucch_processor_format2_test_csi223.dat"}},
  {{86, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 72, 14, 29, {}, 5, 0, 1, 35549, 824, 8835, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols24.dat"}, {"test_data/pucch_processor_format2_test_harq24.dat"}, {"test_data/pucch_processor_format2_test_sr24.dat"}, {"test_data/pucch_processor_format2_test_csi124.dat"}, {"test_data/pucch_processor_format2_test_csi224.dat"}},
  {{149, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 135, 14, 35, {}, 3, 0, 1, 21416, 341, 64211, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols25.dat"}, {"test_data/pucch_processor_format2_test_harq25.dat"}, {"test_data/pucch_processor_format2_test_sr25.dat"}, {"test_data/pucch_processor_format2_test_csi125.dat"}, {"test_data/pucch_processor_format2_test_csi225.dat"}},
  {{92, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 43, 49, 12, {}, 2, 0, 1, 47263, 37, 19842, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols26.dat"}, {"test_data/pucch_processor_format2_test_harq26.dat"}, {"test_data/pucch_processor_format2_test_sr26.dat"}, {"test_data/pucch_processor_format2_test_csi126.dat"}, {"test_data/pucch_processor_format2_test_csi226.dat"}},
  {{274, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 2, 272, 0, {}, 2, 0, 1, 18596, 47, 38943, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols27.dat"}, {"test_data/pucch_processor_format2_test_harq27.dat"}, {"test_data/pucch_processor_format2_test_sr27.dat"}, {"test_data/pucch_processor_format2_test_csi127.dat"}, {"test_data/pucch_processor_format2_test_csi227.dat"}},
  {{270, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 3, 267, 1, {}, 1, 0, 1, 24261, 826, 60434, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols28.dat"}, {"test_data/pucch_processor_format2_test_harq28.dat"}, {"test_data/pucch_processor_format2_test_sr28.dat"}, {"test_data/pucch_processor_format2_test_csi128.dat"}, {"test_data/pucch_processor_format2_test_csi228.dat"}},
  {{254, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 90, 164, 75, {}, 1, 0, 1, 106, 377, 63220, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols29.dat"}, {"test_data/pucch_processor_format2_test_harq29.dat"}, {"test_data/pucch_processor_format2_test_sr29.dat"}, {"test_data/pucch_processor_format2_test_csi129.dat"}, {"test_data/pucch_processor_format2_test_csi229.dat"}},
  {{251, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 191, 60, 110, {}, 8, 0, 1, 2279, 1017, 53656, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols30.dat"}, {"test_data/pucch_processor_format2_test_harq30.dat"}, {"test_data/pucch_processor_format2_test_sr30.dat"}, {"test_data/pucch_processor_format2_test_csi130.dat"}, {"test_data/pucch_processor_format2_test_csi230.dat"}},
  {{257, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 28, 229, 23, {}, 5, 0, 1, 43992, 390, 45683, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols31.dat"}, {"test_data/pucch_processor_format2_test_harq31.dat"}, {"test_data/pucch_processor_format2_test_sr31.dat"}, {"test_data/pucch_processor_format2_test_csi131.dat"}, {"test_data/pucch_processor_format2_test_csi231.dat"}},
  {{219, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 217, 2, 15, {}, 3, 0, 1, 57115, 56, 39779, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols32.dat"}, {"test_data/pucch_processor_format2_test_harq32.dat"}, {"test_data/pucch_processor_format2_test_sr32.dat"}, {"test_data/pucch_processor_format2_test_csi132.dat"}, {"test_data/pucch_processor_format2_test_csi232.dat"}},
  {{274, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 253, 21, 54, {}, 2, 0, 1, 18287, 80, 55957, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols33.dat"}, {"test_data/pucch_processor_format2_test_harq33.dat"}, {"test_data/pucch_processor_format2_test_sr33.dat"}, {"test_data/pucch_processor_format2_test_csi133.dat"}, {"test_data/pucch_processor_format2_test_csi233.dat"}},
  {{253, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 151, 102, 55, {}, 2, 0, 1, 27985, 681, 2985, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols34.dat"}, {"test_data/pucch_processor_format2_test_harq34.dat"}, {"test_data/pucch_processor_format2_test_sr34.dat"}, {"test_data/pucch_processor_format2_test_csi134.dat"}, {"test_data/pucch_processor_format2_test_csi234.dat"}},
  {{269, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 82, 187, 3, {}, 2, 0, 1, 19863, 22, 56473, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols35.dat"}, {"test_data/pucch_processor_format2_test_harq35.dat"}, {"test_data/pucch_processor_format2_test_sr35.dat"}, {"test_data/pucch_processor_format2_test_csi135.dat"}, {"test_data/pucch_processor_format2_test_csi235.dat"}},
  {{213, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 53, 160, 9, {}, 6, 0, 1, 12874, 488, 29343, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols36.dat"}, {"test_data/pucch_processor_format2_test_harq36.dat"}, {"test_data/pucch_processor_format2_test_sr36.dat"}, {"test_data/pucch_processor_format2_test_csi136.dat"}, {"test_data/pucch_processor_format2_test_csi236.dat"}},
  {{260, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 176, 84, 148, {}, 3, 0, 1, 16253, 813, 23566, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols37.dat"}, {"test_data/pucch_processor_format2_test_harq37.dat"}, {"test_data/pucch_processor_format2_test_sr37.dat"}, {"test_data/pucch_processor_format2_test_csi137.dat"}, {"test_data/pucch_processor_format2_test_csi237.dat"}},
  {{249, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 115, 134, 58, {}, 2, 0, 1, 19371, 719, 63855, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols38.dat"}, {"test_data/pucch_processor_format2_test_harq38.dat"}, {"test_data/pucch_processor_format2_test_sr38.dat"}, {"test_data/pucch_processor_format2_test_csi138.dat"}, {"test_data/pucch_processor_format2_test_csi238.dat"}},
  {{254, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 229, 25, 63, {}, 2, 0, 1, 47827, 140, 14393, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols39.dat"}, {"test_data/pucch_processor_format2_test_harq39.dat"}, {"test_data/pucch_processor_format2_test_sr39.dat"}, {"test_data/pucch_processor_format2_test_csi139.dat"}, {"test_data/pucch_processor_format2_test_csi239.dat"}},
  {{274, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 3, 271, 0, {}, 1, 0, 1, 4879, 782, 2124, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols40.dat"}, {"test_data/pucch_processor_format2_test_harq40.dat"}, {"test_data/pucch_processor_format2_test_sr40.dat"}, {"test_data/pucch_processor_format2_test_csi140.dat"}, {"test_data/pucch_processor_format2_test_csi240.dat"}},
  {{269, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 156, 113, 34, {}, 1, 0, 1, 61590, 671, 17505, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols41.dat"}, {"test_data/pucch_processor_format2_test_harq41.dat"}, {"test_data/pucch_processor_format2_test_sr41.dat"}, {"test_data/pucch_processor_format2_test_csi141.dat"}, {"test_data/pucch_processor_format2_test_csi241.dat"}},
  {{211, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 53, 158, 15, {}, 9, 0, 1, 50428, 931, 53033, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols42.dat"}, {"test_data/pucch_processor_format2_test_harq42.dat"}, {"test_data/pucch_processor_format2_test_sr42.dat"}, {"test_data/pucch_processor_format2_test_csi142.dat"}, {"test_data/pucch_processor_format2_test_csi242.dat"}},
  {{246, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 64, 182, 45, {}, 5, 0, 1, 47392, 58, 14684, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols43.dat"}, {"test_data/pucch_processor_format2_test_harq43.dat"}, {"test_data/pucch_processor_format2_test_sr43.dat"}, {"test_data/pucch_processor_format2_test_csi143.dat"}, {"test_data/pucch_processor_format2_test_csi243.dat"}},
  {{97, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 71, 26, 8, {}, 3, 0, 1, 13453, 453, 8117, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols44.dat"}, {"test_data/pucch_processor_format2_test_harq44.dat"}, {"test_data/pucch_processor_format2_test_sr44.dat"}, {"test_data/pucch_processor_format2_test_csi144.dat"}, {"test_data/pucch_processor_format2_test_csi244.dat"}},
  {{183, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 20, 163, 7, {}, 2, 0, 1, 9315, 741, 1620, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols45.dat"}, {"test_data/pucch_processor_format2_test_harq45.dat"}, {"test_data/pucch_processor_format2_test_sr45.dat"}, {"test_data/pucch_processor_format2_test_csi145.dat"}, {"test_data/pucch_processor_format2_test_csi245.dat"}},
  {{163, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 102, 61, 91, {}, 2, 0, 1, 23295, 602, 38403, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols46.dat"}, {"test_data/pucch_processor_format2_test_harq46.dat"}, {"test_data/pucch_processor_format2_test_sr46.dat"}, {"test_data/pucch_processor_format2_test_csi146.dat"}, {"test_data/pucch_processor_format2_test_csi246.dat"}},
  {{239, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 128, 111, 78, {}, 2, 0, 1, 4207, 742, 34498, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols47.dat"}, {"test_data/pucch_processor_format2_test_harq47.dat"}, {"test_data/pucch_processor_format2_test_sr47.dat"}, {"test_data/pucch_processor_format2_test_csi147.dat"}, {"test_data/pucch_processor_format2_test_csi247.dat"}},
  {{274, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 5, 269, 3, {}, 2, 12, 2, 4330, 656, 43120, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols48.dat"}, {"test_data/pucch_processor_format2_test_harq48.dat"}, {"test_data/pucch_processor_format2_test_sr48.dat"}, {"test_data/pucch_processor_format2_test_csi148.dat"}, {"test_data/pucch_processor_format2_test_csi248.dat"}},
  {{213, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 14, 199, 0, {}, 1, 12, 2, 34116, 872, 6037, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols49.dat"}, {"test_data/pucch_processor_format2_test_harq49.dat"}, {"test_data/pucch_processor_format2_test_sr49.dat"}, {"test_data/pucch_processor_format2_test_csi149.dat"}, {"test_data/pucch_processor_format2_test_csi249.dat"}},
  {{190, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 1, 189, 0, {}, 1, 12, 2, 5820, 201, 23132, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols50.dat"}, {"test_data/pucch_processor_format2_test_harq50.dat"}, {"test_data/pucch_processor_format2_test_sr50.dat"}, {"test_data/pucch_processor_format2_test_csi150.dat"}, {"test_data/pucch_processor_format2_test_csi250.dat"}},
  {{162, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 155, 7, 75, {}, 1, 12, 2, 6593, 169, 24704, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols51.dat"}, {"test_data/pucch_processor_format2_test_harq51.dat"}, {"test_data/pucch_processor_format2_test_sr51.dat"}, {"test_data/pucch_processor_format2_test_csi151.dat"}, {"test_data/pucch_processor_format2_test_csi251.dat"}},
  {{266, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 49, 217, 35, {}, 1, 12, 2, 28613, 255, 9645, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols52.dat"}, {"test_data/pucch_processor_format2_test_harq52.dat"}, {"test_data/pucch_processor_format2_test_sr52.dat"}, {"test_data/pucch_processor_format2_test_csi152.dat"}, {"test_data/pucch_processor_format2_test_csi252.dat"}},
  {{246, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 5, 241, 0, {}, 1, 12, 2, 38405, 332, 41193, 3, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols53.dat"}, {"test_data/pucch_processor_format2_test_harq53.dat"}, {"test_data/pucch_processor_format2_test_sr53.dat"}, {"test_data/pucch_processor_format2_test_csi153.dat"}, {"test_data/pucch_processor_format2_test_csi253.dat"}},
  {{226, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 55, 171, 17, {}, 3, 12, 2, 44979, 662, 20749, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols54.dat"}, {"test_data/pucch_processor_format2_test_harq54.dat"}, {"test_data/pucch_processor_format2_test_sr54.dat"}, {"test_data/pucch_processor_format2_test_csi154.dat"}, {"test_data/pucch_processor_format2_test_csi254.dat"}},
  {{164, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 160, 4, 113, {}, 2, 12, 2, 23874, 544, 3491, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols55.dat"}, {"test_data/pucch_processor_format2_test_harq55.dat"}, {"test_data/pucch_processor_format2_test_sr55.dat"}, {"test_data/pucch_processor_format2_test_csi155.dat"}, {"test_data/pucch_processor_format2_test_csi255.dat"}},
  {{250, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 35, 215, 19, {}, 1, 12, 2, 15424, 896, 45609, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols56.dat"}, {"test_data/pucch_processor_format2_test_harq56.dat"}, {"test_data/pucch_processor_format2_test_sr56.dat"}, {"test_data/pucch_processor_format2_test_csi156.dat"}, {"test_data/pucch_processor_format2_test_csi256.dat"}},
  {{274, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 4, 270, 1, {}, 1, 12, 2, 1063, 988, 14255, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols57.dat"}, {"test_data/pucch_processor_format2_test_harq57.dat"}, {"test_data/pucch_processor_format2_test_sr57.dat"}, {"test_data/pucch_processor_format2_test_csi157.dat"}, {"test_data/pucch_processor_format2_test_csi257.dat"}},
  {{223, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 14, 209, 2, {}, 1, 12, 2, 54338, 91, 40857, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols58.dat"}, {"test_data/pucch_processor_format2_test_harq58.dat"}, {"test_data/pucch_processor_format2_test_sr58.dat"}, {"test_data/pucch_processor_format2_test_csi158.dat"}, {"test_data/pucch_processor_format2_test_csi258.dat"}},
  {{148, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 49, 99, 6, {}, 1, 12, 2, 23409, 372, 33428, 3, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols59.dat"}, {"test_data/pucch_processor_format2_test_harq59.dat"}, {"test_data/pucch_processor_format2_test_sr59.dat"}, {"test_data/pucch_processor_format2_test_csi159.dat"}, {"test_data/pucch_processor_format2_test_csi259.dat"}},
  {{210, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 59, 151, 3, {}, 2, 12, 2, 7778, 73, 35503, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols60.dat"}, {"test_data/pucch_processor_format2_test_harq60.dat"}, {"test_data/pucch_processor_format2_test_sr60.dat"}, {"test_data/pucch_processor_format2_test_csi160.dat"}, {"test_data/pucch_processor_format2_test_csi260.dat"}},
  {{261, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 7, 254, 4, {}, 1, 12, 2, 46205, 678, 56217, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols61.dat"}, {"test_data/pucch_processor_format2_test_harq61.dat"}, {"test_data/pucch_processor_format2_test_sr61.dat"}, {"test_data/pucch_processor_format2_test_csi161.dat"}, {"test_data/pucch_processor_format2_test_csi261.dat"}},
  {{251, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 97, 154, 58, {}, 1, 12, 2, 55691, 593, 62598, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols62.dat"}, {"test_data/pucch_processor_format2_test_harq62.dat"}, {"test_data/pucch_processor_format2_test_sr62.dat"}, {"test_data/pucch_processor_format2_test_csi162.dat"}, {"test_data/pucch_processor_format2_test_csi262.dat"}},
  {{57, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 43, 14, 31, {}, 1, 12, 2, 63822, 404, 57303, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols63.dat"}, {"test_data/pucch_processor_format2_test_harq63.dat"}, {"test_data/pucch_processor_format2_test_sr63.dat"}, {"test_data/pucch_processor_format2_test_csi163.dat"}, {"test_data/pucch_processor_format2_test_csi263.dat"}},
  {{133, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 65, 68, 31, {}, 1, 12, 2, 20445, 13, 48316, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols64.dat"}, {"test_data/pucch_processor_format2_test_harq64.dat"}, {"test_data/pucch_processor_format2_test_sr64.dat"}, {"test_data/pucch_processor_format2_test_csi164.dat"}, {"test_data/pucch_processor_format2_test_csi264.dat"}},
  {{264, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 67, 197, 23, {}, 1, 12, 2, 58282, 770, 32257, 3, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols65.dat"}, {"test_data/pucch_processor_format2_test_harq65.dat"}, {"test_data/pucch_processor_format2_test_sr65.dat"}, {"test_data/pucch_processor_format2_test_csi165.dat"}, {"test_data/pucch_processor_format2_test_csi265.dat"}},
  {{243, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 175, 68, 58, {}, 4, 12, 2, 27354, 993, 59559, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols66.dat"}, {"test_data/pucch_processor_format2_test_harq66.dat"}, {"test_data/pucch_processor_format2_test_sr66.dat"}, {"test_data/pucch_processor_format2_test_csi166.dat"}, {"test_data/pucch_processor_format2_test_csi266.dat"}},
  {{224, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 14, 210, 6, {}, 2, 12, 2, 49682, 66, 38830, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols67.dat"}, {"test_data/pucch_processor_format2_test_harq67.dat"}, {"test_data/pucch_processor_format2_test_sr67.dat"}, {"test_data/pucch_processor_format2_test_csi167.dat"}, {"test_data/pucch_processor_format2_test_csi267.dat"}},
  {{177, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 73, 104, 30, {}, 1, 12, 2, 42205, 209, 22831, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols68.dat"}, {"test_data/pucch_processor_format2_test_harq68.dat"}, {"test_data/pucch_processor_format2_test_sr68.dat"}, {"test_data/pucch_processor_format2_test_csi168.dat"}, {"test_data/pucch_processor_format2_test_csi268.dat"}},
  {{242, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 132, 110, 18, {}, 1, 12, 2, 1894, 78, 61060, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols69.dat"}, {"test_data/pucch_processor_format2_test_harq69.dat"}, {"test_data/pucch_processor_format2_test_sr69.dat"}, {"test_data/pucch_processor_format2_test_csi169.dat"}, {"test_data/pucch_processor_format2_test_csi269.dat"}},
  {{227, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 112, 115, 2, {}, 1, 12, 2, 39948, 607, 35008, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols70.dat"}, {"test_data/pucch_processor_format2_test_harq70.dat"}, {"test_data/pucch_processor_format2_test_sr70.dat"}, {"test_data/pucch_processor_format2_test_csi170.dat"}, {"test_data/pucch_processor_format2_test_csi270.dat"}},
  {{201, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 148, 53, 130, {}, 1, 12, 2, 36880, 370, 41220, 3, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols71.dat"}, {"test_data/pucch_processor_format2_test_harq71.dat"}, {"test_data/pucch_processor_format2_test_sr71.dat"}, {"test_data/pucch_processor_format2_test_csi171.dat"}, {"test_data/pucch_processor_format2_test_csi271.dat"}},
  {{155, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 114, 41, 80, {}, 3, 12, 2, 17869, 643, 8302, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols72.dat"}, {"test_data/pucch_processor_format2_test_harq72.dat"}, {"test_data/pucch_processor_format2_test_sr72.dat"}, {"test_data/pucch_processor_format2_test_csi172.dat"}, {"test_data/pucch_processor_format2_test_csi272.dat"}},
  {{245, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 61, 184, 44, {}, 2, 12, 2, 40283, 683, 39739, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols73.dat"}, {"test_data/pucch_processor_format2_test_harq73.dat"}, {"test_data/pucch_processor_format2_test_sr73.dat"}, {"test_data/pucch_processor_format2_test_csi173.dat"}, {"test_data/pucch_processor_format2_test_csi273.dat"}},
  {{86, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 80, 6, 3, {}, 1, 12, 2, 11458, 266, 25679, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols74.dat"}, {"test_data/pucch_processor_format2_test_harq74.dat"}, {"test_data/pucch_processor_format2_test_sr74.dat"}, {"test_data/pucch_processor_format2_test_csi174.dat"}, {"test_data/pucch_processor_format2_test_csi274.dat"}},
  {{238, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 88, 150, 3, {}, 1, 12, 2, 16644, 750, 2029, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols75.dat"}, {"test_data/pucch_processor_format2_test_harq75.dat"}, {"test_data/pucch_processor_format2_test_sr75.dat"}, {"test_data/pucch_processor_format2_test_csi175.dat"}, {"test_data/pucch_processor_format2_test_csi275.dat"}},
  {{206, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 56, 150, 28, {}, 1, 12, 2, 55949, 892, 17283, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols76.dat"}, {"test_data/pucch_processor_format2_test_harq76.dat"}, {"test_data/pucch_processor_format2_test_sr76.dat"}, {"test_data/pucch_processor_format2_test_csi176.dat"}, {"test_data/pucch_processor_format2_test_csi276.dat"}},
  {{214, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 10, 204, 2, {}, 1, 12, 2, 6956, 588, 20665, 6, 0, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols77.dat"}, {"test_data/pucch_processor_format2_test_harq77.dat"}, {"test_data/pucch_processor_format2_test_sr77.dat"}, {"test_data/pucch_processor_format2_test_csi177.dat"}, {"test_data/pucch_processor_format2_test_csi277.dat"}},
  {{129, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 42, 87, 25, {}, 4, 12, 2, 20901, 569, 11351, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols78.dat"}, {"test_data/pucch_processor_format2_test_harq78.dat"}, {"test_data/pucch_processor_format2_test_sr78.dat"}, {"test_data/pucch_processor_format2_test_csi178.dat"}, {"test_data/pucch_processor_format2_test_csi278.dat"}},
  {{108, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 73, 35, 16, {}, 3, 12, 2, 190, 834, 46622, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols79.dat"}, {"test_data/pucch_processor_format2_test_harq79.dat"}, {"test_data/pucch_processor_format2_test_sr79.dat"}, {"test_data/pucch_processor_format2_test_csi179.dat"}, {"test_data/pucch_processor_format2_test_csi279.dat"}},
  {{266, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 204, 62, 65, {}, 2, 12, 2, 36999, 123, 34869, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols80.dat"}, {"test_data/pucch_processor_format2_test_harq80.dat"}, {"test_data/pucch_processor_format2_test_sr80.dat"}, {"test_data/pucch_processor_format2_test_csi180.dat"}, {"test_data/pucch_processor_format2_test_csi280.dat"}},
  {{249, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 10, 239, 3, {}, 1, 12, 2, 20360, 244, 57288, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols81.dat"}, {"test_data/pucch_processor_format2_test_harq81.dat"}, {"test_data/pucch_processor_format2_test_sr81.dat"}, {"test_data/pucch_processor_format2_test_csi181.dat"}, {"test_data/pucch_processor_format2_test_csi281.dat"}},
  {{143, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 12, 131, 5, {}, 1, 12, 2, 31038, 757, 63151, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols82.dat"}, {"test_data/pucch_processor_format2_test_harq82.dat"}, {"test_data/pucch_processor_format2_test_sr82.dat"}, {"test_data/pucch_processor_format2_test_csi182.dat"}, {"test_data/pucch_processor_format2_test_csi282.dat"}},
  {{141, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 6, 135, 1, {}, 1, 12, 2, 59538, 377, 10983, 6, 0, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols83.dat"}, {"test_data/pucch_processor_format2_test_harq83.dat"}, {"test_data/pucch_processor_format2_test_sr83.dat"}, {"test_data/pucch_processor_format2_test_csi183.dat"}, {"test_data/pucch_processor_format2_test_csi283.dat"}},
  {{269, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 94, 175, 22, {}, 3, 12, 2, 39961, 341, 45775, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols84.dat"}, {"test_data/pucch_processor_format2_test_harq84.dat"}, {"test_data/pucch_processor_format2_test_sr84.dat"}, {"test_data/pucch_processor_format2_test_csi184.dat"}, {"test_data/pucch_processor_format2_test_csi284.dat"}},
  {{252, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 7, 245, 2, {}, 2, 12, 2, 20136, 133, 25296, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols85.dat"}, {"test_data/pucch_processor_format2_test_harq85.dat"}, {"test_data/pucch_processor_format2_test_sr85.dat"}, {"test_data/pucch_processor_format2_test_csi185.dat"}, {"test_data/pucch_processor_format2_test_csi285.dat"}},
  {{257, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 36, 221, 4, {}, 1, 12, 2, 13594, 934, 41450, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols86.dat"}, {"test_data/pucch_processor_format2_test_harq86.dat"}, {"test_data/pucch_processor_format2_test_sr86.dat"}, {"test_data/pucch_processor_format2_test_csi186.dat"}, {"test_data/pucch_processor_format2_test_csi286.dat"}},
  {{260, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 222, 38, 59, {}, 1, 12, 2, 63911, 314, 47401, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols87.dat"}, {"test_data/pucch_processor_format2_test_harq87.dat"}, {"test_data/pucch_processor_format2_test_sr87.dat"}, {"test_data/pucch_processor_format2_test_csi187.dat"}, {"test_data/pucch_processor_format2_test_csi287.dat"}},
  {{215, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 19, 196, 4, {}, 1, 12, 2, 51604, 499, 19073, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols88.dat"}, {"test_data/pucch_processor_format2_test_harq88.dat"}, {"test_data/pucch_processor_format2_test_sr88.dat"}, {"test_data/pucch_processor_format2_test_csi188.dat"}, {"test_data/pucch_processor_format2_test_csi288.dat"}},
  {{268, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 19, 249, 11, {}, 1, 12, 2, 48892, 140, 3925, 6, 1, 0, 0}}, {"test_data/pucch_processor_format2_test_input_symbols89.dat"}, {"test_data/pucch_processor_format2_test_harq89.dat"}, {"test_data/pucch_processor_format2_test_sr89.dat"}, {"test_data/pucch_processor_format2_test_csi189.dat"}, {"test_data/pucch_processor_format2_test_csi289.dat"}},
  {{273, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 16, 257, 2, {}, 5, 12, 2, 4117, 624, 41390, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols90.dat"}, {"test_data/pucch_processor_format2_test_harq90.dat"}, {"test_data/pucch_processor_format2_test_sr90.dat"}, {"test_data/pucch_processor_format2_test_csi190.dat"}, {"test_data/pucch_processor_format2_test_csi290.dat"}},
  {{231, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 45, 186, 20, {}, 3, 12, 2, 23822, 481, 3518, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols91.dat"}, {"test_data/pucch_processor_format2_test_harq91.dat"}, {"test_data/pucch_processor_format2_test_sr91.dat"}, {"test_data/pucch_processor_format2_test_csi191.dat"}, {"test_data/pucch_processor_format2_test_csi291.dat"}},
  {{216, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 86, 130, 62, {}, 2, 12, 2, 47070, 23, 63923, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols92.dat"}, {"test_data/pucch_processor_format2_test_harq92.dat"}, {"test_data/pucch_processor_format2_test_sr92.dat"}, {"test_data/pucch_processor_format2_test_csi192.dat"}, {"test_data/pucch_processor_format2_test_csi292.dat"}},
  {{133, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 82, 51, 6, {}, 1, 12, 2, 57294, 187, 37036, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols93.dat"}, {"test_data/pucch_processor_format2_test_harq93.dat"}, {"test_data/pucch_processor_format2_test_sr93.dat"}, {"test_data/pucch_processor_format2_test_csi193.dat"}, {"test_data/pucch_processor_format2_test_csi293.dat"}},
  {{251, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 58, 193, 18, {}, 1, 12, 2, 40340, 552, 40316, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols94.dat"}, {"test_data/pucch_processor_format2_test_harq94.dat"}, {"test_data/pucch_processor_format2_test_sr94.dat"}, {"test_data/pucch_processor_format2_test_csi194.dat"}, {"test_data/pucch_processor_format2_test_csi294.dat"}},
  {{229, 14, {nullopt, {0, 0}, cyclic_prefix::NORMAL, {0}, 141, 88, 68, {}, 1, 12, 2, 64874, 397, 9680, 6, 1, 4, 0}}, {"test_data/pucch_processor_format2_test_input_symbols95.dat"}, {"test_data/pucch_processor_format2_test_harq95.dat"}, {"test_data/pucch_processor_format2_test_sr95.dat"}, {"test_data/pucch_processor_format2_test_csi195.dat"}, {"test_data/pucch_processor_format2_test_csi295.dat"}},
    // clang-format on
};

} // namespace srsran
