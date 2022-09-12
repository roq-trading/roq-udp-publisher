/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include "roq/server.hpp"

namespace roq {
namespace udp_publisher {

struct Bridge : public server::Hook {
  virtual ~Bridge() {}
};

}  // namespace udp_publisher
}  // namespace roq
