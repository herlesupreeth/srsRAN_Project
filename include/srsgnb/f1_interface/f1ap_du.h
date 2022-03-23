
#ifndef SRSGNB_F1AP_DU_H
#define SRSGNB_F1AP_DU_H

#include "srsgnb/adt/byte_buffer.h"
#include "srsgnb/asn1/f1ap.h"
#include "srsgnb/ran/du_types.h"
#include "srsgnb/ran/lcid.h"
#include "srsgnb/support/async/async_task.h"

namespace srsgnb {

struct ul_ccch_indication_message;
struct ul_rrc_transfer_message;
struct du_ue_create_response_message;

struct f1ap_du_ue_create_request_message {
  du_ue_index_t ue_index;
};

struct f1ap_du_ue_create_response_message {
  bool result;
};

class f1ap_du_dl_interface
{
public:
  virtual ~f1ap_du_dl_interface()               = default;
  virtual void push_sdu(const byte_buffer& sdu) = 0;
};

struct f1_rx_pdu {
  du_ue_index_t ue_index;
  lcid_t        lcid;
  byte_buffer   pdu;
};

struct ul_rrc_message_delivery_status {
  du_cell_index_t cell_index;
  du_ue_index_t   ue_index;
  lcid_t          lcid;
  bool            rrc_delivery_status;
};

class f1ap_du_ul_interface
{
public:
  virtual ~f1ap_du_ul_interface()                                                           = default;
  virtual void ul_rrc_message_delivery_report(const ul_rrc_message_delivery_status& report) = 0;
  virtual void handle_pdu(f1_rx_pdu pdu)                                                    = 0;
};

struct du_setup_params {
  // mandatory
  uint64_t gnb_du_id;
  uint8_t  rrc_version;

  // optional
  std::string gnb_du_name;
};

struct du_setup_result {
  bool                        result;
  asn1::f1ap::f1_setup_resp_s resp;
  asn1::f1ap::f1_setup_fail_s failure;
};

class f1ap_du_configurer
{
public:
  virtual ~f1ap_du_configurer() = default;
  virtual async_task<f1ap_du_ue_create_response_message>
                                      handle_ue_creation_request(const f1ap_du_ue_create_request_message& msg) = 0;
  virtual async_task<du_setup_result> f1ap_du_setup_request(const du_setup_params& params)                     = 0;
};

/// Packet entry point for the F1AP interface.
class f1ap_du_interface : public f1ap_du_dl_interface, public f1ap_du_ul_interface, public f1ap_du_configurer
{
public:
  virtual ~f1ap_du_interface() = default;
};

/// Packet notification interface.
class f1ap_du_pdu_notifier
{
public:
  virtual ~f1ap_du_pdu_notifier() = default;
  /// This callback is invoked for each outgoing packed that is generated by the F1AP interface.
  virtual void push_pdu(const byte_buffer& data) = 0;
};

} // namespace srsgnb

#endif // SRSGNB_F1AP_DU_H
