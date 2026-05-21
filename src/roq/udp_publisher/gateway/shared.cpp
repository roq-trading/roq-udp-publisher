/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/udp_publisher/gateway/shared.hpp"

namespace roq {
namespace udp_publisher {
namespace gateway {

Shared::Shared(server::Dispatcher &dispatcher) : dispatcher_{dispatcher} {
}

}  // namespace gateway
}  // namespace udp_publisher
}  // namespace roq
