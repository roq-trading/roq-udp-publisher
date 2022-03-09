/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/pubsub/gateway.hpp"

#include "roq/logging.hpp"

#include "roq/pubsub/flags.hpp"

using namespace std::literals;

namespace roq {
namespace pubsub {

Gateway::Gateway(server::Dispatcher &dispatcher, const Config &)
    : dispatcher_(dispatcher), shared_(dispatcher) {
}

void Gateway::operator()(const Event<Start> &) {
  log::info("Starting the gateway..."sv);
}

void Gateway::operator()(const Event<Stop> &) {
  log::info("Stopping the gateway..."sv);
}

void Gateway::operator()(const Event<Timer> &) {
  context_.dispatch(true);
}

void Gateway::operator()(const Event<Connected> &) {
}

void Gateway::operator()(const Event<Disconnected> &) {
}

uint16_t Gateway::operator()(
    const Event<CreateOrder> &,
    const oms::Order &,
    [[maybe_unused]] const std::string_view &request_id) {
  throw oms::NotSupported("not supported"sv);
}

uint16_t Gateway::operator()(
    const Event<ModifyOrder> &,
    const oms::Order &,
    [[maybe_unused]] const std::string_view &request_id,
    [[maybe_unused]] const std::string_view &previous_request_id) {
  throw oms::NotSupported("not supported"sv);
}

uint16_t Gateway::operator()(
    const Event<CancelOrder> &,
    const oms::Order &,
    [[maybe_unused]] const std::string_view &request_id,
    [[maybe_unused]] const std::string_view &previous_request_id) {
  throw oms::NotSupported("not supported"sv);
}

uint16_t Gateway::operator()(
    const Event<CancelAllOrders> &, [[maybe_unused]] const std::string_view &request_id) {
  throw oms::NotSupported("not supported"sv);
}

void Gateway::operator()(metrics::Writer &) {
}

}  // namespace pubsub
}  // namespace roq
