/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <chrono>
#include <deque>
#include <string>
#include <utility>

#include "roq/api.hpp"
#include "roq/server.hpp"

namespace roq {
namespace udp_publisher {

struct Shared final {
  explicit Shared(server::Dispatcher &);

  Shared(Shared const &) = delete;

  auto discard_symbol(std::string_view const &name) const { return dispatcher_.discard_symbol(name); }

  template <typename... Args>
  auto operator()(Args &&...args) {
    return dispatcher_(std::forward<Args>(args)...);
  }

 private:
  server::Dispatcher &dispatcher_;
};

}  // namespace udp_publisher
}  // namespace roq
