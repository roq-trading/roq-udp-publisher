/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/bridge.hpp"

#include <utility>

#include "roq/logging.hpp"

#include "roq/core/clock.hpp"

#include "roq/core/udp/frame.hpp"

#include "roq/udp_publisher/flags.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

namespace {
auto create_timer(auto &handler, auto &context) {
  return context.create_timer(handler, 3s);
}
auto create_sender(auto &handler, auto &context) {
  return context.create_udp_sender(handler, io::NetworkAddress{Flags::udp_port()});
}
}  // namespace

Bridge::Bridge(io::Context &context, core::udp::Encoding encoding)
    : context_(context), timer_(create_timer(*this, context_)), sender_(create_sender(*this, context_)),
      session_id_(core::clock::GetRealTime<std::chrono::seconds>().count()), encoding_(encoding) {
}

// io::net::sys::Timer::Handler

void Bridge::operator()(io::sys::Timer::Event const &) {
  log::debug("HERE"sv);
  send();  // heartbeat
}

// io::net::udp::Sender::Handler

void Bridge::operator()(io::net::udp::Sender::Error const &) {
  log::fatal("Unexpected"sv);
}

void Bridge::operator()(metrics::Writer &) {
}

void Bridge::send() {
  core::udp::Frame frame{
      .magic = core::udp::MAGIC,
      .encoding = encoding_,
      .total_fragments = 1,
      .fragment_number = 0,
      .source_session_id = session_id_,
      .source_seqno = ++seqno_,
      .source_sending_time_utc = core::clock::GetRealTime<std::chrono::nanoseconds>().count(),
  };
  (*sender_).send(frame);
}

void Bridge::send(std::span<std::byte const> const &payload) {
  // log::debug("{}"sv, debug::hex::Message{payload});
  if (std::size(payload) > core::udp::MAX_PAYLOAD_LENGTH)
    log::fatal("Unsupported"sv);
  core::udp::Frame frame{
      .magic = core::udp::MAGIC,
      .encoding = encoding_,
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
