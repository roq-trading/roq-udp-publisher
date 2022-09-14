/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/bridge.hpp"

#include <algorithm>
#include <utility>

#include "roq/utils/safe_cast.hpp"

#include "roq/logging.hpp"

#include "roq/core/clock.hpp"

#include "roq/core/udp/frame.hpp"

#include "roq/udp_publisher/flags.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

namespace {
auto create_timer(auto &handler, auto &context) {
  return context.create_timer(handler, 1s);
}
auto create_sender(auto &handler, auto &context) {
  return context.create_udp_sender(handler, io::NetworkAddress{Flags::udp_port()});
}
}  // namespace

Bridge::Bridge(io::Context &context, core::udp::Encoding encoding)
    : context_(context), timer_(create_timer(*this, context_)), sender_(create_sender(*this, context_)),
      session_id_(core::clock::GetRealTime<std::chrono::seconds>().count()), encoding_(encoding) {
  (*timer_).resume();
}

// io::net::sys::Timer::Handler

void Bridge::operator()(io::sys::Timer::Event const &event) {
  if (event.now < next_heartbeat_)
    return;
  next_heartbeat_ = event.now + flags::Flags::heartbeat_freq();
  // send heartbeat (empty payload)
  core::udp::Frame frame{
      .magic = core::udp::MAGIC,
      .encoding = encoding_,
      .fragment_number = {},
      .fragment_number_max = {},
      .source_session_id = session_id_,
      .source_seqno = ++seqno_,
      .source_sending_time_utc = core::clock::GetRealTime<std::chrono::nanoseconds>().count(),
  };
  (*sender_).send(frame);
}

// io::net::udp::Sender::Handler

void Bridge::operator()(io::net::udp::Sender::Error const &) {
  log::fatal("Unexpected"sv);
}

void Bridge::operator()(metrics::Writer &) {
}

namespace {
constexpr auto divide_round_up(auto x, auto y) {
  // https://stackoverflow.com/a/2745086
  assert(x != 0);
  return 1 + ((x - 1) / y);
}
static_assert(divide_round_up(10, 4) == 3);
static_assert(divide_round_up(11, 4) == 3);
static_assert(divide_round_up(12, 4) == 3);
static_assert(divide_round_up(13, 4) == 4);
}  // namespace

void Bridge::send(std::span<std::byte const> const &payload) {
  // log::debug("{}"sv, debug::hex::Message{payload});
  if (std::empty(payload))
    return;
  if (std::size(payload) > core::udp::MAX_PAYLOAD_LENGTH)  // XXX DEBUG
    log::fatal("Unsupported"sv);
  auto total_fragments = divide_round_up(std::size(payload), core::udp::MAX_PAYLOAD_LENGTH);
  assert(total_fragments > 0);
  core::udp::Frame frame{
      .magic = core::udp::MAGIC,
      .encoding = encoding_,
      .fragment_number = {},
      .fragment_number_max = utils::safe_cast{total_fragments - 1},
      .source_session_id = session_id_,
      .source_seqno = ++seqno_,
      .source_sending_time_utc = core::clock::GetRealTime<std::chrono::nanoseconds>().count(),
  };
  for (size_t index = 0;; ++index) {
    auto offset = index * core::udp::MAX_PAYLOAD_LENGTH;
    if (std::size(payload) <= offset)
      break;
    frame.fragment_number = utils::safe_cast{index};
    auto bytes = std::min(std::size(payload) - offset, core::udp::MAX_PAYLOAD_LENGTH);
    auto payload_2 = payload.subspan(offset, bytes);
    std::array<std::span<std::byte const>, 2> data{{
        frame,
        payload_2,
    }};
    (*sender_).send(data);
  }
  assert(frame.fragment_number == frame.fragment_number_max);
}

}  // namespace udp_publisher
}  // namespace roq
