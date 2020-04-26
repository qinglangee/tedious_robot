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
    void updateGroupMember(const GroupMemberExt &member);
    void insertGroupMember(const GroupMemberExt &member);

    // 批量插入更新组员信息
    void insertGroupMembers(int64_t groupId, vector<GroupMember> &members);
    void updateGroupMembers(int64_t groupId, vector<GroupMember> &members);
}