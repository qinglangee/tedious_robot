#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <time.h>

#include <cqcppsdk/cqcppsdk.h>
#include <windows.h>



using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

namespace xmalloc{
    default_random_engine e; // 随机数引擎
    vector<string> atGreetings = {
        "欢迎欢迎，新人露几手来！！",
        "欢迎欢迎，爆照还是表演个才艺呀",
        "欢迎来到新世界~",
        "欢迎大佬，请开始你的表演。",
        "来来来，给小菜们证明一下你的强大。",
        "emmmm, 谈谈你的感想吧",
        "为什么会进这个群呢",
    };
    vector<string> justGreetings = {
        "欸，这小破群又有人进了？ ",
        "快来看看是谁进来了~~~",
        "这是今天第一个进群的， papapapapapa",
    };

    string getGreeting(int64_t user_id);

    void greet(const GroupMemberIncreaseEvent &event){
        
        e.seed(time(NULL)); //设置新的种子
        string msg = getGreeting(event.user_id);

        // for(int i=0;i<50;i++){
        //     msg = getGreeting(event.user_id);
        //     logging::info_success("zhch", "msg is:" + msg);
        // }


        uniform_int_distribution<unsigned> u(0, 3);
        Sleep((5+u(e)) * 1000);
        try {
            send_group_message(event.group_id, msg); // 发送群消息
            
        } catch (ApiError &err) { // 忽略发送失败
            logging::warning("群聊", "欢迎消息失败, 错误码: " + to_string(err.code));
        }

        // msg = "[CQ:sface,id=" + to_string(2)+ "]";
        // msg = atGreetings[111];
        // send_group_message(event.group_id, msg); // 发送群消息
    }

    // 随机选条欢迎语
    string getGreeting(int64_t user_id){
        int allSize = atGreetings.size() + justGreetings.size();
        uniform_int_distribution<unsigned> u(0, allSize - 1);
        int index = u(e);
        string msg = "";
        if(index < atGreetings.size()){
            msg = "[CQ:at,qq=" + to_string(user_id) + "] " + atGreetings[index];
        }else{
            msg = justGreetings[index - atGreetings.size()];
        }

        uniform_int_distribution<unsigned> face_num(1, 39);
        msg = msg + " [CQ:face,id=" + to_string(face_num(e))+ "] ";
        

        return msg;
    }
}