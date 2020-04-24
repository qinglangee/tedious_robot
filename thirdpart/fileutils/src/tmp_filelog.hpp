#pragma once

#include <string>

using namespace std;

namespace xmalloc::tmplog {
    class TmpLog{
        public:
        static string logFile;

        static void info(string msg);


    };
}
