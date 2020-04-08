#include <windows.h>

namespace xutils::sys {
    void sleep(unsigned long milliseconds){
        Sleep(milliseconds);
    }
    void debug_sleep(unsigned long milliseconds, bool isDebug){
        unsigned long all = milliseconds;
        if(isDebug){
            all = all / 1000;
        }
        Sleep(all);
    }
}
