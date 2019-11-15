#include "Cache.h"
#include "base/CCUserDefault.h"

size_t Cache::GetUserId() const {
    return std::stoll(cocos2d::UserDefault::getInstance()->getStringForKey("user_id", "0"));
}

void Cache::SaveUserId(const std::string& user_id) {
    cocos2d::UserDefault::getInstance()->setStringForKey("user_id", user_id);
}

