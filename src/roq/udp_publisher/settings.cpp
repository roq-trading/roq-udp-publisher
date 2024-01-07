/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/udp_publisher/settings.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

Settings::Settings(args::Parser const &args)
    : server::flags::Settings{args, ROQ_PACKAGE_NAME, ROQ_BUILD_NUMBER}, flags::Flags{flags::Flags::create()} {
  log::info("settings={}"sv, *this);
}

}  // namespace udp_publisher
}  // namespace roq
