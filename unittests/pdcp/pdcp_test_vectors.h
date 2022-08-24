/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */
#pragma once

#include <array>
#include <cstdint>

// Test SDUs for TX.
const int                           sdu_size = 2;
const std::array<uint8_t, sdu_size> sdu1     = {0x18, 0xe2};
const std::array<uint8_t, sdu_size> sdu2     = {0xde, 0xad};

// Test PDUs for RX.
// Generated from SDU1, using NIA1 and NEA1.
const int                                   pdu_size_snlen12       = 8;
const int                                   pdu_size_snlen18       = 9;
const std::array<uint8_t, pdu_size_snlen12> pdu1_count0_snlen12    = {0x80, 0x00, 0x8f, 0xe3, 0xc7, 0x1b, 0xad, 0x14};
const std::array<uint8_t, pdu_size_snlen12> pdu1_count2048_snlen12 = {0x88, 0x00, 0x8d, 0x2c, 0xe5, 0x38, 0xc0, 0x42};
const std::array<uint8_t, pdu_size_snlen12> pdu1_count4096_snlen12 = {0x80, 0x00, 0x97, 0xbe, 0xee, 0x62, 0xf5, 0xe0};
const std::array<uint8_t, pdu_size_snlen12> pdu1_count4294967295_snlen12 =
    {0x8f, 0xff, 0x1e, 0x47, 0xa9, 0x55, 0xa9, 0xd8};
const std::array<uint8_t, pdu_size_snlen18> pdu1_count0_snlen18 =
    {0x80, 0x00, 0x00, 0x8f, 0xe3, 0x37, 0x33, 0xd5, 0x64};
const std::array<uint8_t, pdu_size_snlen18> pdu1_count131072_snlen18 =
    {0x82, 0x00, 0x00, 0x15, 0x01, 0x99, 0x97, 0xe0, 0x4e};
const std::array<uint8_t, pdu_size_snlen18> pdu1_count262144_snlen18 =
    {0x80, 0x00, 0x00, 0xc2, 0x47, 0xc2, 0xee, 0x46, 0xd9};
const std::array<uint8_t, pdu_size_snlen18> pdu1_count4294967295_snlen18 =
    {0x83, 0xff, 0xff, 0x1e, 0x47, 0x78, 0xb8, 0x7a, 0x9f};
