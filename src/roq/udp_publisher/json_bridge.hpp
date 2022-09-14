/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include "roq/io/context.hpp"

#include "roq/udp_publisher/bridge.hpp"

namespace roq {
namespace udp_publisher {

class JSONBridge final : public Bridge {
 public:
  explicit JSONBridge(io::Context &);

 protected:
  // server::Hook
  void operator()(Trace<TopOfBook const> const &) override;
  void operator()(Trace<CustomMetricsUpdate const> const &) override;

  template <typename... Args>
  void dispatch(fmt::format_string<Args...> const &, Args &&...);

 private:
  std::vector<char> buffer_;
};

}  // namespace udp_publisher
}  // namespace roq
