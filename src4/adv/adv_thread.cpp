#pragma once

#include <string>
#include <process.h>

#include <cqcppsdk/cqcppsdk.h>
#include <windows.h>

#include <vector>

#include "CJsonObject.hpp"

#include <sys_util.hpp>
#include "group.hpp"

using namespace xmalloc;
using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;


namespace xmalloc::adv{
    bool running = false;


    unsigned int __stdcall advSendThread(void *pPM);
    unsigned int __stdcall groupInfoCheckThread(void *pPM);

    // 启动处理广告发送的线程
    void startAdvThread(){
        if(running){
            logging::info("zhch", "优惠播放处理线程已经在运行。");
            return;
        }

        _beginthreadex(NULL, 0, advSendThread, NULL, 0, NULL);
    }

    // 启动处理广告发送的线程
    void stopAdvThread(){
        running = false;
        logging::info("zhch", "停止了优惠播放处理线程。");
    }

    // 启动群员信息检测
    void startGroupInfoCheck(){
        _beginthreadex(NULL, 0, groupInfoCheckThread, NULL, 0, NULL);
    }

    // 群员信息检测
    unsigned int __stdcall groupInfoCheckThread(void *pPM){
        xutils::sys::sleep(3000); // 停一会，错过启动信息高峰。

        logging::info_success("S线程开始", "优惠播放-启动群员信息检测。");
        vector<Group> groups = get_group_list();
        for(int i=0;i<groups.size();i++){
            xutils::sys::sleep(1000); // 停一会，调用API不是太频繁。
            Group g = groups[i];
            logging::info("群组", to_string(g.group_id) + " " + g.group_name + " num:" + to_string(g.member_count));
            Group info = get_group_info(g.group_id);
            logging::info("群组", "num: " + to_string(info.member_count));

            // 读取群组信息
            neb::CJsonObject groupJson = group::readGroupMembers(info.group_id);
            int32_t count;
            groupJson.Get("member_count", count);

            if(info.member_count != count){
                logging::info("zhch", "count is: " + to_string(count));
                // 组员信息
                vector<GroupMember> members = get_group_member_list(info.group_id);
                group::writeGroupMembers(info, members);
                
            }

        }

        logging::info_success("E线程结束", "优惠播放-群员信息检测结束。");
        return 0;
    }

    // 处理广告发送的线程
    unsigned int __stdcall advSendThread(void *pPM){
        running = true;

        logging::info_success("S线程开始", "启动了优惠播放处理线程。");
        while(running){

            logging::info("zhch", "发送优惠。");
            xutils::sys::sleep(3000);
        }

        logging::info_success("E线程结束", "优惠播放循环结束，退出。");

        return 0;
    }
}