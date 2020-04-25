#pragma once

// #include "adv_dto.hpp"
// #include "zhlog.hpp"

// using namespace std;
// using zhl = xmalloc::log::ZhLog;

namespace xmalloc::adv{
    struct Config{
        static string dbFile;
    };

    // file  =========== base_dao.cpp ============
    // 执行一个 sql 语句
    int executeSql(string sqlStr);
}