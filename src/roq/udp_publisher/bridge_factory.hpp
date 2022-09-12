/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <memory>

#include "roq/io/context.hpp"

#include "roq/udp_publisher/bridge.hpp"

namespace roq {
namespace udp_publisher {

struct BridgeFactory final {
  static std::unique_ptr<Bridge> create(io::Context &);
};

}  // namespace udp_publisher
}  // namespace roq
