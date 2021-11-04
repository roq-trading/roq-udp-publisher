/* Copyright (c) 2017-2021, Hans Erik Thrane */

#include "roq/pubsub/shared.h"

#include "roq/pubsub/flags.h"

namespace roq {
namespace pubsub {

Shared::Shared(server::Dispatcher &dispatcher) : dispatcher_(dispatcher) {
}

}  // namespace pubsub
}  // namespace roq
