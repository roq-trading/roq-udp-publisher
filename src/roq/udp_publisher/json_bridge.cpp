/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/json_bridge.hpp"

#include <utility>

#include "roq/logging.hpp"

#include "roq/json/custom_metrics_update.hpp"
#include "roq/json/top_of_book.hpp"

#include "roq/core/clock.hpp"

#include "roq/core/udp/frame.hpp"

#include "roq/udp_publisher/flags.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

namespace {
auto create_sender(auto &handler, auto &context) {
  return context.create_udp_sender(handler, io::NetworkAddress{Flags::udp_port()});
}
}  // namespace

JSONBridge::JSONBridge(io::Context &context)
    : context_(context), sender_(create_sender(*this, context_)),
      session_id_(core::clock::GetRealTime<std::chrono::seconds>().count()) {
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
  std::string_view payload{std::data(buffer_), std::size(buffer_)};
  // log::debug("{}"sv, payload);
  if (std::size(payload) > core::udp::MAX_PAYLOAD_LENGTH)
    log::fatal("Unsupported"sv);
  core::udp::Frame frame{
      .magic = core::udp::MAGIC,
      .encoding = core::udp::Encoding::JSON,
      .total_fragments = 1,
      .fragment_number = 0,
      .source_session_id = session_id_,
      .source_seqno = ++seqno_,
      .source_sending_time_utc = core::clock::GetRealTime<std::chrono::nanoseconds>().count(),
  };
  std::array<std::span<std::byte const>, 2> data{{
      frame,
      {reinterpret_cast<std::byte const *>(std::data(payload)), std::size(payload)},
  }};
  (*sender_).send(data);
}

}  // namespace udp_publisher
}  // namespace roq
