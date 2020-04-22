#pragma once

#include <string>

using namespace std;


namespace xutils::str {
    template<typename ... Args>
    string format(const string& format, Args ... args);
}
