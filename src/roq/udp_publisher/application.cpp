/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/udp_publisher/application.hpp"

#include "roq/udp_publisher/config.hpp"
#include "roq/udp_publisher/gateway.hpp"
#include "roq/udp_publisher/settings.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

// === IMPLEMENTATION ===

int Application::main(args::Parser const &args) {
  Settings settings{args};
  Config config{settings};
  auto context = server::create_io_context(settings);
  server::MarketData<Gateway>{settings, config, *context}.dispatch();
  return EXIT_SUCCESS;
}

}  // namespace udp_publisher
}  // namespace roq
