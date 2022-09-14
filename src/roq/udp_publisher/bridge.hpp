/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include "roq/server.hpp"

#include "roq/io/context.hpp"

#include "roq/io/net/udp/sender.hpp"

#include "roq/io/sys/timer.hpp"

#include "roq/core/udp/frame.hpp"

#include "roq/udp_publisher/bridge.hpp"

namespace roq {
namespace udp_publisher {

struct Bridge : public server::Hook, public io::sys::Timer::Handler, public io::net::udp::Sender::Handler {
  Bridge(io::Context &, core::udp::Encoding);

  virtual ~Bridge() {}

 protected:
  // io::sys::Timer::Handler
  void operator()(io::sys::Timer::Event const &) override;

  // io::net::udp::Sender::Handler
  void operator()(io::net::udp::Sender::Error const &) override;

  void operator()(metrics::Writer &);

  void send(std::span<std::byte const> const &payload);

 private:
  io::Context &context_;
  const std::unique_ptr<io::sys::Timer> timer_;
  const std::unique_ptr<io::Sender> sender_;
  const uint32_t session_id_ = {};
  uint32_t seqno_ = {};
  core::udp::Encoding const encoding_ = {};
  std::chrono::nanoseconds next_heartbeat_ = {};
};

}  // namespace udp_publisher
}  // namespace roq
