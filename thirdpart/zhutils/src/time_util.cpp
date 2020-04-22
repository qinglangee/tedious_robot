
#include <string>
#include <time.h>
#include <sstream>

#include "string_util.hpp"

using namespace std;
namespace xutils::datetime {
    string nowStr(){
        time_t tt = time(NULL);//这句返回的只是一个时间cuo

        struct tm t;
	    localtime_s(&t, &tt);

        // 线程不安全版本
        // tm* t= localtime(&_Time);

        // ostringstream oss;
        // oss<<t.tm_year + 1900<<"-"<<t.tm_mon + 1<<"-"<<t.tm_mday<<" "<<t.tm_hour<<":"<<t.tm_min<<":"<<t.tm_sec;
        
        // return oss.str();

        string result = xutils::str::format("%d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900,t.tm_mon + 1,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);
        return result;

        // return "";
    }
}