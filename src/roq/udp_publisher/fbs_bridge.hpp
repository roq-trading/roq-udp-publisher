/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include "roq/core/fbs/encoder.hpp"

#include "roq/udp_publisher/bridge.hpp"

namespace roq {
namespace udp_publisher {

struct FBSBridge final : public Bridge {
  explicit FBSBridge(io::Context &context);

 protected:
  // server::Hook
  void operator()(Trace<TopOfBook const> const &) override;
  void operator()(Trace<CustomMetricsUpdate const> const &) override;

  template <typename T>
  void dispatch(Trace<T> const &);

 private:
  core::fbs::Encoder encoder_;
};

}  // namespace udp_publisher
}  // namespace roq
