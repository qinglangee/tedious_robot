#pragma once

#include <string>

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
        // unique_ptr<char[]> buf(new char[size]);
        char *bytes = new char[size];
        snprintf(bytes, size, format.c_str(), args ...);
        return string(bytes);
    }
}
