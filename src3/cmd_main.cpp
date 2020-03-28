#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include <cqcppsdk/cqcppsdk.h>

#include "command.hpp"
#include "group_at.hpp"
#include "message_util.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;



CQ_INIT {
    on_enable([] { 
        logging::info("启用", "命令聊天插件已启用"); 
        
    });

    on_private_message([](const PrivateMessageEvent &event) {
        try {
            if(event.user_id != 61804888){
                logging::info_success("zhch", "杂鱼命令 id: " + to_string(event.user_id) );
                return;
            }
            xmalloc::processMessage(event);
        } catch (ApiError &err) {
            logging::warning("私聊", "私聊消息处理出错, 错误码: " + to_string(err.code));
        }
    });

    on_message([](const MessageEvent &event) {
        logging::debug("消息", "收到消息: " + event.message + "\n实际类型: " + typeid(event).name());
    });

    on_group_message([](const GroupMessageEvent &event) {
        int64_t selfId = 3556607653;  // 小软软 ID

        try {
            Message m = Message(event.message);
            
            // 处理 @小软软的消息
            if(xmalloc::messageAt(m, selfId)){
                logging::info_success("zhch", "m: " + event.message );
                
                xmalloc::responseAtMessage(event);
            }
            
            
        } catch (ApiError &err) { // 忽略发送失败
            logging::warning("群聊", "群聊消息复读失败, 错误码: " + to_string(err.code));
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



