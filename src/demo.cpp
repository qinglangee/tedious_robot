#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include <cqcppsdk/cqcppsdk.h>

#include "command.hpp"
#include "group_timer.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;



CQ_INIT {
    on_enable([] { 
        xmalloc::startTiaoxiThread();
        logging::info("启用", "插件已启用"); 
    });

    on_private_message([](const PrivateMessageEvent &event) {
        try {
            
            xmalloc::processMessage(event);
        } catch (ApiError &err) {
            logging::warning("私聊", "私聊消息处理出错, 错误码: " + to_string(err.code));
        }
    });

    on_message([](const MessageEvent &event) {
        logging::debug("消息", "收到消息: " + event.message + "\n实际类型: " + typeid(event).name());
    });

    on_group_message([](const GroupMessageEvent &event) {
        static const set<int64_t> ENABLED_GROUPS = {132847879, 1234567};
        if (ENABLED_GROUPS.count(event.group_id) == 0) return; // 不在启用的群中, 忽略

        try {
            // send_message(event.target, event.message); // 复读
            // auto mem_list = get_group_member_list(event.group_id); // 获取群成员列表
            // string msg;
            // for (auto i = 0; i < min(10, static_cast<int>(mem_list.size())); i++) {
            //     msg += "昵称: " + mem_list[i].nickname + "\n"; // 拼接前十个成员的昵称
            // }
            // send_group_message(event.group_id, "see you"); // 发送群消息
            // send_group_message(132847879, "next time"); // 发送群消息
        } catch (ApiError &err) { // 忽略发送失败
            logging::warning("群聊", "群聊消息复读失败, 错误码: " + to_string(err.code));
        }
        if (event.is_anonymous()) {
            logging::info("群聊", "消息是匿名消息, 匿名昵称: " + event.anonymous.name);
        }
        // event.block(); // 阻止当前事件传递到下一个插件
    });

    on_group_upload([](const auto &event) { // 可以使用 auto 自动推断类型
        // stringstream ss;
        // ss << "您上传了一个文件, 文件名: " << event.file.name << ", 大小(字节): " << event.file.size;
        // try {
        //     send_message(event.target, ss.str());
        // } catch (ApiError &) {
        // }
    });
}

CQ_MENU(menu_demo_1) {
    logging::info("菜单", "点击菜单1");
}

CQ_MENU(menu_demo_2) {
    logging::info("菜单", "点击菜单2");
}



