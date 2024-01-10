/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <fmt/format.h>

#include "roq/server/flags/settings.hpp"

#include "roq/udp_publisher/flags/flags.hpp"

namespace roq {
namespace udp_publisher {

struct Settings final : public server::flags::Settings, public flags::Flags {
  explicit Settings(args::Parser const &);
};

}  // namespace udp_publisher
}  // namespace roq

template <>
struct fmt::formatter<roq::udp_publisher::Settings> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::udp_publisher::Settings const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(exchange="{}", )"
        R"(server={})"
        R"(}})"sv,
        value.exchange,
        static_cast<roq::server::Settings const &>(value));
  }
};
