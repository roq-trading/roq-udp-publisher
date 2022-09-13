/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include "roq/server.hpp"

#include "roq/core/fbs/encoder.hpp"

#include "roq/io/context.hpp"

#include "roq/io/net/udp/sender.hpp"

#include "roq/udp_publisher/bridge.hpp"

namespace roq {
namespace udp_publisher {

class FBSBridge final : public Bridge, public io::net::udp::Sender::Handler {
 public:
  explicit FBSBridge(io::Context &);

 protected:
  // server::Hook
  void operator()(Trace<TopOfBook const> const &) override;
  void operator()(Trace<CustomMetricsUpdate const> const &) override;

  // io::net::udp::Sender::Handler
  void operator()(io::net::udp::Sender::Error const &) override;

  void operator()(metrics::Writer &);

  template <typename T>
  void send(Trace<T> const &);

 private:
  io::Context &context_;
  const std::unique_ptr<io::Sender> sender_;
  const uint32_t session_id_ = {};
  uint32_t seqno_ = {};
  core::fbs::Encoder encoder_;
};

}  // namespace udp_publisher
}  // namespace roq
