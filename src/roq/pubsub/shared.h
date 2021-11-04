/* Copyright (c) 2017-2021, Hans Erik Thrane */

#pragma once

#include <absl/container/flat_hash_map.h>

#include <chrono>
#include <deque>
#include <string>
#include <utility>

#include "roq/api.h"
#include "roq/server.h"

#include "roq/core/memory.h"

namespace roq {
namespace pubsub {

struct Shared final {
  explicit Shared(server::Dispatcher &);

  Shared(Shared &&) = default;
  Shared(const Shared &) = delete;

  auto discard_symbol(const std::string_view &name) const {
    return dispatcher_.discard_symbol(name);
  }
  template <typename... Args>
  auto operator()(Args &&...args) {
    return dispatcher_(std::forward<Args>(args)...);
  }

 private:
  server::Dispatcher &dispatcher_;
};

}  // namespace pubsub
}  // namespace roq
