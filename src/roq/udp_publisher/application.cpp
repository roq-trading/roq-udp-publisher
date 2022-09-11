/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/application.hpp"

#include "roq/io/engine/context_factory.hpp"

#include "roq/udp_publisher/bridge.hpp"
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
  log::info("Prepare environment"sv);
  auto context = io::engine::ContextFactory::create(server::Flags::io_backend());
  Bridge bridge{*context};
  log::info("Start publisher..."sv);
  roq::server::Router<Gateway>{ROQ_PACKAGE_NAME, ROQ_BUILD_NUMBER, {}, config, bridge, *context}.dispatch();
  log::info("Done!"sv);
  return EXIT_SUCCESS;
}

}  // namespace udp_publisher
}  // namespace roq
