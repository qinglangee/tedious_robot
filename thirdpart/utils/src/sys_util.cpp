#include <windows.h>

namespace xutils::sys {
    void sleep(unsigned long milliseconds){
        Sleep(milliseconds);
    }
}
