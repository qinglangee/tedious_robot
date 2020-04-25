#include <string>

// #include <cqcppsdk/cqcppsdk.h>

#include "zhsqlite3.hpp"
#include "base_dao.hpp"
#include "adv_dto.hpp"
#include "string_util.hpp"

#include "zhlog.hpp"

using namespace std;
using namespace xutils::str;
using zhl = xmalloc::log::ZhLog;

// using namespace cq;


namespace xmalloc::adv{
    


    // 获取群人数
    int getGroupMemberCount(int64_t  groupId){
        string dbPath = get_app_directory() + Config::dbFile;

        // zhl::info("db", dbPath);


        // 打开数据库
        sqlite3* conn = xutils::sqlite::db_open(dbPath);

        string sqlStr = "SELECT id,name,member_count FROM group_info WHERE ID=" + to_string(groupId);
        
        sqlite3_stmt* stmt2 = xutils::sqlite::prepare(conn, sqlStr);
        int count = 0;
        if(sqlite3_step(stmt2) != SQLITE_DONE){
            count = sqlite3_column_int(stmt2, 2);
        }

        xutils::sqlite::close(stmt2, conn);

        
        return count;
    }

    // 新增群信息
    int insertGroupInfo(const GroupExt &group){
        string sqlStr = "INSERT INTO group_info (id,name,member_count) VALUES("+to_string(group.group_id) + ",'"+group.group_name+"'," +to_string(group.member_count) + ")";
        return executeSql(sqlStr);
        return 0;
    }

    // 更新群信息
    int updateGroupInfo(const GroupExt &group){
        string sqlStr = format("UPDATE group_info SET name='%s',member_count=%d WHERE id=%d", group.group_name.c_str(), group.member_count, group.group_id);
        return executeSql(sqlStr);
        return 0;
    }

}