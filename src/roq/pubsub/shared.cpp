/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/pubsub/shared.hpp"

#include "roq/pubsub/flags.hpp"

namespace roq {
namespace pubsub {

Shared::Shared(server::Dispatcher &dispatcher) : dispatcher_(dispatcher) {
}

}  // namespace pubsub
}  // namespace roq
