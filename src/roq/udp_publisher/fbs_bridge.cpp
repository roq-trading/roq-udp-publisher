/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/fbs_bridge.hpp"

#include <utility>

#include "roq/debug/hex/message.hpp"

#include "roq/fbs/api.hpp"
#include "roq/fbs/encode.hpp"

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

FBSBridge::FBSBridge(io::Context &context)
    : context_(context), sender_(create_sender(*this, context_)),
      session_id_(core::clock::GetRealTime<std::chrono::seconds>().count()), encoder_(4096) {
}

// server::Hook

void FBSBridge::operator()(Trace<TopOfBook const> const &event) {
  send(event);
}

void FBSBridge::operator()(Trace<CustomMetricsUpdate const> const &event) {
  send(event);
}

// io::net::udp::Sender::Handler

void FBSBridge::operator()(io::net::udp::Sender::Error const &) {
  log::fatal("Unexpected"sv);
}

void FBSBridge::operator()(metrics::Writer &) {
}

template <typename T>
void FBSBridge::send(Trace<T> const &event) {
  auto &[trace_info, value] = event;
  MessageInfo message_info{
      .source = {},
      .source_name = {},
      .source_session_id = {},
      .source_seqno = {},
      .receive_time_utc = {},  // XXX
      .receive_time = {},      // XXX
      .source_send_time = {},
      .source_receive_time = trace_info.source_receive_time,
      .origin_create_time = trace_info.origin_create_time,
      .origin_create_time_utc = trace_info.origin_create_time_utc,
      .is_last = true,
      .opaque = {},
  };
  Event event_2{message_info, value};
  auto payload = encoder_(event_2);
  // log::debug("{}"sv, debug::hex::Message{payload});
  if (std::size(payload) > core::udp::MAX_PAYLOAD_LENGTH)
    log::fatal("Unsupported"sv);
  core::udp::Frame frame{
      .magic = core::udp::MAGIC,
      .encoding = core::udp::Encoding::FLATBUFFERS,
      .total_fragments = 1,
      .fragment_number = 0,
      .source_session_id = session_id_,
      .source_seqno = ++seqno_,
      .source_sending_time_utc = core::clock::GetRealTime<std::chrono::nanoseconds>().count(),
  };
  std::array<std::span<std::byte const>, 2> data{{
      frame,
      payload,
  }};
  (*sender_).send(data);
}

}  // namespace udp_publisher
}  // namespace roq
