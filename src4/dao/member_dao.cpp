#include <string>
#include <stdexcept>

#include "zhsqlite3.hpp"
#include "base_dao.hpp"
#include "adv_dto.hpp"
#include "string_util.hpp"

#include "zhlog.hpp"

using namespace xutils::str;
using zhl = xmalloc::log::ZhLog;
using namespace xutils::sqlite;

namespace xmalloc::adv{

    
    // 插入单个群员信息
    int insertGroupMember(sqlite3_stmt* stmt, GroupMemberExt &m){
        zhl::debug("开始插入单个组员 ");

        
        zh_bind(stmt,1, m.user_id);
        zh_bind(stmt,2, m.nickname);
        zh_bind(stmt,3, m.card);
        zh_bind(stmt,4, static_cast<int>(m.sex));
        zh_bind(stmt,5, m.age);
        zh_bind(stmt,6, m.join_time);
        zh_bind(stmt,7, static_cast<int>(m.role));
        zh_bind(stmt,8, m.sended);
        int r = sqlite3_step(stmt);
        sqlite3_reset(stmt);
        return r;
    }

    // 批量插入群员信息
    void insertGroupMembers(int64_t groupId, vector<GroupMember> &members){
        string tableName = "m" + to_string(groupId);

        sqlite3* conn = xutils::sqlite::db_open(get_app_directory() + Config::dbFile);
        executeReturnDone(conn, "BEGIN TRANSACTION");
        string sqlTemplate = "INSERT INTO " + tableName + " (id, nickname, card, sex, age, join_time, role, sended) VALUES (?,?,?,?,?,?,?,?)";
        sqlite3_stmt* stmt = xutils::sqlite::prepare(conn, sqlTemplate);
        // 再循环插入数据
        for(int i=0;i<members.size();i++){
            // zhl::info("循环 " + to_string(i));
            GroupMemberExt member = GroupMemberExt(members[i]);
            int r = insertGroupMember(stmt, member);

        }
        executeReturnDone(conn, "COMMIT");
        
        xutils::sqlite::close(stmt, conn);
    }

    // 创建表并插入数据
    void createTableAndInsertGroupMembers(int64_t groupId, vector<GroupMember> &members){
        // 先创建表
        string tableName = "m" + to_string(groupId);
        string sql = "CREATE TABLE " + tableName + "(id INT PRIMARY KEY NOT NULL, nickname TEXT, card TEXT, sex INT, age int,join_time int, role int,"
            + "sended INT NOT NULL)";
        zhl::debug("创建新的群员信息表 " + sql);
        executeReturnDone(sql);

        insertGroupMembers(groupId, members);
    }

    void updateGroupMembers(int64_t groupId, vector<GroupMember> &members){
        // 直接强插，已有的插不进去就是了
        insertGroupMembers(groupId, members);

    }
    
}