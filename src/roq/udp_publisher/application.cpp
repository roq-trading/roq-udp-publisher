/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/application.hpp"

#include "roq/udp_publisher/config.hpp"
#include "roq/udp_publisher/gateway.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

// === CONSTANTS ===

namespace {
server::Settings const SETTINGS{
    .package_name = ROQ_PACKAGE_NAME,
    .build_number = ROQ_BUILD_NUMBER,
    .api = {},
    .type = server::Type::MARKET_DATA,
};
}  // namespace

// === IMPLEMENTATION ===

int Application::main(int, char **) {
  Config config;
  auto context = server::create_io_context();
  server::Trading<Gateway>{SETTINGS, config, *context}.dispatch();
  return EXIT_SUCCESS;
}

}  // namespace udp_publisher
}  // namespace roq
