
#include <string>

#include <cqcppsdk/cqcppsdk.h>

#include "zhlog.hpp"
#include "time_util.hpp"
#include "fileutils.hpp"

using namespace std;
using namespace cq;

namespace xmalloc::log {
    
    string ZhLog::logFile = "";

    // 底层调用  info
    void ZhLog::info(string type, string msg){
        if(logFile == ""){
            logging::warning("WARN", "logFile is empty!!!");
        }else{
            logging::info(type, msg);
            string content = xutils::datetime::nowStr() + " [[" + type + "]] " + msg + "\n";
            xutils::file::appendFile(content, logFile);
        }
    }

    void ZhLog::info(string msg){
        info("INFO", msg);
    }

    // 底层调用  info_success
    void ZhLog::info_success(string type, string msg){
        if(logFile == ""){
            logging::warning("WARN", "logFile is empty!!!");
        }else{
            logging::info_success(type, msg);
            string content = xutils::datetime::nowStr() + " [[" + type + "]] " + msg + "\n";
            xutils::file::appendFile(content, logFile);
        }
    }

    void ZhLog::info_success(string msg){
        info_success("INFO_SUC", msg);
    }
}
