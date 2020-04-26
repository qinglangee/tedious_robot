
#include <string>

#include <cqcppsdk/cqcppsdk.h>

#include "zhlog.hpp"
#include "time_util.hpp"
#include "fileutils.hpp"

using namespace std;
using namespace cq;

namespace xmalloc::log {
    
    string ZhLog::logFile = "";
    Level ZhLog::level = Level::INFO;

    void ZhLog::fileLog(Level levelArg, string type, string msg){
        if(logFile == ""){
            logging::warning("WARN", "logFile is empty!!!");
        }else{
            if(levelArg < level){
                return;
            }else{
                string content = xutils::datetime::nowStr() + " [[" + type + "]] " + msg + "\n";
                xutils::file::appendFile(content, logFile);
            }
        }
    }

    // 底层调用  debug
    void ZhLog::test(string type, string msg){
        logging::debug(type, msg);
        fileLog(Level::TEST, type, msg);
    }

    void ZhLog::test(string msg){
        test("TEST", msg);
    }

    // 底层调用  debug
    void ZhLog::debug(string type, string msg){
        logging::debug(type, msg);
        fileLog(Level::DEBUG, type, msg);
    }

    void ZhLog::debug(string msg){
        debug("DEBUG", msg);
    }

    // 底层调用  info
    void ZhLog::info(string type, string msg){
        logging::info(type, msg);
        fileLog(Level::INFO, type, msg);
    }

    void ZhLog::info(string msg){
        info("INFO", msg);
    }

    // 底层调用  info_success
    void ZhLog::info_success(string type, string msg){
        logging::info_success(type, msg);
        fileLog(Level::INFO, type, msg);
    }

    void ZhLog::info_success(string msg){
        info_success("INFO_SUC", msg);
    }
}
