#include <iostream>
#include <sstream>
#include <string>
#include <process.h>
#include <time.h>
#include <random>

//cqcppsdk.h 要放在windows.h 之前， 要不就会出莫名其妙的BUG,编译不通过
#include <cqcppsdk/cqcppsdk.h>
#include <windows.h>

#include "command.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

namespace xmalloc {
    bool running = false; // 定时器是否执行

    unsigned int __stdcall tiaoxiThread(void *pPM);
    void tiaoxiFun();


    void startTiaoxiThread(){
        if(running){
            return;
        }

        _beginthreadex(NULL, 0, tiaoxiThread, NULL, 0, NULL);
        
        // logging::info_success("启动", "启动定时线程");
    }

    // 调戏机器人
    unsigned int __stdcall tiaoxiThread(void *pPM){
        
        running = true;

        default_random_engine e;
        uniform_int_distribution<unsigned> u(0, 10*60*1000);

        while(running){
            
            tiaoxiFun();
            DWORD sleepTime = 30 * 60 * 1000 + u(e);
            logging::info_success("zhch", "休眠时间: " + to_string(sleepTime) + " 分钟：" + to_string(sleepTime/60000));
            Sleep(sleepTime);
        }

        return 0;
    }

    int temp = 0;
    void tiaoxiFun(){
        time_t tt = time(NULL);//这句返回的只是一个时间cuo
        tm* t= localtime(&tt);
        string aa = to_string(t->tm_year);
        ostringstream oss;
        oss<<t->tm_year + 1900<<"-"<<t->tm_mon + 1<<"-"<<t->tm_mday<<" "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec;
        logging::info_success("zhch", "定时器: " + oss.str());
        // send_group_message(132847879, "count:" + to_string(3));

        int hour = t->tm_hour;
        // int hour = (temp++) % 24;


        string cmd = "";
        string groupId = "1";
        if(hour > 5 && hour < 9){
            cmd = "!"+ groupId + " @1 3" + to_string(9-hour);
        }else if(hour >8 && hour < 12){
            cmd = "!"+ groupId + " @1 48";
        }else if(hour > 17 && hour < 20){
            cmd = "!"+ groupId + " @1 ";
            if(t->tm_min % 2 == 1){
                cmd = cmd + "33";
            }else{
                cmd = cmd + "43";
            }
        }
        logging::info_success("zhch", "hour:" + to_string(hour) + "  发送: " + cmd);
        processChuxinMessage(cmd);
    }

    void stopTiaoxi(){
        running = false;
    }
}