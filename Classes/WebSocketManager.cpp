#include "WebSocketManager.h"

WebSocketManager::~WebSocketManager() {

}

void WebSocketManager::Initialize() {
    //websocket_ = new network::WebSocket();
}

bool WebSocketManager::Connect(SocketCallback* delegates, const std::string& url) {
    callback_ = delegates;
    websocket_ = std::make_shared<network::WebSocket>();
    return websocket_->init(*this, url);
}

void WebSocketManager::Close() {
    if (websocket_ != nullptr) {
        websocket_->close();
    }
}


void WebSocketManager::Send(const Payload& payload) {
    const std::string json_str = payload.dump();
    websocket_->send(json_str);
}


network::WebSocket* WebSocketManager::socket() const {
    return websocket_.get();
}

void WebSocketManager::SetDelegate(SocketCallback* callback) {
    callback_ = callback;
}

// 네크워크 콜백
void WebSocketManager::onOpen(network::WebSocket* ws) {
    callback_->onOpen(ws);
}

void WebSocketManager::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data) {
    std::string err;
    const auto json = json11::Json::parse(data.bytes, err);
    if (!err.empty()) {
        return;
    }
    const auto packet_id = json["packet_id"].int_value();
    callback_->onMessage(ws, static_cast<PacketType>(packet_id), json);
}

void WebSocketManager::onClose(network::WebSocket* ws) {
    callback_->onClose(ws);
}

void WebSocketManager::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) {
    callback_->onError(ws, error);
}