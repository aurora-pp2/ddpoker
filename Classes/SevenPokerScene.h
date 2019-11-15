#ifndef __SEVENPOKER_SCENE_H__
#define __SEVENPOKER_SCENE_H__

#include "cocos2d.h"
#include "WebSocketManager.h"

using namespace cocos2d;

class SevenPokerScene : public cocos2d::Scene, public SocketCallback
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SevenPokerScene);

    void onOpen(network::WebSocket* ws) override;
    void onMessage(network::WebSocket* ws, const PacketType packet_id, const Payload& payload) override;
    void onClose(network::WebSocket* ws) override;
    void onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) override;

private:
    Layer* table_layer_ = nullptr;
    Vec2 center_;
};

#endif // __SEVENPOKER_SCENE_H__
