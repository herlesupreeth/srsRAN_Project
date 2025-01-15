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

#include "srsran/ofh/ethernet/ethernet_unique_buffer.h"
#include "srsran/support/srsran_assert.h"

namespace srsran {
namespace ether {

class ethernet_rx_buffer_pool;

/// Receive buffer wrapper dedicated for socket-based Ethernet receiver.
class ethernet_rx_buffer_impl : public rx_buffer
{
public:
  /// Constructor receives the reference to the pool, from which one buffer is requested.
  ethernet_rx_buffer_impl(ethernet_rx_buffer_pool& pool_, unsigned id);

  /// Destructor frees this buffer in the pool.
  ~ethernet_rx_buffer_impl();

  /// Copy constructor is deleted.
  ethernet_rx_buffer_impl(ethernet_rx_buffer_impl& /**/) = delete;

  /// Copy assignment operator is deleted.
  ethernet_rx_buffer_impl& operator=(const ethernet_rx_buffer_impl& other) = delete;

  /// Move assignment operator.
  ethernet_rx_buffer_impl& operator=(ethernet_rx_buffer_impl&& other) noexcept;

  /// Move constructor.
  ethernet_rx_buffer_impl(ethernet_rx_buffer_impl&& other) noexcept;

  // See interface for documentation.
  span<const uint8_t> data() const override;

  /// Returns span of bytes for writing.
  span<uint8_t> storage();

  /// Sets the actually used size.
  void resize(unsigned used_size);

private:
  ethernet_rx_buffer_pool& pool;
  int                      id = -1;
  /// Using size instead of a span here to save space and to enable using this class inside a \c unique_task
  /// implementation exploiting small buffer vtable.
  unsigned size = 0;
};

} // namespace ether
} // namespace srsran
