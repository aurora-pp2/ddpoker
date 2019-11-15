#include "SevenPokerScene.h"
#include "SimpleAudioEngine.h"
#include "LobbyScene.h"

USING_NS_CC;

using namespace json11;

class TableController {
public:
    TableController(Layer* layer) : table_layer_(layer) {
    }

    void NotiJoinedPlayer(const Json& payload) {
       const size_t id = std::stoll(payload["id"].string_value());
       const std::string name = payload["name"].string_value();
       const int64_t money = std::stoll(payload["money"].string_value());
       const int seat_index = payload["seat_index"].int_value();
    }

private:
    Layer* table_layer_;
};


Scene* SevenPokerScene::createScene()
{
    return SevenPokerScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SevenPokerScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    WebSocketManager::GetInstance().SetDelegate(this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    center_ = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    table_layer_ = Layer::create();

    const Json req_join_seven_table = Json::object{
     { "packet_id", static_cast<int>(kReqJoinSevenTable) },
     { "random_table", true },
     { "password", "abc"},
    };

    WebSocketManager::GetInstance().Send(req_join_seven_table);
    
    return true;
}

void SevenPokerScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

// 네크워크 콜백
void SevenPokerScene::onOpen(network::WebSocket* ws) {
    //WebSocketManager::GetInstance().Send(ReqUserInfo(true, 154, "").ToJson());

}

void SevenPokerScene::onMessage(network::WebSocket* ws, const PacketType packet_id, const Payload& payload) {
    if (packet_id == kNotiJoinedPlayer) {
        TableController(table_layer_).NotiJoinedPlayer(payload);
    }
}

void SevenPokerScene::onClose(network::WebSocket* ws) {

}

void SevenPokerScene::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) {

}
