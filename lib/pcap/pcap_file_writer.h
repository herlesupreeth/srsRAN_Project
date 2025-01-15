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

#include "srsran/adt/byte_buffer.h"
#include "srsran/adt/span.h"
#include "srsran/srslog/srslog.h"
#include <fstream>
#include <string>

#define PCAP_CONTEXT_HEADER_MAX 256

namespace srsran {

/// This structure gets written to the start of the file
struct pcap_hdr_t {
  unsigned       magic_number;  /// magic number
  unsigned short version_major; /// major version number
  unsigned short version_minor; /// minor version number
  unsigned       thiszone;      /// GMT to local correction
  unsigned       sigfigs;       /// accuracy of timestamps
  unsigned       snaplen;       /// max length of captured packets, in octets
  unsigned       network;       /// data link type
};

/// This structure precedes each packet
struct pcaprec_hdr_t {
  unsigned ts_sec;   /// timestamp seconds
  unsigned ts_usec;  /// timestamp microseconds
  unsigned incl_len; /// number of octets of packet saved in file
  unsigned orig_len; /// actual length of packet
};

/// @brief Base class for PCAP writing to files.
/// The class in *not* thread-safe. Proper protection from multiple threads
/// needs to be implemented by the user of the class.
class pcap_file_writer
{
public:
  pcap_file_writer();
  ~pcap_file_writer();
  pcap_file_writer(const pcap_file_writer& other)            = delete;
  pcap_file_writer& operator=(const pcap_file_writer& other) = delete;
  pcap_file_writer(pcap_file_writer&& other)                 = delete;
  pcap_file_writer& operator=(pcap_file_writer&& other)      = delete;

  bool is_write_enabled() const { return pcap_fstream.is_open(); }

  bool open(uint32_t dlt, const std::string& filename);
  void flush();
  void close();
  void write_pdu_header(uint32_t length);
  void write_pdu(srsran::const_span<uint8_t> pdu);
  void write_pdu(const byte_buffer& pdu);

private:
  srslog::basic_logger& logger;
  std::ofstream         pcap_fstream;
  std::string           filename;
  uint32_t              dlt = 0;
};

} // namespace srsran
