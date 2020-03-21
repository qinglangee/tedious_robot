#include <iostream>
#include <sstream>
#include <string>
#include <cqcppsdk/cqcppsdk.h>

#include "group_timer.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;


namespace xmalloc {
    
    void forwardGroupMessage(const PrivateMessageEvent &event);
    void forwardCommandMessage(const PrivateMessageEvent &event);
    void forwardChuxinMessage(const PrivateMessageEvent &event);
    void processChuxinMessage(string message);

    void processMessage(const PrivateMessageEvent &event) {
        if(event.user_id != 61804888){
            logging::info_success("zhch", "杂鱼命令 id: " + to_string(event.user_id) );
            return;
        }

        if(event.message.find_first_of("r ") == 0){

            auto msgid = send_private_message(event.user_id, event.message); // 直接复读消息
            logging::info_success("私聊", "私聊消息复读完成, 消息 Id: " + to_string(msgid));
            auto msgid2 = send_message(event.target,
                        MessageSegment::face(111) + "这是通过 message 模块构造的消息~"); // 使用 message 模块构造消息
            logging::info_success("私聊", "私聊消息复读完成, 消息 Id: " + to_string(msgid2));
        }else if(event.message.find_first_of("!") == 0){
            forwardGroupMessage(event);
        }else if(event.message.find_first_of("#") == 0){
            forwardCommandMessage(event);
        }else if(event.message.find_first_of("cmd ") == 0){
            auto groups = get_group_list();
            for(size_t i = 0; i < groups.size(); i++){
                cq::Group g = groups[i];
                logging::info_success("zhch", "群名字: " + to_string(g.group_name));

                auto members = get_group_member_list(g.group_id);
                for(size_t j = 0; j < members.size(); j++){
                    cq::GroupMember m = members[j];
                    logging::info_success("zhch", "群员名字: " + to_string(m.nickname) + " qq号：" + to_string(m.user_id));
                }
            }
        }

        
        send_message(event.target, MessageSegment::face(111) + "完毕." + event.message);
    }

    // 转发到群的消息
    void forwardGroupMessage(const PrivateMessageEvent &event){
        size_t spaceIndex = event.message.find(" ");
        if(spaceIndex == string::npos){
            send_message(event.target, MessageSegment::face(110) + "错误:" + event.message);
            return;
        }

        int64_t invincible = 132847879;  // invincible no 学生会

        string groupIdStr = event.message.substr(1, spaceIndex - 1);
        int64_t groupId;
        if(groupIdStr == "0"){
            groupId = invincible;
        }else if(groupIdStr == "1"){
            groupId = 479646367;  // 初心诠释 预备队
            forwardChuxinMessage(event);
            return;
        }else{
            groupId = stoll(groupIdStr, 0, 10);
        }

        string msg = event.message.substr(spaceIndex + 1);

        // 需要 at 某人
        if(msg.find("@") == 0){
            spaceIndex = msg.find(" ");
            if(spaceIndex != string::npos){
                string atIdStr = msg.substr(1, spaceIndex - 1);
                string newMsg = msg.substr(spaceIndex + 1);
                msg = "[CQ:at,qq=" + atIdStr + "] " + newMsg;

            }
        }

        // send_message(event.target, MessageSegment::face(110) + "head:" + groupIdStr + to_string(spaceIndex) + msg);
        try {
            send_group_message(groupId, msg); // 发送群消息
            
        } catch (ApiError &err) { // 忽略发送失败
            logging::warning("群聊", "群聊消息复读失败, 错误码: " + to_string(err.code));
        }
    }

    // 命令消息的处理
    void forwardCommandMessage(const PrivateMessageEvent &event){
        string command = event.message.substr(1);
        if(command == "stop"){
            stopTiaoxi();
        }else if (command == "start"){
            startTiaoxiThread();
        }
    }
    // 初心预备队消息单独处理
    void forwardChuxinMessage(const PrivateMessageEvent &event){
        processChuxinMessage(event.message);

    }
    void processChuxinMessage(string message){
        if(message.find("!") == string::npos){
            return;
        }
        int64_t groupId = 479646367; // 初心预备队
        // int64_t groupId = 132847879; // 学生会
        size_t spaceIndex = 2;

        string msg = message.substr(spaceIndex + 1);

        // 需要 at 某人
        if(msg.find("@") == 0){
            spaceIndex = msg.find(" ");
            if(spaceIndex != string::npos){
                string atIdStr = msg.substr(1, spaceIndex - 1);
                if(atIdStr == "1"){
                    atIdStr = "3039744519";
                }

                string newMsg = msg.substr(spaceIndex + 1);
                string convertMsg = newMsg;
                if(newMsg == "0"){
                    convertMsg = "梦月查指令";
                }else if(newMsg == "1"){
                    convertMsg = "资料";
                }else if(newMsg == "2"){
                    convertMsg = "抽签";
                }else if(newMsg.find("3") == 0){
                    convertMsg = "锻炼" + newMsg.substr(1);
                }else if(newMsg.find("4") == 0){
                    convertMsg = "打工" + newMsg.substr(1);
                }



                msg = "[CQ:at,qq=" + atIdStr + "] " + convertMsg;

            }
        }

        try {
            send_group_message(groupId, msg); // 发送群消息
            
        } catch (ApiError &err) { // 忽略发送失败
            logging::warning("群聊", "群聊消息复读失败, 错误码: " + to_string(err.code));
        }
    }


}

