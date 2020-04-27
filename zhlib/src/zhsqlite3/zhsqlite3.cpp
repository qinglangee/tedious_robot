
#include <string>
#include <stdexcept>

#include "sqlite3.h"
#include "zhlog.hpp"

using namespace std;
namespace xutils::sqlite {
    // 打开数据库
    sqlite3* db_open(string dbPath){

        sqlite3* conn = NULL;
        // 打开数据库
        int result = sqlite3_open(dbPath.c_str(), &conn);
        if(result != SQLITE_OK){
            sqlite3_close(conn);
            throw runtime_error("打开数据库的时候不 OK 啊。(" + to_string(result) + ")");
        }
        return conn;
    }
    // 准备数据库语句
    sqlite3_stmt* prepare(sqlite3* conn, string sqlStr){
        const char* selectSql = sqlStr.c_str();
        
        sqlite3_stmt* stmt2 = NULL;
        int r = sqlite3_prepare_v2(conn,selectSql,strlen(selectSql),&stmt2,NULL);
        if(r != SQLITE_OK){
            if(stmt2){
                sqlite3_finalize(stmt2);
            }
            sqlite3_close(conn);
            throw runtime_error("准备 sql statement 的时候不 OK 啊。(" + to_string(r) + ")  " + sqlStr);
        }
        return stmt2;
    }

    // 关闭清理资源 
    void close(sqlite3_stmt* stmt, sqlite3* conn){
        sqlite3_finalize(stmt);
        sqlite3_close(conn);
    }


    // sql 语句绑定值
    int zh_bind(sqlite3_stmt* stmt, int i, int64_t iValue){
        return sqlite3_bind_int64(stmt, i, iValue);
    }
    int zh_bind(sqlite3_stmt* stmt, int i, string iValue){
        const char* strData = iValue.c_str();
        return sqlite3_bind_text(stmt, i, strData, strlen(strData), SQLITE_TRANSIENT);
    }

}
