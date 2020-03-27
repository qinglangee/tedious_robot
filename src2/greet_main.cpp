#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include <cqcppsdk/cqcppsdk.h>
#include <windows.h>

#include "greet.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;



CQ_INIT {
    on_enable([] { 
        logging::info("启用", "迎新插件已启用"); 
    });

    

    on_group_member_increase([](const GroupMemberIncreaseEvent &event){
        logging::info("迎新", "收到  on_group_member_increase");
        try {
            xmalloc::greet(event);
        } catch (ApiError &err) { // 忽略发送失败
            logging::warning("新人", "迎新消息失败, 错误码: " + to_string(err.code));
        }
    });

    on_group_message([](const GroupMessageEvent &event) {
        static const set<int64_t> ENABLED_GROUPS = {132847879, 1234567};
        if (ENABLED_GROUPS.count(event.group_id) == 0) return; // 不在启用的群中, 忽略

        try {
            if(event.user_id == 61804888666){
                GroupMemberIncreaseEvent ee = {event.user_id, event.group_id, event.user_id, GroupMemberIncreaseEvent::SubType::APPROVE};
                xmalloc::greet(ee);

                // for(int i=0;i<8;i++){
                //     string msg = "";
                //     for(int j=0;j<10;j++){
                //         int id = i * 10 + j + 1;
                //         msg = msg + to_string(id) + " [CQ:face,id=" + to_string(id)+ "] ";
                //         // msg = msg + to_string(id) + " [CQ:sface,id=" + to_string(id)+ "] " + " [CQ:face,id=" + to_string(id)+ "] ";
                //     }
                //     send_group_message(event.group_id, msg); // 发送群消息
                // }
            }
            
        } catch (ApiError &err) { // 忽略发送失败
            logging::warning("群聊", "群聊消息瞎JB处理失败了, 错误码: " + to_string(666666));
        }
        if (event.is_anonymous()) {
            logging::info("群聊", "消息是匿名消息, 匿名昵称: " + event.anonymous.name);
        }
        // event.block(); // 阻止当前事件传递到下一个插件
    });

}

CQ_MENU(menu_demo_1) {
    logging::info("菜单", "点击菜单1");
}

CQ_MENU(menu_demo_2) {
    logging::info("菜单", "点击菜单2");
}



