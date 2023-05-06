/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/udp_publisher/settings.hpp"

#include "roq/udp_publisher/flags/flags.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

Settings Settings::create(server::Type type) {
  auto settings = server::create_settings(type, ROQ_PACKAGE_NAME, ROQ_BUILD_NUMBER);
  return {settings};
}

}  // namespace udp_publisher
}  // namespace roq
