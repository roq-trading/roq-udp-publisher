/* Copyright (c) 2017-2021, Hans Erik Thrane */

#include "roq/pubsub/security.h"

namespace roq {
namespace pubsub {

Security::Security(const Config &config, const std::string_view &account)
    : account_(account), hasher_(config.get_api_key(account_), config.get_secret(account_)) {
}

}  // namespace pubsub
}  // namespace roq
