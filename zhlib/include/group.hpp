#pragma once
#include <cqcppsdk/cqcppsdk.h>

#include <vector>

using namespace cq;
using namespace std;

namespace xmalloc::group {
    /**========group_info.cpp======================================*/
    // 把组员信息写入文件
    void writeGroupMembers(Group group, vector<GroupMember> members);
    // 从文件读入组员信息
    neb::CJsonObject readGroupMembers(int64_t groupId);
}
