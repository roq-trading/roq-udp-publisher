/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <fmt/format.h>

#include "roq/server/flags/settings.hpp"

#include "roq/udp_publisher/flags/flags.hpp"

namespace roq {
namespace udp_publisher {
namespace flags {

struct ROQ_PUBLIC Settings final : public server::flags::Settings, public flags::Flags {
  explicit Settings(args::Parser const &);
};

}  // namespace flags
}  // namespace udp_publisher
}  // namespace roq

template <>
struct fmt::formatter<roq::udp_publisher::flags::Settings> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::udp_publisher::flags::Settings const &value, format_context &context) const {
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
