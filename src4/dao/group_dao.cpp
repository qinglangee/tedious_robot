#include <string>

// #include <cqcppsdk/cqcppsdk.h>

#include "zhsqlite3.hpp"
#include "adv_dto.hpp"

#include "zhlog.hpp"

using namespace std;

// using namespace cq;
using zhl = xmalloc::log::ZhLog;

namespace xmalloc::adv{
    string dbFile = "adv.db";

    // 获取群人数
    int getGroupMemberCount(int64_t  groupId){
        string dbPath = get_app_directory() + dbFile;


        // 打开数据库
        sqlite3* conn = xutils::sqlite::db_open(dbPath);

        string sqlStr = "SELECT * FROM group_info WHERE ID=" + to_string(groupId);
        
        sqlite3_stmt* stmt2 = xutils::sqlite::prepare(conn, sqlStr);
        int count = 0;
        if(sqlite3_step(stmt2) != SQLITE_DONE){
            count = sqlite3_column_int(stmt2, 2);
        }

        xutils::sqlite::close(stmt2, conn);

        
        return count;
    }

    // 更新群信息
    int updateGroupInfo(const GroupExt &group){
        return 0;
    }

    // 新增群信息
    int insertGroupInfo(const GroupExt &group){
        sqlite3* conn = xutils::sqlite::db_open(get_app_directory() + dbFile);
        string sqlStr = "INSERT INTO group_info (id,name,member_count) VALUES("+to_string(group.group_id) + ",'"+group.group_name+"'," +to_string(group.member_count)  +")";
        
        sqlite3_stmt* stmt2 = xutils::sqlite::prepare(conn, sqlStr);

        int r = sqlite3_step(stmt2);

        xutils::sqlite::close(stmt2, conn);
        return 0;
    }
}