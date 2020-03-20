#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include <cqcppsdk/cqcppsdk.h>

#include "command.hpp"
#include "group_timer.hpp"

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;



CQ_INIT {
    on_enable([] { 
        xmalloc::startTiaoxiThread();
        logging::info("����", "���������"); 
    });

    on_private_message([](const PrivateMessageEvent &event) {
        try {
            
            xmalloc::processMessage(event);
        } catch (ApiError &err) {
            logging::warning("˽��", "˽����Ϣ�������, ������: " + to_string(err.code));
        }
    });

    on_message([](const MessageEvent &event) {
        logging::debug("��Ϣ", "�յ���Ϣ: " + event.message + "\nʵ������: " + typeid(event).name());
    });

    on_group_message([](const GroupMessageEvent &event) {
        static const set<int64_t> ENABLED_GROUPS = {132847879, 1234567};
        if (ENABLED_GROUPS.count(event.group_id) == 0) return; // �������õ�Ⱥ��, ����

        try {
            // send_message(event.target, event.message); // ����
            // auto mem_list = get_group_member_list(event.group_id); // ��ȡȺ��Ա�б�
            // string msg;
            // for (auto i = 0; i < min(10, static_cast<int>(mem_list.size())); i++) {
            //     msg += "�ǳ�: " + mem_list[i].nickname + "\n"; // ƴ��ǰʮ����Ա���ǳ�
            // }
            // send_group_message(event.group_id, "see you"); // ����Ⱥ��Ϣ
            // send_group_message(132847879, "next time"); // ����Ⱥ��Ϣ
        } catch (ApiError &err) { // ���Է���ʧ��
            logging::warning("Ⱥ��", "Ⱥ����Ϣ����ʧ��, ������: " + to_string(err.code));
        }
        if (event.is_anonymous()) {
            logging::info("Ⱥ��", "��Ϣ��������Ϣ, �����ǳ�: " + event.anonymous.name);
        }
        // event.block(); // ��ֹ��ǰ�¼����ݵ���һ�����
    });

    on_group_upload([](const auto &event) { // ����ʹ�� auto �Զ��ƶ�����
        // stringstream ss;
        // ss << "���ϴ���һ���ļ�, �ļ���: " << event.file.name << ", ��С(�ֽ�): " << event.file.size;
        // try {
        //     send_message(event.target, ss.str());
        // } catch (ApiError &) {
        // }
    });
}

CQ_MENU(menu_demo_1) {
    logging::info("�˵�", "����˵�1");
}

CQ_MENU(menu_demo_2) {
    logging::info("�˵�", "����˵�2");
}



