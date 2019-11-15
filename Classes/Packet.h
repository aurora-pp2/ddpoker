#ifndef __PACKET_H__
#define __PACKET_H__

#include <string>

#include "json11.hpp"

using Payload = json11::Json;

enum PacketType { 
    kReqUserInfo = 0, kResUserInfo,
    kReqJoinSevenTable = 20, kResJoinSevenTable, kNotiJoinedPlayer, kNotiOtherPlayerLeaveSevenTable
};

struct ReqUserInfo {
    static const size_t kPacketId = kReqUserInfo;

    ReqUserInfo(bool success_, int number, const std::string& message);
    Payload ToJson() const;

    bool success_ = false;
    int number_ = 1;
    std::string message_;
};


#endif