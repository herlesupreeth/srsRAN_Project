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

#include "rigtorp/SPSCQueue.h"
#include "srsran/adt/concurrent_queue.h"
#include "srsran/support/error_handling.h"
#include <chrono>
#include <thread>

namespace srsran {
namespace detail {

/// Specialization for lockfree SPSC without a blocking mechanism.
template <typename T>
class queue_impl<T, concurrent_queue_policy::lockfree_spsc, concurrent_queue_wait_policy::non_blocking>
{
public:
  template <typename... Args>
  explicit queue_impl(size_t qsize) : queue(qsize)
  {
  }

  template <typename U>
  bool try_push(U&& elem)
  {
    return queue.try_push(std::forward<U>(elem));
  }

  bool try_pop(T& elem)
  {
    T* front = queue.front();
    if (front != nullptr) {
      elem = std::move(*front);
      queue.pop();
      return true;
    }
    return false;
  }

  size_t size() const { return queue.size(); }

  bool empty() const { return queue.empty(); }

  size_t capacity() const { return queue.capacity(); }

protected:
  ::rigtorp::SPSCQueue<T> queue;
};

/// Specialization for lockfree SPSC using a spin sleep loop as the blocking mechanism.
template <typename T>
class queue_impl<T, concurrent_queue_policy::lockfree_spsc, concurrent_queue_wait_policy::sleep>
  : public queue_impl<T, concurrent_queue_policy::lockfree_spsc, concurrent_queue_wait_policy::non_blocking>
{
  using base_type = queue_impl<T, concurrent_queue_policy::lockfree_spsc, concurrent_queue_wait_policy::non_blocking>;

public:
  template <typename... Args>
  explicit queue_impl(size_t qsize, std::chrono::microseconds sleep_time_) :
    queue_impl<T, concurrent_queue_policy::lockfree_spsc, concurrent_queue_wait_policy::non_blocking>(qsize),
    sleep_time(sleep_time_)
  {
  }

  void request_stop() { running = false; }

  template <typename U>
  bool push_blocking(U&& elem)
  {
    while (running.load(std::memory_order_relaxed)) {
      if (this->try_push(std::forward<U>(elem))) {
        return true;
      }
      std::this_thread::sleep_for(sleep_time);
    }
    return false;
  }

  bool pop_blocking(T& elem) noexcept
  {
    T* f = front_blocking();
    if (f != nullptr) {
      elem = std::move(*f);
      this->queue.pop();
      return true;
    }
    return false;
  }

  template <typename PoppingFunc>
  bool call_on_pop_blocking(PoppingFunc&& func)
  {
    T* f = front_blocking();
    if (f != nullptr) {
      func(*f);
      this->queue.pop();
      return true;
    }
    return false;
  }

private:
  T* front_blocking()
  {
    while (running.load(std::memory_order_relaxed)) {
      T* front = this->queue.front();
      if (front != nullptr) {
        return front;
      }
      std::this_thread::sleep_for(sleep_time);
    }
    return nullptr;
  }

  std::chrono::microseconds sleep_time;
  std::atomic<bool>         running{true};
};

} // namespace detail
} // namespace srsran
