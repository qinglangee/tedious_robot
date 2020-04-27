#pragma once

#include <string>
#include "sqlite3.h"

using namespace std;

namespace xutils::sqlite {
    // 打开数据库
    sqlite3* db_open(string dbPath);

    // 准备数据库语句
    sqlite3_stmt*  prepare(sqlite3* conn, string sqlStr);

    // 关闭清理资源 
    void close(sqlite3_stmt* stmt, sqlite3* conn);

    // sql 语句绑定值
    int zh_bind(sqlite3_stmt* stmt, int i, int64_t iValue);
    int zh_bind(sqlite3_stmt* stmt, int i, string iValue);
}
