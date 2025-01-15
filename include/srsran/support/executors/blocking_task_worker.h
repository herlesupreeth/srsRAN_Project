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

/// \brief Contrarily to other type of workers, this worker runs in the same thread where run() is called.
/// run() is blocking.
class blocking_task_worker final : public task_executor
{
public:
  blocking_task_worker(size_t q_size) : pending_tasks(q_size) {}

  [[nodiscard]] bool execute(unique_task task) override
  {
    pending_tasks.push_blocking(std::move(task));
    return true;
  }

  [[nodiscard]] bool defer(unique_task task) override
  {
    (void)execute(std::move(task));
    return true;
  }

  void request_stop()
  {
    (void)execute([this]() {
      if (not pending_tasks.is_stopped()) {
        pending_tasks.stop();
      }
    });
  }

  void run()
  {
    while (true) {
      bool        success;
      unique_task t = pending_tasks.pop_blocking(&success);
      if (not success) {
        break;
      }
      t();
    }
  }

private:
  blocking_queue<unique_task> pending_tasks;
};

} // namespace srsran
