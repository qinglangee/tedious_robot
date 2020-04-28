#pragma once

#include "adv_dto.hpp"

using namespace std;

namespace xmalloc::adv{

    // file  =========== group_dao.cpp ============
    int getGroupMemberCount(int64_t  groupId);
    int insertGroupInfo(const GroupExt &group);
    int updateGroupInfo(const GroupExt &group);


    
    // file  =========== member_dao.cpp ============
    void startAdvThread(string cmd);
    void insertGroupMember(GroupMemberExt &member); // 插入一条组员
    void updateGroupMember(GroupMemberExt &member); // 更新一条组员
    void deleteGroupMember(GroupMemberExt &member); // 删除一条组员

    // 批量插入更新组员信息
    void createTableAndInsertGroupMembers(int64_t groupId, vector<GroupMember> &members);
    void updateGroupMembers(int64_t groupId, vector<GroupMember> &members);

    // 取没发送过的群员信息
    GroupMemberExt getUnsendGroupMember(int64_t groupId);
}