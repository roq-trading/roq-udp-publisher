/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/bridge_factory.hpp"

#include "roq/utils/compare.hpp"

#include "roq/logging.hpp"

#include "roq/udp_publisher/flags.hpp"

#include "roq/udp_publisher/fbs_bridge.hpp"
#include "roq/udp_publisher/json_bridge.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

std::unique_ptr<Bridge> BridgeFactory::create(io::Context &context) {
  auto encoding = Flags::encoding();
  if (utils::case_insensitive_compare(encoding, "json"sv) == 0) {
    return std::make_unique<JSONBridge>(context);
  } else if (
      utils::case_insensitive_compare(encoding, "fbs"sv) == 0 ||
      utils::case_insensitive_compare(encoding, "flatbuffers"sv) == 0) {
    return std::make_unique<FBSBridge>(context);
  } else {
    log::fatal(R"(Unexpected: encoding="{}")"sv, encoding);
  }
}

}  // namespace udp_publisher
}  // namespace roq
