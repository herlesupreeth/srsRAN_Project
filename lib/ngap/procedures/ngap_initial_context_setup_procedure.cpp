/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ngap_initial_context_setup_procedure.h"
#include "../ngap_asn1_helpers.h"
#include "srsran/asn1/ngap/common.h"
#include "srsran/ngap/ngap_message.h"
#include "srsran/support/async/coroutine.h"

using namespace srsran;
using namespace srsran::srs_cu_cp;
using namespace asn1::ngap;

ngap_initial_context_setup_procedure::ngap_initial_context_setup_procedure(
    const ngap_init_context_setup_request& request_,
    const ngap_ue_ids&                     ue_ids_,
    ngap_cu_cp_notifier&                   cu_cp_notifier_,
    ngap_message_notifier&                 amf_notifier_,
    ngap_ue_logger&                        logger_) :
  request(request_), ue_ids(ue_ids_), cu_cp_notifier(cu_cp_notifier_), amf_notifier(amf_notifier_), logger(logger_)
{
}

void ngap_initial_context_setup_procedure::operator()(coro_context<async_task<void>>& ctx)
{
  CORO_BEGIN(ctx);

  logger.log_debug("\"{}\" initialized", name());

  CORO_AWAIT_VALUE(init_ctxt_setup_routine_outcome, cu_cp_notifier.on_new_initial_context_setup_request(request));

  if (not init_ctxt_setup_routine_outcome.has_value()) {
    send_initial_context_setup_failure(init_ctxt_setup_routine_outcome.error(), ue_ids.amf_ue_id, ue_ids.ran_ue_id);
    logger.log_debug("\"{}\" failed", name());
  } else {
    send_initial_context_setup_response(init_ctxt_setup_routine_outcome.value(), ue_ids.amf_ue_id, ue_ids.ran_ue_id);
    logger.log_debug("\"{}\" finished successfully", name());
  }

  CORO_RETURN();
}

void ngap_initial_context_setup_procedure::send_initial_context_setup_response(
    const ngap_init_context_setup_response& msg,
    const amf_ue_id_t&                      amf_ue_id,
    const ran_ue_id_t&                      ran_ue_id)
{
  ngap_message ngap_msg = {};

  ngap_msg.pdu.set_successful_outcome();
  ngap_msg.pdu.successful_outcome().load_info_obj(ASN1_NGAP_ID_INIT_CONTEXT_SETUP);
  auto& init_ctxt_setup_resp           = ngap_msg.pdu.successful_outcome().value.init_context_setup_resp();
  init_ctxt_setup_resp->amf_ue_ngap_id = amf_ue_id_to_uint(amf_ue_id);
  init_ctxt_setup_resp->ran_ue_ngap_id = ran_ue_id_to_uint(ran_ue_id);

  if (!fill_asn1_initial_context_setup_response(init_ctxt_setup_resp, msg)) {
    logger.log_warning("Unable to fill ASN1 contents for InitialContextSetupResponse");
    return;
  }

  amf_notifier.on_new_message(ngap_msg);
}

void ngap_initial_context_setup_procedure::send_initial_context_setup_failure(
    const ngap_init_context_setup_failure& msg,
    const amf_ue_id_t&                     amf_ue_id,
    const ran_ue_id_t&                     ran_ue_id)
{
  ngap_message ngap_msg = {};

  ngap_msg.pdu.set_unsuccessful_outcome();
  ngap_msg.pdu.unsuccessful_outcome().load_info_obj(ASN1_NGAP_ID_INIT_CONTEXT_SETUP);
  auto& init_ctxt_setup_fail           = ngap_msg.pdu.unsuccessful_outcome().value.init_context_setup_fail();
  init_ctxt_setup_fail->amf_ue_ngap_id = amf_ue_id_to_uint(amf_ue_id);
  init_ctxt_setup_fail->ran_ue_ngap_id = ran_ue_id_to_uint(ran_ue_id);

  // Fill PDU Session Resource Failed to Setup List
  fill_asn1_initial_context_setup_failure(init_ctxt_setup_fail, msg);

  logger.log_info("Sending InitialContextSetupFailure");
  amf_notifier.on_new_message(ngap_msg);
}
