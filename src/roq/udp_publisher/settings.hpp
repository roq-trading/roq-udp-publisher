/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <fmt/chrono.h>
#include <fmt/compile.h>
#include <fmt/format.h>

#include "roq/server/flags/settings.hpp"

namespace roq {
namespace udp_publisher {

struct Settings final : public server::flags::Settings {
  explicit Settings(args::Parser const &, server::Type);

  std::string_view exchange;
};

}  // namespace udp_publisher
}  // namespace roq

template <>
struct fmt::formatter<roq::udp_publisher::Settings> {
  template <typename Context>
  constexpr auto parse(Context &context) {
    return std::begin(context);
  }
  template <typename Context>
  auto format(roq::udp_publisher::Settings const &value, Context &context) const {
    using namespace fmt::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(exchange="{}", )"
        R"(server={})"
        R"(}})"_cf,
        value.exchange,
        static_cast<roq::server::Settings const &>(value));
  }
};
