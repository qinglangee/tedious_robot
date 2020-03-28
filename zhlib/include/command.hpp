#pragma once
#include <cqcppsdk/cqcppsdk.h>

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

namespace xmalloc {
    void processMessage(const PrivateMessageEvent &event);
    void processChuxinMessage(string message);
}
