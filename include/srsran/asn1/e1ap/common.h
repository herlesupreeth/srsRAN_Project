/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

/*******************************************************************************
 *
 *                     3GPP TS ASN1 E1AP v16.10.0 (2022-06)
 *
 ******************************************************************************/

#pragma once

#include "srsran/asn1/asn1_ap_utils.h"

namespace asn1 {
namespace e1ap {

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/

// PrivateIE-ID ::= CHOICE
struct private_ie_id_c {
  struct types_opts {
    enum options { local, global, nulltype } value;

    const char* to_string() const;
  };
  using types = enumerated<types_opts>;

  // choice methods
  private_ie_id_c() = default;
  void        set(types::options e = types::nulltype);
  types       type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  // getters
  uint32_t& local()
  {
    assert_choice_type(types::local, type_, "PrivateIE-ID");
    return c;
  }
  const uint32_t& local() const
  {
    assert_choice_type(types::local, type_, "PrivateIE-ID");
    return c;
  }
  uint32_t& set_local();
  void      set_global();

private:
  types    type_;
  uint32_t c;
};

// PrivateIE-Field{E1AP-PRIVATE-IES : IEsSetParam} ::= SEQUENCE{{E1AP-PRIVATE-IES}}
template <class ies_set_paramT_>
struct private_ie_field_s {
  private_ie_id_c                   id;
  crit_e                            crit;
  typename ies_set_paramT_::value_c value;

  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

// PrivateIE-Container{E1AP-PRIVATE-IES : IEsSetParam} ::= SEQUENCE (SIZE (1..65535)) OF PrivateIE-Field
template <class ies_set_paramT_>
using private_ie_container_l = dyn_seq_of<private_ie_field_s<ies_set_paramT_>, 1, 65535, true>;

template <class valueT_>
struct private_ie_container_item_s {
  private_ie_id_c id;
  crit_e          crit;
  valueT_         value;

  // sequence methods
  private_ie_container_item_s(private_ie_id_c id_, crit_e crit_);
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

} // namespace e1ap
} // namespace asn1
