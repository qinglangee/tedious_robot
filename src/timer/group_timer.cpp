#include <iostream>
#include <sstream>
#include <string>
#include <process.h>
#include <time.h>
#include <random>
#include <map>
#include <vector>
#include <direct.h>

//cqcppsdk.h 要放在windows.h 之前， 要不就会出莫名其妙的BUG,编译不通过
#include <cqcppsdk/cqcppsdk.h>
#include <windows.h>

#include "command.hpp"
#include "CJsonObject.hpp"
#include "fileutils.hpp"


using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

namespace xmalloc {
    bool running = false; // 定时器是否执行
    default_random_engine e; // 随机数引擎
    string recordFilepath;
    string prettyFilepath;


    bool isDebug = false; // 内部调试开关

    unsigned int __stdcall tiaoxiThread(void *pPM);
    void tiaoxiFun();
    void processCmd(int hour, string cmdContent);
    void innerSleep(DWORD dwMilliseconds);
    time_t nextTime();
    void writeTimeToFile(time_t sleepTime);


    void startTiaoxiThread(){
        if(running){
            return;
        }

        e.seed(time(NULL)); //设置新的种子

        string appDir = get_app_directory();
        recordFilepath = appDir + "record.json";
        prettyFilepath = appDir + "pretty.json";

        _beginthreadex(NULL, 0, tiaoxiThread, NULL, 0, NULL);
        
        // logging::info_success("启动", "启动定时线程");
    }

    // 调戏机器人
    unsigned int __stdcall tiaoxiThread(void *pPM){
        
        running = true;

        
        // 先判断下有没有达到预定的下次执行时间
        time_t leftTime = nextTime();
        if(leftTime > 0){
            logging::info_success("zhch", "未达预定，稍等: " + to_string(leftTime) + " 分钟：" + to_string(leftTime/60));
            innerSleep(leftTime * 1000);
        }

        
        
        uniform_int_distribution<unsigned> u(0, 9*60*1000);

        while(running){
            
            tiaoxiFun();
            DWORD sleepTime = 48 * 60 * 1000 + u(e);
            logging::info_success("zhch", "休眠时间: " + to_string(sleepTime) + " 分钟：" + to_string(sleepTime/60000));
            
            writeTimeToFile(sleepTime); // 记录时间

            innerSleep(sleepTime);
            innerSleep(5000);
        }
        logging::info_success("zhch", "循环结束，退出。");

        return 0;
    }

    int temp = 0;
    // 主功能流程
    void tiaoxiFun(){


        time_t tt = time(NULL);//这句返回的只是一个时间cuo
        tm* t= localtime(&tt);

        int hour = 0;
        if(!isDebug){
            hour = t->tm_hour;
        }else{
            hour = (temp++) % 24;
        }

        ostringstream oss;
        oss<<t->tm_year + 1900<<"-"<<t->tm_mon + 1<<"-"<<t->tm_mday<<" "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec;
        logging::info_success("zhch", "定时器: " + oss.str() + " 应用hour:" + to_string(hour));
        // send_group_message(132847879, "count:" + to_string(3));



        map<int, vector<string>> timeMap;
        timeMap[6] = {"锻炼"};
        timeMap[7] = {"锻炼"};
        map<int, vector<string>> cmdMap;
        cmdMap[7] = {"一起吃早饭"};
        cmdMap[9] = {"打工8"};
        cmdMap[10] = {"打工8"};
        cmdMap[12] = {"抽签", "一起吃午饭"};
        cmdMap[18] = {"一起吃晚饭"};
        cmdMap[22] = {"晚安"};
        map<int, vector<string>> randMap;
        randMap[7] = {"早安", "早上好"};
        randMap[18] = {"锻炼3", "打工2"};
        randMap[19] = {"锻炼2", "打工1"};

        bool haveAct = false;
        string cmd = "";
        int i;
        map<int, vector<string>>::iterator acts = timeMap.find(hour);
        // 需要设置时间的命令
        if(acts != timeMap.end()){
            haveAct = true;
            for(int i=0;i<acts->second.size();i++){
                cmd = acts->second[i] + to_string(9-hour);
                processCmd(hour, cmd);
            }
        }

        // 全部执行的命令
        acts = cmdMap.find(hour);
        if(acts != cmdMap.end()){
            haveAct = true;
            for(int i = 0; i<acts->second.size(); i++){
                cmd = acts->second[i];
                processCmd(hour, cmd);
            }
        }

        // 挑一个执行的命令
        acts = randMap.find(hour);
        if(acts != randMap.end()){
            haveAct = true;
            vector<string> cmds = acts->second;
            uniform_int_distribution<unsigned> u(0, cmds.size() - 1);
            processCmd(hour, cmds[u(e)]);
        }

        if(!haveAct && hour > 5 && hour < 23){
            string others[] ={"摸头", "摸摸头", "打钱1", "打钱2", "打钱3", "抱抱", "举高高", "亲亲", "摸腿", "拉小手"};
            uniform_int_distribution<unsigned> u(0, sizeof(others)/sizeof(others[0]) - 1);
            cmd = others[u(e)];
            processCmd(hour, cmd);

        }


    }

    // 命令处理
    void processCmd(int hour, string cmdContent){
        string cmdHead = "!1 @1 ";
        string cmd = cmdHead + cmdContent;
        logging::info_success("zhch", "hour:" + to_string(hour) + "  发送: " + cmd);
        if(!isDebug){
            processChuxinMessage(cmd);
        }
        uniform_int_distribution<unsigned> u(0, 10);
        innerSleep((10+u(e)) * 1000);
        innerSleep(800);
    }

    // 记录本次调戏和下次调戏执行的时间
    void writeTimeToFile(time_t sleepTime){
        time_t now = time(NULL);//这句返回的只是一个时间cuo，精确到秒
        tm* t= localtime(&now);
        ostringstream oss;
        oss<<t->tm_year + 1900<<"-"<<t->tm_mon + 1<<"-"<<t->tm_mday<<" "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec;
        
        
        time_t next = now + sleepTime/1000;

        neb::CJsonObject oJson("{}");
        oJson.Add("next", next);
        oJson.Add("nextStr", oss.str());
        xutils::file::writeFile(oJson.ToString(), recordFilepath);
        xutils::file::writeFile(oJson.ToFormattedString(), prettyFilepath);


    }

    // 判断距离预定下次执行时间的间隔，以秒为单位
    time_t nextTime(){
        if(!xutils::file::fileExist(recordFilepath)){
            logging::info_success("zhch", "没有记录文件。继续。。。");
            return 0;
        }
        vector<string> lines = xutils::file::readFile(recordFilepath);
        neb::CJsonObject oJson(lines[0]);
        time_t next;
        oJson.Get("next", next);
        time_t now = time(NULL);//这句返回的只是一个时间cuo，精确到秒
        time_t delta =  next - now;

        // logging::info_success("zhch", "离预定时间还有秒数: " + to_string(delta) + " 分钟：" + to_string(delta/60));

        return delta;
    }
    // running 控制 sleep 还要不要继续
    void innerSleep(DWORD dwMilliseconds){
        DWORD all = dwMilliseconds/1000;

        // 调试时间开关
        if(isDebug){
            all = all / 1000;

        }


        while(all > 0 && running){
            Sleep(1000);
            all--;
        }
    }

    void stopTiaoxi(){
        running = false;
    }
}