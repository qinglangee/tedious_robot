#pragma once

#include <string>

using namespace std;

namespace xmalloc::log {
    enum class Level {
        TEST = 10,
        DEBUG = 20,
        INFO = 30,
        WARN = 40,
        ERR = 50,
        FATAL = 60,
    };
    class ZhLog{
        public:
        static string logFile;
        // test 10 debug 20 info 30 warn 40 error 50
        static Level level;

        static void fileLog(Level level, string type, string msg);

        static void test(string type, string msg);
        static void test(string msg);
        static void debug(string type, string msg);
        static void debug(string msg);
        static void info(string type, string msg);
        static void info(string msg);
        
        static void info_success(string type, string msg);
        static void info_success(string msg);

        static void warning(string type, string msg);
        static void warning(string msg);

    };
}
