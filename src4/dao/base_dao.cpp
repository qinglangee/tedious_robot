#include <string>


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
    int executeSql(string sqlStr){
        sqlite3* conn = xutils::sqlite::db_open(get_app_directory() + Config::dbFile);
        
        
        sqlite3_stmt* stmt2 = xutils::sqlite::prepare(conn, sqlStr);

        int r = sqlite3_step(stmt2);

        xutils::sqlite::close(stmt2, conn);
        return 0;
    }
}