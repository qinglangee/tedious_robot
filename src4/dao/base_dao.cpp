#include <string>
#include <stdexcept>

#include "zhsqlite3.hpp"
#include "base_dao.hpp"
#include "adv_dto.hpp"
#include "string_util.hpp"

#include "zhlog.hpp"

using namespace std;
using namespace xutils::str;

using zhl = xmalloc::log::ZhLog;

namespace xmalloc::adv{
    string Config::dbFile = "";
    
    // 执行一个 sql 语句
    int executeReturnDone(string sqlStr){
        sqlite3* conn = xutils::sqlite::db_open(get_app_directory() + Config::dbFile);
        
        
        sqlite3_stmt* stmt = xutils::sqlite::prepare(conn, sqlStr);

        int r = sqlite3_step(stmt);
        xutils::sqlite::close(stmt, conn);
        
        if (r != SQLITE_DONE) {
            throw runtime_error("执行语句的时候不 OK 啊。(" + to_string(r) + ") " + sqlStr);
        }

        return r;
    }
    
    // 执行一个 sql 语句
    int executeReturnDone(sqlite3* conn, string sqlStr){
        
        
        sqlite3_stmt* stmt = xutils::sqlite::prepare(conn, sqlStr);

        int r = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (r != SQLITE_DONE) {
            throw runtime_error("执行语句的时候不 OK 啊。(" + to_string(r) + ") " + sqlStr);
        }
        return r;
    }
}