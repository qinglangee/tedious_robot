#pragma once

#include <string>
#include <cqcppsdk/cqcppsdk.h>

#include "adv.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

/**
 * 现有的命令 命令结构  adv cmd
 * start 123456 ：给群 123456 的群员发送优惠信息
 * end : 结束发送的线程
 * check : 检查群信息同步
 * 
*/
namespace xmalloc::adv{
    void advCmd(const PrivateMessageEvent &event){

        if (event.message.find("adv ") != 0) return; // 不以 adv 开头的, 忽略

        event.block();

        string cmd = event.message.substr(4);

        if(cmd.find("start") == 0){
            startAdvThread(cmd);
            send_message(event.target, MessageSegment::face(111) + "优惠播放线程开启.");
        }else if(cmd.find("end") == 0 ){
            stopAdvThread();
            send_message(event.target, MessageSegment::face(111) + "优惠播放线程关闭.");
        }else{

            send_message(event.target, MessageSegment::face(111) + "不识别的优惠播放命令.");
        }

        logging::info("zhch", "优惠播放命令处理完毕。"); 

    }
}