#pragma once


namespace xmalloc::adv{
    // group_dao.cpp
    void advCmd(const PrivateMessageEvent &event);

    // member.cpp
    void startAdvThread(string cmd);
    void stopAdvThread();
    void startGroupInfoCheck();
}