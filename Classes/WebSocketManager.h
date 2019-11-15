#ifndef __WEBSOCKET_MANAGER_H__
#define __WEBSOCKET_MANAGER_H__

#include "cocos2d.h"
#include "network/WebSocket.h"
#include "Packet.h"

using namespace cocos2d;

using Payload = json11::Json;

class SocketCallback {
public:
    virtual ~SocketCallback() {}
    virtual void onOpen(network::WebSocket* ws) = 0;
    virtual void onMessage(network::WebSocket* ws, const PacketType packet_id, const Payload& data) = 0;
    virtual void onClose(network::WebSocket* ws) = 0;
    virtual void onError(network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) = 0;
};

class WebSocketManager : public cocos2d::network::WebSocket::Delegate {
public:
    static WebSocketManager& GetInstance() {
        static WebSocketManager instance;
        return instance;
    }

    virtual ~WebSocketManager();
    void Initialize();

    bool Connect(SocketCallback* delegates, const std::string& url);
    void Close();
    void Send(const Payload& payload);

    network::WebSocket* socket() const;

    void SetDelegate(SocketCallback* scene);

    void onOpen(network::WebSocket* ws) override;
    void onMessage(network::WebSocket* ws, const network::WebSocket::Data& data) override;
    void onClose(network::WebSocket* ws) override;
    void onError(network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) override;

private:
    std::shared_ptr<network::WebSocket> websocket_ = nullptr;
    SocketCallback* callback_ = nullptr;
}; 

#endif // __WEBSOCKET_MANAGER_H__
