/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/pubsub/application.hpp"

#include "roq/pubsub/config.hpp"
#include "roq/pubsub/flags.hpp"
#include "roq/pubsub/gateway.hpp"

using namespace std::literals;

namespace roq {
namespace pubsub {

int Application::main(int, char **) {
  log::info(R"(Parse config_file="{}")"sv, Flags::config_file());
  Config config(Flags::config_file());
  log::info<1>("config={}"sv, config);
  log::info("Starting the gateway"sv);
  roq::server::Trading<Gateway>(ROQ_PACKAGE_NAME, ROQ_BUILD_NUMBER, {}, config).dispatch();
  return EXIT_SUCCESS;
}

}  // namespace pubsub
}  // namespace roq
