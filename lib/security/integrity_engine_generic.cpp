/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "integrity_engine_generic.h"
#include "srsran/security/integrity.h"
#include "srsran/security/security.h"

using namespace srsran;
using namespace security;

integrity_engine_generic::integrity_engine_generic(sec_128_key         k_128_int_,
                                                   uint8_t             bearer_id_,
                                                   security_direction  direction_,
                                                   integrity_algorithm integ_algo_) :
  k_128_int(k_128_int_), bearer_id(bearer_id_), direction(direction_), integ_algo(integ_algo_)
{
}

security_result integrity_engine_generic::protect_integrity(byte_buffer buf, uint32_t count)
{
  security_result   result{.buf = std::move(buf), .count = count};
  security::sec_mac mac = {};

  byte_buffer_view v{result.buf.value().begin(), result.buf.value().end()};

  switch (integ_algo) {
    case security::integrity_algorithm::nia0:
      // TS 33.501, Sec. D.1
      // The NIA0 algorithm shall be implemented in such way that it shall generate a 32 bit MAC-I/NAS-MAC and
      // XMAC-I/XNAS-MAC of all zeroes (see sub-clause D.3.1).
      std::fill(mac.begin(), mac.end(), 0);
      break;
    case security::integrity_algorithm::nia1:
      security_nia1(mac, k_128_int, count, bearer_id, direction, v);
      break;
    case security::integrity_algorithm::nia2:
      security_nia2(mac, k_128_int, count, bearer_id, direction, v);
      break;
    case security::integrity_algorithm::nia3:
      security_nia3(mac, k_128_int, count, bearer_id, direction, v);
      break;
    default:
      break;
  }

  if (not result.buf->append(mac)) {
    result.buf = make_unexpected(security_error::buffer_failure);
  }
  return result;
}

security_result integrity_engine_generic::verify_integrity(byte_buffer buf, uint32_t count)
{
  security_result   result{.buf = std::move(buf), .count = count};
  security::sec_mac mac = {};

  if (result.buf->length() <= mac.size()) {
    result.buf = make_unexpected(security_error::integrity_failure);
    return result;
  }

  byte_buffer_view v{result.buf.value(), 0, result.buf.value().length() - mac.size()};
  byte_buffer_view m{result.buf.value(), result.buf.value().length() - mac.size(), mac.size()};

  switch (integ_algo) {
    case security::integrity_algorithm::nia0:
      // TS 33.501, Sec. D.1
      // The NIA0 algorithm shall be implemented in such way that it shall generate a 32 bit MAC-I/NAS-MAC and
      // XMAC-I/XNAS-MAC of all zeroes (see sub-clause D.3.1).
      std::fill(mac.begin(), mac.end(), 0);
      break;
    case security::integrity_algorithm::nia1:
      security_nia1(mac, k_128_int, count, bearer_id, direction, v);
      break;
    case security::integrity_algorithm::nia2:
      security_nia2(mac, k_128_int, count, bearer_id, direction, v);
      break;
    case security::integrity_algorithm::nia3:
      security_nia3(mac, k_128_int, count, bearer_id, direction, v);
      break;
    default:
      break;
  }

  // Verify MAC
  if (!std::equal(mac.begin(), mac.end(), m.begin(), m.end())) {
    result.buf = make_unexpected(security_error::integrity_failure);
    return result;
  }

  // Trim MAC from PDU
  result.buf.value().trim_tail(mac.size());

  return result;
}
