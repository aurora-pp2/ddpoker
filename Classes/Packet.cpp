#include "Packet.h"

using namespace json11;

ReqUserInfo::ReqUserInfo(bool success, int number, const std::string& message) 
    : success_(success), number_(number), message_(message) {

}

Payload ReqUserInfo::ToJson() const {
    Json payload = Json::object{
        { "packet_id", static_cast<int>(kReqUserInfo) },
        { "success", success_ },
        { "number", number_ },
        { "message", message_ },
    };
    return payload;
}
