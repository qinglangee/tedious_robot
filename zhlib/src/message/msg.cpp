#include <iostream>
#include <sstream>
#include <string>
#include <cqcppsdk/cqcppsdk.h>




using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;


namespace xmalloc{
    // 判断 userId 是否在 at 列表中
    bool messageAt(const Message &message, int64_t userId){
        list<MessageSegment> segments = message.segments();
        list<MessageSegment>::iterator i;
        for (i = segments.begin(); i != segments.end(); ++i) {
            // logging::info_success("zhch", "type: " + i->type );
            if(i->type == "at"){
                // logging::info_success("zhch", "type: " + i->type );
                std::map<std::string, std::string> data = i->data;
                
                if(data["qq"] == to_string(userId)){
                    return true;
                }
            }
        }
        return false;
    }
}