
#include <string>

#include "tmp_filelog.hpp"
#include "fileutils.hpp"

using namespace std;

namespace xmalloc::tmplog {
    
    string TmpLog::logFile = "d:/temp/d3/ttlog.txt";
    

    // 底层调用  info
    void TmpLog::info(string msg){
        string content = msg + "\n";
        xutils::file::appendFile(content, logFile);
    }
}
