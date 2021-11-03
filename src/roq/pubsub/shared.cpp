/* Copyright (c) 2017-2021, Hans Erik Thrane */

#include "roq/pubsub/shared.h"

#include "roq/pubsub/flags.h"

namespace roq {
namespace pubsub {

Shared::Shared(server::Dispatcher &dispatcher)
    : fills(server::Flags::cache_fills_max_depth()), bids(server::Flags::cache_mbp_max_depth()),
      asks(server::Flags::cache_mbp_max_depth()), final_bids(server::Flags::cache_mbp_max_depth()),
      final_asks(server::Flags::cache_mbp_max_depth()), dispatcher_(dispatcher),
      rate_limiter_(Flags::request_limit(), Flags::request_limit_interval()) {
}

}  // namespace pubsub
}  // namespace roq
