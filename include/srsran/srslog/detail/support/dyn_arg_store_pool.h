/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#pragma once

#include "rigtorp/MPMCQueue.h"
#include "srsran/srslog/detail/support/backend_capacity.h"

namespace srslog {

namespace detail {

/// Keeps a pool of dynamic_format_arg_store objects. The main reason for this class is that the arg store objects are
/// implemented with std::vectors, so we want to avoid allocating memory each time we create a new object. Instead,
/// reserve memory for each vector during initialization and recycle the objects.
class dyn_arg_store_pool
{
public:
  dyn_arg_store_pool() : free_list(SRSLOG_QUEUE_CAPACITY)
  {
    pool.resize(SRSLOG_QUEUE_CAPACITY);
    for (auto& elem : pool) {
      // Reserve for 10 normal and 2 named arguments.
      elem.reserve(10, 2);
    }
    for (auto& elem : pool) {
      free_list.push(&elem);
    }
  }

  /// Returns a pointer to a free dyn arg store object, otherwise returns nullptr.
  fmt::dynamic_format_arg_store<fmt::format_context>* alloc()
  {
    if (free_list.empty()) {
      return nullptr;
    }

    fmt::dynamic_format_arg_store<fmt::format_context>* p = nullptr;
    free_list.try_pop(p);

    return p;
  }

  /// Deallocate the given dyn arg store object returning it to the pool.
  void dealloc(fmt::dynamic_format_arg_store<fmt::format_context>* p)
  {
    if (!p) {
      return;
    }

    p->clear();
    free_list.push(p);
  }

private:
  std::vector<fmt::dynamic_format_arg_store<fmt::format_context>>         pool;
  rigtorp::MPMCQueue<fmt::dynamic_format_arg_store<fmt::format_context>*> free_list;
};

} // namespace detail

} // namespace srslog
