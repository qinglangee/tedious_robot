#include <iostream>
#include <sstream>
#include <string>
#include <process.h>
#include <windows.h>

#include <cqcppsdk/cqcppsdk.h>

#include "command.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

namespace xmalloc {
    void tiaoxiFun();
    void startTiaoxiThread(){
        _beginthreadex(NULL, 0, tiaoxiFun, NULL, 0, NULL);
        
        logging::info_success("启动", "启动定时线程");
    }

    // 调戏机器人
    void tiaoxiFun(){
        size_t count = 10;

        while(count){
            send_group_message(132847879, "count:" + to_string(count));
            Sleep(1500);
            count--;
        }

    }
}