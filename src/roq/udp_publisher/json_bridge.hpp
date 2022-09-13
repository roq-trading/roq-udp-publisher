/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include "roq/server.hpp"

#include "roq/io/context.hpp"

#include "roq/io/net/udp/sender.hpp"

#include "roq/udp_publisher/bridge.hpp"

namespace roq {
namespace udp_publisher {

class JSONBridge final : public Bridge, public io::net::udp::Sender::Handler {
 public:
  explicit JSONBridge(io::Context &);

 protected:
  // server::Hook
  void operator()(Trace<TopOfBook const> const &) override;
  void operator()(Trace<CustomMetricsUpdate const> const &) override;

  // io::net::udp::Sender::Handler
  void operator()(io::net::udp::Sender::Error const &) override;

  void operator()(metrics::Writer &);

  template <typename... Args>
  void send(fmt::format_string<Args...> const &, Args &&...);

 private:
  io::Context &context_;
  const std::unique_ptr<io::Sender> sender_;
  const uint32_t session_id_ = {};
  uint32_t seqno_ = {};
  std::vector<char> buffer_;
};

}  // namespace udp_publisher
}  // namespace roq
