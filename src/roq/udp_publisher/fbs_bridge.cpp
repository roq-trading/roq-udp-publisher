/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/udp_publisher/fbs_bridge.hpp"

#include <utility>

#include "roq/fbs/api.hpp"
#include "roq/fbs/encode.hpp"

#include "roq/logging.hpp"

#include "roq/json/custom_metrics_update.hpp"
#include "roq/json/top_of_book.hpp"

#include "roq/udp_publisher/flags.hpp"

using namespace std::literals;

namespace roq {
namespace udp_publisher {

FBSBridge::FBSBridge(io::Context &context) : Bridge(context, core::udp::Encoding::FLATBUFFERS), encoder_(4096) {
}

// server::Hook

void FBSBridge::operator()(Trace<TopOfBook> const &event) {
  dispatch(event);
}

void FBSBridge::operator()(Trace<CustomMetricsUpdate> const &event) {
  dispatch(event);
}

template <typename T>
void FBSBridge::dispatch(Trace<T> const &event) {
  auto &[trace_info, value] = event;
  MessageInfo message_info{
      .source = {},
      .source_name = {},
      .source_session_id = {},
      .source_seqno = {},
      .receive_time_utc = {},  // XXX
      .receive_time = {},      // XXX
      .source_send_time = {},
      .source_receive_time = trace_info.source_receive_time,
      .origin_create_time = trace_info.origin_create_time,
      .origin_create_time_utc = trace_info.origin_create_time_utc,
      .is_last = true,
      .opaque = {},
  };
  Event event_2{message_info, value};
  auto payload = encoder_(event_2);
  send(payload);
}

}  // namespace udp_publisher
}  // namespace roq
