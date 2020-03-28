#pragma once
#include <string>
#include <cqcppsdk/cqcppsdk.h>

using namespace cq;
using Message = cq::message::Message;

namespace xmalloc {
    bool messageAt(const Message &message, int64_t userId);
}
