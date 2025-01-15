/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "inter_cu_handover_target_routine.h"

using namespace srsran;
using namespace srs_cu_cp;

#ifndef SRSRAN_HAS_ENTERPRISE

async_task<ngap_handover_resource_allocation_response>
srsran::srs_cu_cp::start_inter_cu_handover_target_routine(const ngap_handover_request& request,
                                                          e1ap_bearer_context_manager& e1ap_bearer_ctxt_mng,
                                                          f1ap_ue_context_manager&     f1ap_ue_ctxt_mng,
                                                          cu_cp_ue_removal_handler&    ue_removal_handler,
                                                          ue_manager&                  ue_mng,
                                                          const security_indication_t& default_security_indication,
                                                          srslog::basic_logger&        logger)
{
  logger.error("Inter-CU handover target routine failed. Cause: Inter-CU handover not supported");

  ngap_handover_resource_allocation_response response = {};
  response.success                                    = false;
  response.ue_index                                   = request.ue_index;
  response.cause                                      = cause_protocol_t::unspecified;

  auto err_function = [response](coro_context<async_task<ngap_handover_resource_allocation_response>>& ctx) {
    CORO_BEGIN(ctx);
    CORO_RETURN(response);
  };
  return launch_async(std::move(err_function));
}

#endif // SRSRAN_HAS_ENTERPRISE
