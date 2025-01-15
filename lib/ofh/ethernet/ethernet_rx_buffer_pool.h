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

#include "ethernet_rx_buffer_impl.h"
#include "srsran/adt/expected.h"
#include "srsran/adt/mpmc_queue.h"
#include "srsran/adt/span.h"
#include "srsran/support/math/math_utils.h"
#include "srsran/support/srsran_assert.h"
#include "srsran/support/units.h"
#include <vector>

namespace srsran {
namespace ether {

/// Pool of buffers accessed by a socket-based Ethernet receiver.
class ethernet_rx_buffer_pool
{
  /// Allocate 4MB of storage, evenly divided between Ethernet receive buffers.
  static inline constexpr units::bytes ETH_BUFFER_POOL_SIZE{4096000};

  using rx_buffer_id_list =
      concurrent_queue<unsigned, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>;

  unsigned number_of_buffers;

  std::vector<std::vector<uint8_t>> entries;
  rx_buffer_id_list                 free_list;

public:
  /// Constructor allocates buffers with given size, assigns an ID to each of them and puts them into a list of free
  /// buffers.
  explicit ethernet_rx_buffer_pool(unsigned buffer_size) :
    number_of_buffers(divide_ceil(ETH_BUFFER_POOL_SIZE.value(), buffer_size)),
    entries(number_of_buffers),
    free_list(number_of_buffers)
  {
    for (unsigned i = 0; i != number_of_buffers; ++i) {
      entries[i].resize(buffer_size);
      while (!free_list.try_push(i)) {
      }
    }
  }

  /// Tries to get an ID of a free buffer from the pre-allocated storage.
  expected<ethernet_rx_buffer_impl> reserve()
  {
    auto buffer_id = free_list.try_pop();
    if (!buffer_id.has_value()) {
      return make_unexpected(default_error_t{});
    }
    return {{*this, buffer_id.value()}};
  }

  /// Marks the buffer with given ID as free.
  void free(unsigned buffer_id)
  {
    // Push identifier back in the pool.
    while (!free_list.try_push(buffer_id)) {
    }
  }

  /// Returns the span of data belonging to a buffer with the given ID.
  span<uint8_t> get_data(unsigned id)
  {
    srsran_assert(id < entries.size(), "Buffer index ({}) is out of range ({}).", id, entries.size());
    return {entries[id].data(), entries[id].size()};
  }
};

} // namespace ether
} // namespace srsran
