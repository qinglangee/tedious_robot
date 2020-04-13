#pragma once

#include "adv_dto.hpp"

using namespace std;
namespace xmalloc::adv{
    // group_dao.cpp
    int getGroupMemberCount(int64_t  groupId);
    int updateGroupInfo(const GroupExt &group);
    int insertGroupInfo(const GroupExt &group);

    // member_dao.cpp
    void startAdvThread(string cmd);
    void updateGroupMember(const GroupMemberExt &member);
    void insertGroupMember(const GroupMemberExt &member);
}