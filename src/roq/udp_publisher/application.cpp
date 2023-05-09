/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/udp_publisher/application.hpp"

#include "roq/udp_publisher/config.hpp"
#include "roq/udp_publisher/gateway.hpp"
#include "roq/udp_publisher/settings.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

// === CONSTANTS ===

namespace {
auto const TYPE = server::Type::MARKET_DATA;
}  // namespace

// === IMPLEMENTATION ===

int Application::main(int, char **) {
  Settings settings{TYPE};
  Config config{settings};
  auto context = server::create_io_context();
  server::Trading<Gateway>{settings, config, *context}.dispatch();
  return EXIT_SUCCESS;
}

}  // namespace udp_publisher
}  // namespace roq
