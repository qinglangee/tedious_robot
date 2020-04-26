#pragma once

#include <string>
#include <process.h>

#include <cqcppsdk/cqcppsdk.h>
#include <windows.h>

#include <vector>

#include "CJsonObject.hpp"

#include <sys_util.hpp>
#include "zhlog.hpp"
#include "string_util.hpp"
#include "group.hpp"
#include "adv_dao.hpp"
#include "adv_dto.hpp"

#include "tmp_filelog.hpp"

using namespace xmalloc;
using namespace cq;
using namespace std;
using namespace xmalloc::log;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

using zhl = xmalloc::log::ZhLog;
using namespace xutils::str;

namespace xmalloc::adv{
    bool running = false;
    int64_t sendGroupId = 0; // 要发送优惠的群号 0：没有 1：全部 其它：按群号来


    bool isDebug = true;  // 调试控制变量


    unsigned int __stdcall advSendThread(void *pPM);
    unsigned int __stdcall groupInfoCheckThread(void *pPM);


    // 启动处理广告发送的线程
    void startAdvThread(string cmd){
        if(running){
            logging::info("zhch", "优惠播放处理线程已经在运行。");
            return;
        }

        if(cmd.find("start ") == 0){
            string groupIdStr = cmd.substr(6);
            sendGroupId = stoll(groupIdStr, 0, 10);
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

        zhl::info_success("S线程开始", "优惠播放-启动群员信息检测。");
        try{
            vector<Group> groups = get_group_list();
            for(int i=0;i<groups.size();i++){
                xutils::sys::sleep(1000); // 停一会，调用API不要太频繁。
                Group g = groups[i];
                Group info = get_group_info(g.group_id);

                // // 读取群组信息
                // neb::CJsonObject groupJson = group::readGroupMembers(info.group_id);
                // int32_t count;
                // groupJson.Get("member_count", count);

                // if(info.member_count != count){
                //     zhl::info("群组", to_string(g.group_id) + " " + g.group_name + " now:" + to_string(info.member_count) + " get:" + to_string(count));
                //     // 组员信息
                //     vector<GroupMember> members = get_group_member_list(info.group_id);
                //     group::writeGroupMembers(info, members);
                    
                // }else{
                //     zhl::info("====== 群组", to_string(g.group_id) + " " + g.group_name + " now:" + to_string(info.member_count) + " 不需要更新");
                // }


                int memCount = 0;
                memCount = getGroupMemberCount(info.group_id);
                zhl::info("群", format("群信息 %s id %llu 成员数量 %d 记录数量 %d", info.group_name.c_str(), info.group_id, info.member_count, memCount));
                                

                if(memCount < info.member_count){  // 大于真实数量就不管了，有点误差不理他
                    GroupExt gg = GroupExt();
                    gg.group_id = info.group_id;
                    gg.group_name = info.group_name;
                    gg.member_count = info.member_count;

                    // 组员信息
                    zhl::info("请求群员信息。");
                    vector<GroupMember> members;
                    if(info.group_id == 132847879){
                    }
                    zhl::info("time1:");
                    members = get_group_member_list(info.group_id);
                    zhl::info("time2:");
                    if(memCount == 0){
                        zhl::info("没有找到组信息, 插入一条记录。");
                        int r = insertGroupInfo(gg);
                        insertGroupMembers(info.group_id, members);
                    }else{
                        zhl::info("===更新群信息。");
                        int r = updateGroupInfo(gg);
                        // updateGroupMembers(info.group_id, members);
                    }
                    zhl::info("time3:");
                }

            }

        }catch(runtime_error e){

            zhl::info("群组", "逮到一个错误： " + to_string(e.what()));
        }
        zhl::info_success("E线程结束", "优惠播放-群员信息检测结束。");
        return 0;
    }

    // 处理优惠发送的线程
    unsigned int __stdcall advSendThread(void *pPM){
        if(sendGroupId == 0){
            logging::info_success("优惠发送", "群号为0。");
            return 0;
        }
        running = true;

        logging::info_success("S线程开始", "启动了优惠播放处理线程。");

        neb::CJsonObject groupJson = group::readGroupMembers(sendGroupId);
        neb::CJsonObject membersJson; groupJson.Get("members", membersJson);
        neb::CJsonObject memberJson;
        int index = 0;

        bool hasNext = true;

        while(running && hasNext){
            membersJson.Get(index, memberJson);

            string name;memberJson.Get("name", name);

            logging::info("zhch", "发送优惠。name:" + name);
            memberJson.Replace("sended", 1);
            membersJson.Replace(index, memberJson);
            groupJson.Replace("members", membersJson);

            group::writeGroupMembersJson(groupJson);

            xutils::sys::debug_sleep(3000, isDebug);

            index++;
            hasNext = index < membersJson.GetArraySize();
        }

        logging::info_success("E线程结束", "优惠播放循环结束，退出。");

        return 0;
    }
}