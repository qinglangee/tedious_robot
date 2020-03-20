#include <iostream>
#include <sstream>
#include <string>
#include <cqcppsdk/cqcppsdk.h>

#include "command.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;


namespace xmalloc {
    
    void forwardGroupMessage(const PrivateMessageEvent &event);
    void forwardChuxinMessage(const PrivateMessageEvent &event);

    void processMessage(const PrivateMessageEvent &event) {
        if(event.user_id != 61804888){
            logging::info_success("zhch", "�������� id: " + to_string(event.user_id) );
            return;
        }

        if(event.message.find_first_of("r ") == 0){

            auto msgid = send_private_message(event.user_id, event.message); // ֱ�Ӹ�����Ϣ
            logging::info_success("˽��", "˽����Ϣ�������, ��Ϣ Id: " + to_string(msgid));
            auto msgid2 = send_message(event.target,
                        MessageSegment::face(111) + "����ͨ�� message ģ�鹹�����Ϣ~"); // ʹ�� message ģ�鹹����Ϣ
            logging::info_success("˽��", "˽����Ϣ�������, ��Ϣ Id: " + to_string(msgid2));
        }else if(event.message.find_first_of("!") == 0){
            forwardGroupMessage(event);
        }else if(event.message.find_first_of("cmd ") == 0){
            auto groups = get_group_list();
            for(size_t i = 0; i < groups.size(); i++){
                cq::Group g = groups[i];
                logging::info_success("zhch", "Ⱥ����: " + to_string(g.group_name));

                auto members = get_group_member_list(g.group_id);
                for(size_t j = 0; j < members.size(); j++){
                    cq::GroupMember m = members[j];
                    logging::info_success("zhch", "ȺԱ����: " + to_string(m.nickname) + " qq�ţ�" + to_string(m.user_id));
                }
            }
        }

        
        send_message(event.target, MessageSegment::face(111) + "���." + event.message);
    }

    // ת����Ⱥ����Ϣ
    void forwardGroupMessage(const PrivateMessageEvent &event){
        size_t spaceIndex = event.message.find(" ");
        if(spaceIndex == string::npos){
            send_message(event.target, MessageSegment::face(110) + "����:" + event.message);
            return;
        }

        int64_t invincible = 132847879;  // invincible no ѧ����

        string groupIdStr = event.message.substr(1, spaceIndex - 1);
        int64_t groupId;
        if(groupIdStr == "0"){
            groupId = invincible;
        }else if(groupIdStr == "1"){
            groupId = 479646367;  // ����ڹ�� Ԥ����
            forwardChuxinMessage(event);
            return;
        }else{
            groupId = stoll(groupIdStr, 0, 10);
        }

        string msg = event.message.substr(spaceIndex + 1);

        // ��Ҫ at ĳ��
        if(msg.find("@") == 0){
            spaceIndex = msg.find(" ");
            if(spaceIndex != string::npos){
                string atIdStr = msg.substr(1, spaceIndex - 1);
                string newMsg = msg.substr(spaceIndex + 1);
                msg = "[CQ:at,qq=" + atIdStr + "] " + newMsg;

            }
        }

        // send_message(event.target, MessageSegment::face(110) + "head:" + groupIdStr + to_string(spaceIndex) + msg);
        try {
            send_group_message(groupId, msg); // ����Ⱥ��Ϣ
            
        } catch (ApiError &err) { // ���Է���ʧ��
            logging::warning("Ⱥ��", "Ⱥ����Ϣ����ʧ��, ������: " + to_string(err.code));
        }
    }

    // ����Ԥ������Ϣ��������
    void forwardChuxinMessage(const PrivateMessageEvent &event){
        int64_t groupId = 479646367;
        size_t spaceIndex = 2;

        string msg = event.message.substr(spaceIndex + 1);

        // ��Ҫ at ĳ��
        if(msg.find("@") == 0){
            spaceIndex = msg.find(" ");
            if(spaceIndex != string::npos){
                string atIdStr = msg.substr(1, spaceIndex - 1);
                if(atIdStr == "1"){
                    atIdStr = "3039744519";
                }

                string newMsg = msg.substr(spaceIndex + 1);
                string convertMsg = newMsg;
                if(newMsg == "0"){
                    convertMsg = "���²�ָ��";
                }else if(newMsg == "1"){
                    convertMsg = "����";
                }else if(newMsg == "2"){
                    convertMsg = "��ǩ";
                }else if(newMsg.find("3") == 0){
                    convertMsg = "����" + newMsg.substr(1);
                }else if(newMsg.find("4") == 0){
                    convertMsg = "��" + newMsg.substr(1);
                }



                msg = "[CQ:at,qq=" + atIdStr + "] " + convertMsg;

            }
        }

        try {
            send_group_message(groupId, msg); // ����Ⱥ��Ϣ
            
        } catch (ApiError &err) { // ���Է���ʧ��
            logging::warning("Ⱥ��", "Ⱥ����Ϣ����ʧ��, ������: " + to_string(err.code));
        }
    }


}

