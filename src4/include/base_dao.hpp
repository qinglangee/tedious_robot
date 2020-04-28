#pragma once

#include "zhsqlite3.hpp"
// #include "adv_dto.hpp"
// #include "zhlog.hpp"

// using namespace std;
// using zhl = xmalloc::log::ZhLog;

namespace xmalloc::adv{
    struct Config{
        static string dbFile;
    };
    // 打开数据库
    sqlite3* openConnection();

    // file  =========== base_dao.cpp ============
    // 执行一个 sql 语句
    int executeReturnDone(string sqlStr);
    // 执行一个 sql 语句
    int executeReturnDone(sqlite3* conn, string sqlStr);
}