#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include <cqcppsdk/cqcppsdk.h>

#include "adv.hpp"
#include "zhlog.hpp"
#include "base_dao.hpp"


using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

using zhl = xmalloc::log::ZhLog;



CQ_INIT {
    on_enable([] { 
        xmalloc::log::ZhLog::logFile = get_app_directory() + "log/output.txt";
        xmalloc::log::ZhLog::level = xmalloc::log::Level::INFO;
        xmalloc::adv::Config::dbFile = "adv.db";


        // 这个改为命令调用了，测试时可以打开
        // xmalloc::adv::startGroupInfoCheck();

        zhl::info("启用", "优惠播放机插件已启用"); 
        
    });

    on_private_message([](const PrivateMessageEvent &event) {
        try {
            if(event.user_id != 61804888){
                return;
            }
            xmalloc::adv::advCmd(event);
        } catch (ApiError &err) {
            zhl::warning("私聊", "优惠播放机命令处理出错, 错误码: " + to_string(err.code));
        }
    });

    
    on_group_member_increase([](const GroupMemberIncreaseEvent &event){
        zhl::info("迎新", "收到新群员 " + to_string(event.group_id) + "-" + to_string(event.user_id));
        try {
            xmalloc::adv::groupMemberIncrease(event);
        } catch (ApiError &err) { // 忽略发送失败
            zhl::warning("优惠", "优惠新人增加处理失败, 错误码: " + to_string(err.code));
        }
    });
    
    on_group_member_decrease([](const GroupMemberDecreaseEvent &event){
        zhl::info("送旧", "收到退群 "  + to_string(event.group_id) + "-" + to_string(event.user_id));
        try {
            xmalloc::adv::groupMemberDecrease(event);
        } catch (ApiError &err) { // 忽略发送失败
            zhl::warning("优惠", "优惠旧人减少处理失败, 错误码: " + to_string(err.code));
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



