/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "pcap_file_writer.h"
#include "srsran/adt/byte_buffer.h"
#include "srsran/adt/unique_function.h"
#include <mutex>

namespace srsran {

class task_executor;

class pcap_pdu_data
{
public:
  explicit pcap_pdu_data(byte_buffer payload_) : payload_buf(std::move(payload_)) {}

  pcap_pdu_data(span<const uint8_t> context_header, byte_buffer payload)
  {
    auto header = byte_buffer::create(context_header);
    if (not header.has_value()) {
      return;
    }
    if (not header_buf.append(std::move(header.value()))) {
      return;
    }
    if (not payload_buf.append(std::move(payload))) {
      header_buf.clear();
      return;
    }
  }
  pcap_pdu_data(uint16_t            src,
                uint16_t            dest,
                const char*         layer_str,
                span<const uint8_t> context_header,
                byte_buffer         payload);

  const byte_buffer& header() const { return header_buf; }
  const byte_buffer& payload() const { return payload_buf; }

private:
  byte_buffer header_buf;
  byte_buffer payload_buf;
};

/// \brief This class provides a thread-safe interface to write to the pcap file, by only allowing accesses to the
/// file via a single executor.
class backend_pcap_writer
{
  std::string           layer_name;
  std::string           filename;
  task_executor&        backend_exec;
  srslog::basic_logger& logger;
  pcap_file_writer      writer;
  std::atomic<bool>     is_open{true};

public:
  backend_pcap_writer(unsigned           dlt_,
                      const std::string& layer_name_,
                      const std::string& filename,
                      task_executor&     backend_exec_);

  ~backend_pcap_writer();

  backend_pcap_writer(const backend_pcap_writer& other)            = delete;
  backend_pcap_writer& operator=(const backend_pcap_writer& other) = delete;
  backend_pcap_writer(backend_pcap_writer&& other)                 = delete;
  backend_pcap_writer& operator=(backend_pcap_writer&& other)      = delete;

  void flush();

  void close();

  bool is_write_enabled() const { return is_open.load(std::memory_order_relaxed); }

  void write_pdu(byte_buffer pdu);

  void write_pdu(pcap_pdu_data pdu);

private:
  void flush_impl();

  void write_pdu_impl(const byte_buffer& pdu);

  void write_context_pdu_impl(const pcap_pdu_data& pdu);
};

} // namespace srsran
