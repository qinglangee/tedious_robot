#include <iostream>
#include <sstream>
#include <string>
#include <cqcppsdk/cqcppsdk.h>

#include "tiaoxi.hpp"


using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;


namespace xmalloc {
    
    void forwardGroupMessage(const PrivateMessageEvent &event);

    void processMessage(const PrivateMessageEvent &event) {
        

        if(event.message.find_first_of("r ") == 0){

            auto msgid = send_private_message(event.user_id, event.message); // 直接复读消息
            logging::info_success("私聊", "私聊消息复读完成, 消息 Id: " + to_string(msgid));
            auto msgid2 = send_message(event.target,
                        MessageSegment::face(111) + "这是通过 message 模块构造的消息~"); // 使用 message 模块构造消息
            logging::info_success("私聊", "私聊消息复读完成, 消息 Id: " + to_string(msgid2));
        }else if(event.message.find_first_of("!") == 0){
            forwardGroupMessage(event);
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
        int64_t blenderCaiji = 770876213;  // blender 菜鸡互啄群

        string groupIdStr = event.message.substr(1, spaceIndex - 1);
        int64_t groupId;
        if(groupIdStr == "0"){
            groupId = invincible;
        }else if(groupIdStr == "1"){
            groupId = 479646367;  // 初心诠释 预备队
            forwardChuxinMessage(event);
            return;
        }else if(groupIdStr == "2"){
            groupId = blenderCaiji;
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



}

