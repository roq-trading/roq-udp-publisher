/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include "roq/server.hpp"

#include "roq/io/context.hpp"

#include "roq/io/net/udp/sender.hpp"

namespace roq {
namespace udp_publisher {

class Bridge final : public server::Hook, public io::net::udp::Sender::Handler {
 public:
  Bridge(io::Context &);

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
  std::vector<char> buffer_;
};

}  // namespace udp_publisher
}  // namespace roq
