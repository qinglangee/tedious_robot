#pragma once

#include "adv_dto.hpp"

using namespace std;
namespace xmalloc::adv{
    // file  =========== group_dao.cpp ============
    int getGroupMemberCount(int64_t  groupId);
    int insertGroupInfo(const GroupExt &group);
    int updateGroupInfo(const GroupExt &group);

    void insertGroupMembers();
    void updateGroupMembers();

    
    // file  =========== member_dao.cpp ============
    void startAdvThread(string cmd);
    void updateGroupMember(const GroupMemberExt &member);
    void insertGroupMember(const GroupMemberExt &member);
}