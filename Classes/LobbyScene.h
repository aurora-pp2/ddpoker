#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "WebSocketManager.h"

using namespace cocos2d;

class LobbyScene : public cocos2d::Scene, public SocketCallback
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LobbyScene);

    void onOpen(network::WebSocket* ws) override;
    void onMessage(network::WebSocket* ws, const PacketType packet_id, const Payload& payload) override;
    void onClose(network::WebSocket* ws) override;
    void onError(network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) override;

private:
    Vec2 center_;
};

#endif // __LOBBY_SCENE_H__
