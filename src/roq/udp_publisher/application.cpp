/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/application.hpp"

#include "roq/udp_publisher/config.hpp"
#include "roq/udp_publisher/gateway.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

int Application::main(int, char **) {
  Config config;
  log::info<1>("config={}"sv, config);
  auto context = server::create_io_context();
  server::Settings settings{
      .package_name = ROQ_PACKAGE_NAME,
      .build_number = ROQ_BUILD_NUMBER,
      .api = {},
      .type = server::Type::MARKET_DATA,
  };
  server::Trading<Gateway>{settings, config, *context}.dispatch();
  log::info("Done!"sv);
  return EXIT_SUCCESS;
}

}  // namespace udp_publisher
}  // namespace roq
