/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/json_bridge.hpp"

#include <utility>

#include "roq/logging.hpp"

#include "roq/json/custom_metrics_update.hpp"
#include "roq/json/top_of_book.hpp"

#include "roq/udp_publisher/flags.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

JSONBridge::JSONBridge(io::Context &context) : Bridge(context, core::udp::Encoding::JSON) {
}

// server::Hook

void JSONBridge::operator()(Trace<TopOfBook> const &event) {
  dispatch(R"(["TopOfBook",{}])"sv, json::TopOfBook{event});
}

void JSONBridge::operator()(Trace<CustomMetricsUpdate> const &event) {
  dispatch(R"(["CustomMetricsUpdate",{}])"sv, json::CustomMetricsUpdate{event});
}

template <typename... Args>
void JSONBridge::dispatch(fmt::format_string<Args...> const &fmt, Args &&...args) {
  buffer_.clear();
  fmt::format_to(std::back_inserter(buffer_), fmt, std::forward<Args>(args)...);
  std::string_view message{std::data(buffer_), std::size(buffer_)};
  std::span payload{reinterpret_cast<std::byte const *>(std::data(message)), std::size(message)};
  send(payload);
}

}  // namespace udp_publisher
}  // namespace roq
