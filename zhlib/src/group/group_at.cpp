#include <sstream>
#include <string>
#include <cqcppsdk/cqcppsdk.h>

#include "sys_util.hpp"


using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

using namespace xutils::sys;


namespace xmalloc{
    void responseAtMessage(const GroupMessageEvent &event){
        sleep(1000);
        Message m = Message(event.message);
        string msg = "[CQ:at,qq=" + to_string(event.user_id) + "] " + m.extract_plain_text();


        logging::info_success("zhch", "回复: " + msg );
        // send_group_message(event.group_id, msg); // 发送群消息
    }
}