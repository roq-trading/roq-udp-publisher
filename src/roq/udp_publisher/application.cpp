/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/application.hpp"

#include "roq/udp_publisher/config.hpp"
#include "roq/udp_publisher/flags.hpp"
#include "roq/udp_publisher/gateway.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

int Application::main(int, char **) {
  log::info(R"(Parse config_file="{}")"sv, Flags::config_file());
  Config config(Flags::config_file());
  log::info<1>("config={}"sv, config);
  log::info("Starting the gateway"sv);
  roq::server::Trading<Gateway>(ROQ_PACKAGE_NAME, ROQ_BUILD_NUMBER, {}, config).dispatch();
  return EXIT_SUCCESS;
}

}  // namespace udp_publisher
}  // namespace roq
