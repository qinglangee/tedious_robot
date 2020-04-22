#pragma once

#include <string>

using namespace std;

namespace xmalloc::log {
    class ZhLog{
        public:
        static string logFile;

        static void info(string type, string msg);
        static void info(string msg);
        
        static void info_success(string type, string msg);
        static void info_success(string msg);


    };
}
