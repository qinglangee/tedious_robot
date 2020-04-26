
#include "adv_dto.hpp"

using namespace std;
using namespace cq;

namespace xmalloc::adv{

    GroupMemberExt::GroupMemberExt(){
        sended = 0;
    }
    GroupMemberExt::GroupMemberExt(GroupMember &src):GroupMemberExt(){
        
        group_id = src.group_id;
        user_id = src.user_id;
        nickname = src.nickname;
        card = src.card;
        sex = src.sex;
        age = src.age;
        area = src.area;
        join_time = src.join_time;
        level = src.level;
        role = src.role;

    }
    GroupMemberExt GroupMemberExt::convert(GroupMember &src){
        GroupMemberExt dest = GroupMemberExt(src);
        return dest;
    }


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