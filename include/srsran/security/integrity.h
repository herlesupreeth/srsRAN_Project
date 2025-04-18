/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#pragma once

#include "srsran/adt/byte_buffer.h"
#include "srsran/adt/span.h"
#include "srsran/security/s3g.h"
#include "srsran/security/security.h"
#include "srsran/security/ssl.h"
#include "srsran/security/zuc.h"

namespace srsran {
namespace security {

constexpr uint32_t sec_var_short_mac_input_packed_len = 8;

/******************************************************************************
 * Integrity Protection
 *****************************************************************************/
inline void security_nia1(sec_mac&           mac,
                          const sec_128_key& key,
                          uint32_t           count,
                          uint8_t            bearer,
                          security_direction direction,
                          byte_buffer_view&  msg,
                          uint32_t           msg_len)
{
  // FIXME for now we copy the byte buffer to a contiguous piece of memory.
  // This will be fixed later.
  std::vector<uint8_t> continuous_buf;
  uint32_t             len = msg.length();
  continuous_buf.reserve(len);

  for (uint32_t i = 0; i < len; i++) {
    continuous_buf.push_back(msg[i]);
  }

  if ((msg_len + 7) / 8 <= len) {
    s3g_f9(mac, key.data(), count, bearer << 27, static_cast<uint8_t>(direction), continuous_buf.data(), msg_len);
  }
}

inline void security_nia1(sec_mac&           mac,
                          const sec_128_key& key,
                          uint32_t           count,
                          uint8_t            bearer,
                          security_direction direction,
                          byte_buffer_view&  msg)
{
  security_nia1(mac, key, count, bearer, direction, msg, msg.length() * 8);
}

#ifdef MBEDTLS_CMAC_C
inline void security_nia2_cmac(sec_mac&           mac,
                               const sec_128_key& key,
                               uint32_t           count,
                               uint8_t            bearer,
                               security_direction direction,
                               byte_buffer_view&  msg)
{
  int                          ret;
  mbedtls_cipher_context_t     ctx;
  const mbedtls_cipher_info_t* cipher_info;
  cipher_info = mbedtls_cipher_info_from_type(MBEDTLS_CIPHER_AES_128_ECB);
  if (cipher_info == nullptr) {
    return;
  }
  mbedtls_cipher_init(&ctx);

  ret = mbedtls_cipher_setup(&ctx, cipher_info);
  if (ret != 0) {
    return;
  }

  ret = mbedtls_cipher_cmac_starts(&ctx, key.data(), 128);
  if (ret != 0) {
    return;
  }

  std::array<uint8_t, 8> preamble = {};
  preamble[0]                     = (count >> 24) & 0xff;
  preamble[1]                     = (count >> 16) & 0xff;
  preamble[2]                     = (count >> 8) & 0xff;
  preamble[3]                     = count & 0xff;
  preamble[4]                     = (bearer << 3) | (to_number(direction) << 2);
  ret                             = mbedtls_cipher_cmac_update(&ctx, preamble.data(), preamble.size());

  byte_buffer_segment_span_range segments = msg.modifiable_segments();
  for (const auto& segment : segments) {
    ret = mbedtls_cipher_cmac_update(&ctx, segment.data(), segment.size());
    if (ret != 0) {
      return;
    }
  }
  uint8_t tmp_mac[16];
  ret = mbedtls_cipher_cmac_finish(&ctx, tmp_mac);
  if (ret != 0) {
    return;
  }
  mbedtls_cipher_free(&ctx);
  for (int i = 0; i < 4; ++i) {
    mac[i] = tmp_mac[i];
  }
}
#endif

inline void security_nia2_non_cmac(sec_mac&           mac,
                                   const sec_128_key& key,
                                   uint32_t           count,
                                   uint8_t            bearer,
                                   security_direction direction,
                                   byte_buffer_view&  msg,
                                   uint32_t           msg_len)
{
  uint32_t    len             = msg.length();
  uint32_t    msg_len_block_8 = (msg_len + 7) / 8;
  aes_context ctx;
  uint32_t    i;
  uint32_t    j;
  uint32_t    n;
  uint32_t    pad_bits;
  uint8_t     const_zero[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t     L[16];
  uint8_t     K1[16];
  uint8_t     K2[16];
  uint8_t     T[16];
  uint8_t     tmp[16];

  const uint32_t msg_len_block_8_with_padding = msg_len_block_8 + 8 + 16;
  srsran_assert(msg_len_block_8_with_padding <= sec_max_pdu_size,
                "{}: Maximum PDU length exceeded. len={} max_len={}",
                __FUNCTION__,
                msg_len_block_8_with_padding,
                sec_max_pdu_size);

  std::array<uint8_t, sec_max_pdu_size> M_buf;
  span<uint8_t>                         M(M_buf.data(), msg_len_block_8_with_padding);

  if (msg_len_block_8 <= len) {
    // Subkey L generation
    aes_setkey_enc(&ctx, key.data(), 128);
    aes_crypt_ecb(&ctx, aes_encrypt, const_zero, L);

    // Subkey K1 generation
    for (i = 0; i < 15; i++) {
      K1[i] = (L[i] << 1) | ((L[i + 1] >> 7) & 0x01);
    }
    K1[15] = L[15] << 1;
    if (L[0] & 0x80) {
      K1[15] ^= 0x87;
    }

    // Subkey K2 generation
    for (i = 0; i < 15; i++) {
      K2[i] = (K1[i] << 1) | ((K1[i + 1] >> 7) & 0x01);
    }
    K2[15] = K1[15] << 1;
    if (K1[0] & 0x80) {
      K2[15] ^= 0x87;
    }

    // Construct M
    std::fill(M.begin(), M.end(), 0);
    M[0] = (count >> 24) & 0xff;
    M[1] = (count >> 16) & 0xff;
    M[2] = (count >> 8) & 0xff;
    M[3] = count & 0xff;
    M[4] = (bearer << 3) | (to_number(direction) << 2);
    for (i = 0; i < msg_len_block_8; i++) {
      M[8 + i] = msg[i];
    }

    // MAC generation
    n = (uint32_t)(ceilf((float)(msg_len_block_8 + 8) / (float)(16)));
    for (i = 0; i < 16; i++) {
      T[i] = 0;
    }
    for (i = 0; i < n - 1; i++) {
      for (j = 0; j < 16; j++) {
        tmp[j] = T[j] ^ M[i * 16 + j];
      }
      aes_crypt_ecb(&ctx, aes_encrypt, tmp, T);
    }
    pad_bits = ((msg_len) + 64) % 128;
    if (pad_bits == 0) {
      for (j = 0; j < 16; j++) {
        tmp[j] = T[j] ^ K1[j] ^ M[i * 16 + j];
      }
      aes_crypt_ecb(&ctx, aes_encrypt, tmp, T);
    } else {
      pad_bits = (128 - pad_bits) - 1;
      M[i * 16 + (15 - (pad_bits / 8))] |= 0x1 << (pad_bits % 8);
      for (j = 0; j < 16; j++) {
        tmp[j] = T[j] ^ K2[j] ^ M[i * 16 + j];
      }
      aes_crypt_ecb(&ctx, aes_encrypt, tmp, T);
    }

    for (i = 0; i < 4; i++) {
      mac[i] = T[i];
    }
  }
}

inline void security_nia2(sec_mac&           mac,
                          const sec_128_key& key,
                          uint32_t           count,
                          uint8_t            bearer,
                          security_direction direction,
                          byte_buffer_view&  msg)
{
#ifdef MBEDTLS_CMAC_C
  security_nia2_cmac(mac, key, count, bearer, direction, msg);
#else
  security_nia2_non_cmac(mac, key, count, bearer, direction, msg, msg.length() * 8);
#endif
}

inline uint32_t GET_WORD(uint32_t* DATA, uint32_t i)
{
  uint32_t WORD, ti;
  ti = i % 32;
  if (ti == 0)
    WORD = DATA[i / 32];
  else
    WORD = (DATA[i / 32] << ti) | (DATA[i / 32 + 1] >> (32 - ti));
  return WORD;
}

inline void security_nia3(sec_mac&           mac,
                          const sec_128_key& key,
                          uint32_t           count,
                          uint8_t            bearer,
                          security_direction direction,
                          byte_buffer_view&  msg,
                          uint32_t           msg_len)
{
  uint32_t len    = msg.length();
  uint8_t  iv[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  uint32_t* ks;
  uint32_t  msg_len_block_8 = (msg_len + 7) / 8;
  if (msg_len_block_8 <= len) {
    // Construct iv
    iv[0] = (count >> 24) & 0xff;
    iv[1] = (count >> 16) & 0xff;
    iv[2] = (count >> 8) & 0xff;
    iv[3] = count & 0xff;

    iv[4] = (bearer << 3) & 0xf8;
    iv[5] = iv[6] = iv[7] = 0;

    iv[8]  = ((count >> 24) & 0xff) ^ ((to_number(direction) & 1) << 7);
    iv[9]  = (count >> 16) & 0xff;
    iv[10] = (count >> 8) & 0xff;
    iv[11] = count & 0xff;

    iv[12] = iv[4];
    iv[13] = iv[5];
    iv[14] = iv[6] ^ ((to_number(direction) & 1) << 7);
    iv[15] = iv[7];

    zuc_state_t zuc_state;
    // Initialize keystream
    zuc_initialize(&zuc_state, key.data(), iv);

    // Generate keystream
    int N = msg_len + 64;
    int L = (N + 31) / 32;

    ks = (uint32_t*)calloc(L, sizeof(uint32_t));

    zuc_generate_keystream(&zuc_state, L, ks);

    uint32_t T = 0;
    for (uint32_t i = 0; i < msg_len; i++) {
      if (msg[i / 8] & (1 << (7 - (i % 8)))) {
        T ^= GET_WORD(ks, i);
      }
    }

    T ^= GET_WORD(ks, msg_len);

    uint32_t mac_tmp = T ^ ks[L - 1];
    mac[0]           = (mac_tmp >> 24) & 0xff;
    mac[1]           = (mac_tmp >> 16) & 0xff;
    mac[2]           = (mac_tmp >> 8) & 0xff;
    mac[3]           = mac_tmp & 0xff;

    free(ks);
  }
}

inline void security_nia3(sec_mac&           mac,
                          const sec_128_key& key,
                          uint32_t           count,
                          uint8_t            bearer,
                          security_direction direction,
                          byte_buffer_view&  msg)
{
  security_nia3(mac, key, count, bearer, direction, msg, msg.length() * 8);
}

/// \brief Verify shortMAC-I as specified in TS 38.331, section 5.3.7.4
///
/// \param[in] rx_short_mac The received shortMAC-I
/// \param[in] packed_var The varShortMAC-I packed over ASN.1 rules
/// \param[in] source_as_config The AS keys/algorithms used on the source PCell.
inline bool verify_short_mac(const sec_short_mac_i& rx_short_mac,
                             const byte_buffer&     packed_var,
                             const sec_as_config&   source_as_config)
{
  auto& logger = srslog::fetch_basic_logger("SEC");

  if (packed_var.length() != sec_var_short_mac_input_packed_len) {
    logger.error("Invalid varShortMAC-Input incorrect length. len={}", packed_var.length());
    return false;
  }
  if (!source_as_config.k_int.has_value()) {
    logger.error("Cannot verify short mac: Integrity key is not configured.");
    return false;
  }
  if (!source_as_config.integ_algo.has_value()) {
    logger.error("Cannot verify short mac: Integrity algorithm is not configured.");
    return false;
  }

  security::sec_mac mac_exp  = {};
  bool              is_valid = true;
  sec_128_key       key      = truncate_key(source_as_config.k_int.value());
  byte_buffer_view  packed_var_view{packed_var};
  switch (source_as_config.integ_algo.value()) {
    case security::integrity_algorithm::nia0:
      break;
    case security::integrity_algorithm::nia1:
      security_nia1(mac_exp,
                    key,
                    0xffffffff,                   // 32-bit all to ones
                    0x1f,                         // 5-bit all to ones
                    security_direction::downlink, // 1-bit to one
                    packed_var_view);
      break;
    case security::integrity_algorithm::nia2:
      security_nia2(mac_exp,
                    key,
                    0xffffffff,                   // 32-bit all to ones
                    0x1f,                         // 5-bit all to ones
                    security_direction::downlink, // 1-bit to one
                    packed_var_view);
      break;
    case security::integrity_algorithm::nia3:
      security_nia3(mac_exp,
                    key,
                    0xffffffff,                   // 32-bit all to ones
                    0x1f,                         // 5-bit all to ones
                    security_direction::downlink, // 1-bit to one
                    packed_var_view);
      break;
    default:
      break;
  }

  if (source_as_config.integ_algo != security::integrity_algorithm::nia0) {
    // Check only the two least significant bits
    for (uint8_t i = 2; i < 4; i++) {
      if (rx_short_mac[i - 2] != mac_exp[i]) {
        is_valid = false;
        break;
      }
    }
  }

  // TODO log as warning when shortMAC-I is invalid.
  auto& channel = logger.debug;
  channel(rx_short_mac.data(), rx_short_mac.size(), "shortMAC-I Integrity check. is_valid={}", is_valid);
  channel(key.data(), 16, "Integrity check key.");
  channel(mac_exp.data(), 4, "MAC expected.");
  channel(rx_short_mac.data(), 2, "MAC found.");
  channel(packed_var.begin(), packed_var.end(), "Integrity check input message.");
  return is_valid;
}
} // namespace security
} // namespace srsran
