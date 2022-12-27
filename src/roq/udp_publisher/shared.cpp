/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/udp_publisher/shared.hpp"

#include "roq/udp_publisher/flags.hpp"

namespace roq {
namespace udp_publisher {

Shared::Shared(server::Dispatcher &dispatcher) : dispatcher_{dispatcher} {
}

}  // namespace udp_publisher
}  // namespace roq
