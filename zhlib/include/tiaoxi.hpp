#pragma once
#include <cqcppsdk/cqcppsdk.h>

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

namespace xmalloc {
    void tiaoxiCmd(const PrivateMessageEvent &event);
    void forwardChuxinMessage(const PrivateMessageEvent &event);
}
