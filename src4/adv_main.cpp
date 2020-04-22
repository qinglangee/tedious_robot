#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include <cqcppsdk/cqcppsdk.h>

#include "adv.hpp"
#include "zhlog.hpp"


using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;



CQ_INIT {
    on_enable([] { 
        xmalloc::log::ZhLog::logFile = get_app_directory() + "log/output.txt";
        xmalloc::adv::startGroupInfoCheck();
        logging::info("启用", "优惠播放机插件已启用"); 
        
    });

    on_private_message([](const PrivateMessageEvent &event) {
        try {
            if(event.user_id != 61804888){
                return;
            }
            xmalloc::adv::advCmd(event);
        } catch (ApiError &err) {
            logging::warning("私聊", "优惠播放机命令处理出错, 错误码: " + to_string(err.code));
        }
    });


    on_group_message([](const GroupMessageEvent &event) {
        
    });

}

CQ_MENU(menu_demo_1) {
    logging::info("菜单", "点击菜单1");
}

CQ_MENU(menu_demo_2) {
    logging::info("菜单", "点击菜单2");
}



