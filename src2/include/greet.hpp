#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cqcppsdk/cqcppsdk.h>



using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

namespace xmalloc{
    void greet(const GroupMemberIncreaseEvent &event);
}