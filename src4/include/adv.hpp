#pragma once

#include <cqcppsdk/cqcppsdk.h>



using namespace cq;
using namespace std;

namespace xmalloc::adv{
    // file  =========== adv_send.cpp ============
    void advCmd(const PrivateMessageEvent &event);

    
    // file  =========== adv_thread.cpp ============
    void startAdvThread(string cmd);
    void stopAdvThread();
    void startGroupInfoCheck();

    // file  =========== adv_member.cpp ============
    // 群员增加
    void groupMemberIncrease(const GroupMemberIncreaseEvent &event);
    // 群员减少
    void groupMemberDecrease(const GroupMemberDecreaseEvent &event);
}