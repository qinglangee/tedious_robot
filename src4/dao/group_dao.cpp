#include <string>

#include <cqcppsdk/cqcppsdk.h>

#include "sqlite3.h"
#include "adv_dto.hpp"

using namespace cq;

namespace xmalloc::adv{
    int getGroupMemberCount(int64_t  groupId){

        sqlite3* conn = NULL;
        // 打开数据库
        int result = sqlite3_open("./my.db", &conn);
        if(result != SQLITE_OK){
            sqlite3_close(conn);
            return 1;
        }
        string sqlStr = "SELECT * FROM group_info WHERE ID=" + to_string(groupId);
        const char* selectSql = sqlStr.c_str();
        
        sqlite3_stmt* stmt2 = NULL;
        if(sqlite3_prepare_v2(conn,selectSql,strlen(selectSql),&stmt2,NULL) != SQLITE_OK){
            if(stmt2){
                sqlite3_finalize(stmt2);
            }
            sqlite3_close(conn);
        }
        int fieldCount = sqlite3_column_count(stmt2);
        logging::info("sql", "The column count is " + to_string(fieldCount));

        int r = sqlite3_step(stmt2);
        int count = 0;
        if(r != SQLITE_DONE){
            count = sqlite3_column_int(stmt2, 2);
            logging::info("sql", "count is " + to_string(count));
            r = sqlite3_step(stmt2);
        }
        // do{
        // }
        // while(r != SQLITE_DONE)

        sqlite3_finalize(stmt2);
        sqlite3_close(conn);
        return count;
    }
    int updateGroupInfo(const GroupExt &group){
        return 0;
    }
    int insertGroupInfo(const GroupExt &group){
        sqlite3* conn = NULL;
        // 打开数据库
        int result = sqlite3_open("./my.db", &conn);
        if(result != SQLITE_OK){
            sqlite3_close(conn);
            return 1;
        }
        string sqlStr = "INSERT INTO group_info (id,name,member_count) VALUES("+to_string(group.group_id) + ",'"+group.group_name+"'," +to_string(group.member_count)  +")";
        const char* sql = sqlStr.c_str();
        sqlite3_stmt* stmt2 = NULL;
        if(sqlite3_prepare_v2(conn,sql,strlen(sql),&stmt2,NULL) != SQLITE_OK){
            if(stmt2){
                sqlite3_finalize(stmt2);
            }
            sqlite3_close(conn);
        }

        int r = sqlite3_step(stmt2);

        sqlite3_finalize(stmt2);
        sqlite3_close(conn);
        return 0;
    }
}