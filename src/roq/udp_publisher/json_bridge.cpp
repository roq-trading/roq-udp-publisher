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

namespace {
auto create_sender(auto &handler, auto &context) {
  return context.create_udp_sender(handler, io::NetworkAddress{Flags::udp_port()});
}
}  // namespace

JSONBridge::JSONBridge(io::Context &context) : context_(context), sender_(create_sender(*this, context_)) {
}

// server::Hook

void JSONBridge::operator()(Trace<TopOfBook const> const &event) {
  send(R"(["TopOfBook",{}])"sv, json::TopOfBook{event});
}

void JSONBridge::operator()(Trace<CustomMetricsUpdate const> const &event) {
  send(R"(["CustomMetricsUpdate",{}])"sv, json::CustomMetricsUpdate{event});
}

// io::net::udp::Sender::Handler

void JSONBridge::operator()(io::net::udp::Sender::Error const &) {
  log::fatal("Unexpected"sv);
}

void JSONBridge::operator()(metrics::Writer &) {
}

template <typename... Args>
void JSONBridge::send(fmt::format_string<Args...> const &fmt, Args &&...args) {
  buffer_.clear();
  fmt::format_to(std::back_inserter(buffer_), fmt, std::forward<Args>(args)...);
  std::string_view message{std::data(buffer_), std::size(buffer_)};
  log::info<0>("{}"sv, message);
  (*sender_).send({reinterpret_cast<std::byte const *>(std::data(message)), std::size(message)});
}

}  // namespace udp_publisher
}  // namespace roq
