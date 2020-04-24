
#include <string>
#include <cqcppsdk/cqcppsdk.h>
#include <vector>

#include "CJsonObject.hpp"
#include "fileutils.hpp"

#include "group.hpp"

using namespace cq;
using namespace std;

/** 因为用了数据库，这个类就不需要了。  */
namespace xmalloc::group {
    neb::CJsonObject convertMembersToJson(vector<GroupMember> members);

    // 把组员信息写入文件
    void writeGroupMembers(Group group, vector<GroupMember> members){
        
        // 写入群组信息
        neb::CJsonObject oJson("{}");
        oJson.Add("group_id", group.group_id);
        oJson.Add("group_name", group.group_name);
        oJson.Add("member_count", group.member_count);
        neb::CJsonObject membersJson = convertMembersToJson(members);
        oJson.Add("members", membersJson);

        writeGroupMembersJson(oJson);
    }
    // json写入文件
    void writeGroupMembersJson(neb::CJsonObject json){
        int64_t groupId;
        json.Get("group_id", groupId);
        
        string filepath = get_app_directory() + "group/mems_" + to_string(groupId);
        string prettyFilepath = get_app_directory() + "group/pretty_" + to_string(groupId);

        
        xutils::file::writeFile(json.ToString(), filepath);
        xutils::file::writeFile(json.ToFormattedString(), prettyFilepath);

    }
    // 从文件读入组员信息
    neb::CJsonObject readGroupMembers(int64_t groupId){
        string filepath = get_app_directory() + "group/mems_" + to_string(groupId);
        neb::CJsonObject empty("{}");
        if(xutils::file::fileExist(filepath)){
            vector<string> lines = xutils::file::readFile(filepath);
            neb::CJsonObject json(lines[0]);
            return json;

        }else{

            return empty;
        }

    }

    neb::CJsonObject convertMembersToJson(vector<GroupMember> members){
        neb::CJsonObject json("[]");
        for(int i=0; i<members.size();i++){
            GroupMember member = members[i];
            neb::CJsonObject sub("{}");
            sub.Add("name", member.nickname);


            
            sub.Add("sended", 0); // 优惠发送标记信息
            json.Add(sub);

        }

        return json;
    }
}
