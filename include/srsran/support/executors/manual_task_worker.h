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

#include "srsran/adt/blocking_queue.h"
#include "srsran/support/executors/task_executor.h"

namespace srsran {

/// \brief Task worker that implements the executor interface and requires manual calls to run pending deferred tasks.
/// Useful for unit testing.
class manual_task_worker : public task_executor
{
public:
  manual_task_worker(size_t q_size, bool blocking_mode_ = true) :
    t_id(std::this_thread::get_id()), pending_tasks(q_size), blocking_mode(blocking_mode_)
  {
  }

  std::thread::id get_thread_id() const { return t_id; }

  [[nodiscard]] bool execute(unique_task task) override
  {
    if (std::this_thread::get_id() == t_id) {
      task();
      return true;
    }
    return defer(std::move(task));
  }

  [[nodiscard]] bool defer(unique_task task) override
  {
    if (blocking_mode) {
      pending_tasks.push_blocking(std::move(task));
      return true;
    }
    return pending_tasks.try_push(std::move(task)).has_value();
  }

  size_t max_pending_tasks() const { return pending_tasks.max_size(); }

  bool has_pending_tasks() const { return not pending_tasks.empty(); }

  bool is_stopped() const { return pending_tasks.is_stopped(); }

  void stop()
  {
    if (not is_stopped()) {
      pending_tasks.stop();
    }
  }

  void request_stop()
  {
    (void)defer([this]() { stop(); });
  }

  /// Run all pending tasks until queue is emptied.
  bool run_pending_tasks()
  {
    assert_thread_id();
    bool ret = false, success = false;
    do {
      unique_task t;
      success = pending_tasks.try_pop(t);
      if (success) {
        t();
        ret = true;
      }
    } while (success);
    return ret;
  }

  /// Run next pending task if it is enqueued.
  bool try_run_next()
  {
    assert_thread_id();
    unique_task t;
    bool        success = pending_tasks.try_pop(t);
    if (not success) {
      return false;
    }
    t();
    return true;
  }

  /// Run next pending task once it is enqueued.
  bool run_next_blocking()
  {
    assert_thread_id();
    bool        success = false;
    unique_task t       = pending_tasks.pop_blocking(&success);
    if (not success) {
      return false;
    }
    t();
    return true;
  }

private:
  bool has_thread_id() const { return t_id != std::thread::id{}; }

  void assert_thread_id()
  {
    srsran_assert(t_id == std::this_thread::get_id(), "run() caller thread should not change.");
  }

  std::thread::id             t_id;
  blocking_queue<unique_task> pending_tasks;
  bool                        blocking_mode;
};

} // namespace srsran
