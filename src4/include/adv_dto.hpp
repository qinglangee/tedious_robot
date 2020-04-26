#pragma once

#include <string>

#include <cqcppsdk/cqcppsdk.h>

using namespace std;
using namespace cq;

namespace xmalloc::adv{

struct GroupExt : Group{
};

struct GroupMemberExt : GroupMember{

    int sended;
    GroupMemberExt();
    GroupMemberExt(GroupMember &src);

    static GroupMemberExt convert(GroupMember &src);

};


    // int64_t group_id = 0; // 群号
    //     // int64_t user_id; // 继承自 User 类
    //     // std::string nickname; // 继承自 User 类
    //     std::string card; // 名片(现在为群昵称)
    //     // Sex sex; // 继承自 User 类
    //     // int32_t age; // 继承自 User 类
    //     std::string area; // 地区
    //     int32_t join_time = 0; // 入群时间
    //     int32_t last_sent_time = 0; // 最近发言时间
    //     std::string level; // 等级
    //     GroupRole role = GroupRole::MEMBER; // 角色(权限)
    //     bool unfriendly = false; // 是否有不良记录
    //     std::string title; // 头衔
    //     int32_t title_expire_time = 0; // 头衔过期时间
    //     bool card_changeable = false; // 是否可修改名片


}