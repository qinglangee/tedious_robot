#pragma once

#include <cqcppsdk/cqcppsdk.h>



using namespace cq;
using namespace std;

namespace xmalloc::adv{
    // adv_send.cpp
    void advCmd(const PrivateMessageEvent &event);

    // adv_thread.cpp
    void startAdvThread();
    void stopAdvThread();
    void startGroupInfoCheck();
}