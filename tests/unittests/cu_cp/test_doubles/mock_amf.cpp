/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "mock_amf.h"
#include "srsran/adt/concurrent_queue.h"
#include "srsran/adt/mutexed_mpmc_queue.h"
#include "srsran/ngap/ngap_message.h"

using namespace srsran;
using namespace srs_cu_cp;

/// \brief Mock class for the interface between CU-CP and AMF that accounts for the fact that the CU-CP may push PDUs
/// from different threads.
class synchronized_mock_amf : public mock_amf
{
public:
  explicit synchronized_mock_amf() : rx_pdus(1024), pending_tx_pdus(16) {}

  std::unique_ptr<ngap_message_notifier>
  handle_cu_cp_connection_request(std::unique_ptr<ngap_message_notifier> cu_cp_rx_pdu_notifier) override
  {
    class sync_mock_pdu_notifier : public ngap_message_notifier
    {
    public:
      sync_mock_pdu_notifier(synchronized_mock_amf& parent_) : parent(parent_) {}
      ~sync_mock_pdu_notifier() override { parent.rx_pdu_notifier.reset(); }

      void on_new_message(const ngap_message& msg) override
      {
        // If a PDU response has been previously enqueued, we send it now.
        if (not parent.pending_tx_pdus.empty()) {
          ngap_message tx_pdu;
          parent.pending_tx_pdus.try_pop(tx_pdu);
          parent.push_tx_pdu(tx_pdu);
        }

        bool success = parent.rx_pdus.push_blocking(msg);
        report_error_if_not(success, "Queue is full");
      }

    private:
      synchronized_mock_amf& parent;
    };

    rx_pdu_notifier = std::move(cu_cp_rx_pdu_notifier);
    return std::make_unique<sync_mock_pdu_notifier>(*this);
  }

  bool try_pop_rx_pdu(ngap_message& pdu) override { return rx_pdus.try_pop(pdu); }

  void push_tx_pdu(const ngap_message& pdu) override { rx_pdu_notifier->on_new_message(pdu); }

  void enqueue_next_tx_pdu(const ngap_message& pdu) override { pending_tx_pdus.push_blocking(pdu); }

  void drop_connection() override { rx_pdu_notifier.reset(); }

private:
  using ngap_pdu_queue = concurrent_queue<ngap_message,
                                          concurrent_queue_policy::locking_mpmc,
                                          concurrent_queue_wait_policy::condition_variable>;

  ngap_pdu_queue rx_pdus;

  std::unique_ptr<ngap_message_notifier> rx_pdu_notifier;

  // Tx PDUs to send once the NG connection is set up.
  ngap_pdu_queue pending_tx_pdus;
};

std::unique_ptr<mock_amf> srsran::srs_cu_cp::create_mock_amf()
{
  return std::make_unique<synchronized_mock_amf>();
}
