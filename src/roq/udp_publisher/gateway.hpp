/* Copyright (c) 2017-2025, Hans Erik Thrane */

#pragma once

#include "roq/server.hpp"

#include "roq/io/context.hpp"

#include "roq/udp_publisher/config.hpp"
#include "roq/udp_publisher/settings.hpp"
#include "roq/udp_publisher/shared.hpp"

namespace roq {
namespace udp_publisher {

struct Gateway final : public server::Handler {
  Gateway(server::Dispatcher &, Settings const &, Config const &, io::Context &);

  Gateway(Gateway const &) = delete;

 protected:
  void operator()(Event<Start> const &) override;
  void operator()(Event<Stop> const &) override;
  void operator()(Event<Timer> const &) override;
  void operator()(Event<Control> const &) override;
  void operator()(Event<Connected> const &) override;
  void operator()(Event<Disconnected> const &) override;

  uint16_t operator()(Event<CreateOrder> const &, server::oms::Order const &, std::string_view const &request_id) override;
  uint16_t operator()(
      Event<ModifyOrder> const &, server::oms::Order const &, std::string_view const &request_id, std::string_view const &previous_request_id) override;
  uint16_t operator()(
      Event<CancelOrder> const &, server::oms::Order const &, std::string_view const &request_id, std::string_view const &previous_request_id) override;

  uint16_t operator()(Event<CancelAllOrders> const &, std::string_view const &request_id) override;

  uint16_t operator()(Event<MassQuote> const &) override;

  uint16_t operator()(Event<CancelQuotes> const &) override;

  void operator()(metrics::Writer &) const override;

 private:
  server::Dispatcher &dispatcher_;
  Shared shared_;
};

}  // namespace udp_publisher
}  // namespace roq
