#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cqcppsdk/cqcppsdk.h>

#include "group_timer.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;


namespace xmalloc {
    vector<string> cmds = {"start", "stop"};
    
    
    void processChuxinMessage(string message);
    
    void tiaoxiCmd(const PrivateMessageEvent &event){
        string command = event.message;
        // logging::info_success("zhch", "命令 is: --" + command + "--" );


        vector<string>::iterator it;        
        it=find(cmds.begin(),cmds.end(),command);
        
        if (it == cmds.end()){
            return;
        }

        event.block(); // 处理过的消息就不给其它应用处理了

        if(command == "stop"){
            stopTiaoxi();
            send_message(event.target, MessageSegment::face(111) + "无聊线程关闭.");
        }else if (command == "start"){
            startTiaoxiThread();
            send_message(event.target, MessageSegment::face(111) + "无聊线程启动.");
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