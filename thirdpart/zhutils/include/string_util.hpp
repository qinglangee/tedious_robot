#pragma once

#include <string>
#include <iostream>

// #include "tmp_filelog.hpp"


using namespace std;


namespace xutils::str {
    /**
     * copy from  https://zhuanlan.zhihu.com/p/90732830
     * 功能：格式化字符串
     * 返回值：格式化的结果字符串
     */
    template<typename ... Args>
    string format(const string& format, Args ... args){
        const size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
        // xmalloc::tmplog::TmpLog::info("== " + format + " size:" + to_string(size));

        // unique_ptr<char[]> buf(new char[size]);
        char *bytes = new char[size];
        snprintf(bytes, size, format.c_str(), args ...);
        string result = string(bytes);
        // xmalloc::tmplog::TmpLog::info("-- " + result);
        return result;
    }

    // 字符串替换  replace_all("12212", "12", "21")  原字串变为 21221 ， 返回 char*
    string replace_all(string& str,const string& old_value,const string& new_value);

    // 字符串替换  replace_all2("12212", "12", "21")  原字串变为 22211 ， 返回 char*
    string replace_all2(string& str,const string& old_value,const string& new_value);
}
