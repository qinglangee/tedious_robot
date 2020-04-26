#include <string>
#include <stdexcept>

#include "zhsqlite3.hpp"
#include "base_dao.hpp"
#include "adv_dto.hpp"
#include "string_util.hpp"

#include "zhlog.hpp"

using namespace xutils::str;
using zhl = xmalloc::log::ZhLog;

namespace xmalloc::adv{

    
    // 插入单个群员信息
    int insertGroupMember(GroupMemberExt &m){
        zhl::debug("开始插入单个组员 ");
        string tableName = "m" + to_string(m.group_id);
        string sqlTemplate = "INSERT INTO " + tableName + " (id, nickname, card, sex, age, join_time, role, sended) VALUES (%llu, '%s', '%s', %d, %lu,%lu,%d, %d)";
        string nickname = replace_all(m.nickname, "'", "");
        string card = replace_all(m.card, "'", "");
        string sql = format(sqlTemplate, m.user_id, nickname.c_str(), card.c_str(), m.sex, m.age, m.join_time, m.role, m.sended);
        zhl::debug("插入单个组员 " + sql);
        return executeSql(sql);
    }

    // 批量插入群员信息
    void insertGroupMembers(int64_t groupId, vector<GroupMember> &members){
        // 先创建表
        string tableName = "m" + to_string(groupId);
        string sql = "CREATE TABLE " + tableName + "(id INT PRIMARY KEY NOT NULL, nickname TEXT, card TEXT, sex INT, age int,join_time int, role int,"
            + "sended INT NOT NULL)";
        zhl::debug("创建新的群员信息表 " + sql);
        executeSql(sql);

        // 再循环插入数据
        for(int i=0;i<members.size();i++){
            // zhl::info("循环 " + to_string(i));
            GroupMemberExt member = GroupMemberExt(members[i]);
            insertGroupMember(member);
        }

    }

    
    // int64_t group_id = 0; // 群号
    //     // int64_t user_id; // 继承自 User 类
    //     // std::string nickname; // 继承自 User 类
    //     std::string card; // 名片(现在为群昵称)
    //     // Sex sex; // 继承自 User 类
    //     // int32_t age; // 继承自 User 类
    //     std::string area; // 地区
    //     int32_t join_time = 0; // 入群时间
    //     std::string level; // 等级
    //     GroupRole role = GroupRole::MEMBER; // 角色(权限)

    void updateGroupMembers(int64_t groupId, vector<GroupMember> &members){
        // zhl::info("来来来， 这方法还没完成，03===========");

    }
    
}