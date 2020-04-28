
#include "adv_dao.hpp"
#include "zhlog.hpp"



using namespace xmalloc;
using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

using zhl = xmalloc::log::ZhLog;

namespace xmalloc::adv{
    
    // 群员增加
    void groupMemberIncrease(const GroupMemberIncreaseEvent &event){
        GroupMember member = get_group_member_info(event.group_id, event.user_id);
        GroupMemberExt memberExt = GroupMemberExt(member);
        insertGroupMember(memberExt);
    }
    // 群员减少
    void groupMemberDecrease(const GroupMemberDecreaseEvent &event){
        GroupMemberExt member = GroupMemberExt();
        member.user_id = event.user_id;
        member.group_id = event.group_id;
        deleteGroupMember(member);
    }
}