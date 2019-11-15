#include "LobbyScene.h"
#include "SimpleAudioEngine.h"
#include "WebSocketManager.h"
#include "ui/UIButton.h"
#include "SevenPokerScene.h"

USING_NS_CC;

Scene* LobbyScene::createScene()
{
    return LobbyScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LobbyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    center_ = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(LobbyScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // 포커 시작 버튼
    auto button = ui::Button::create("ui/button/StartSevenPoker.jpg", "ui/button/StartSevenPoker.jpg", "ui/button/StartSevenPoker.jpg");
    button->setPosition(Vec2(center_.x + 300, center_.y - 275.0f));
    button->setScale(1.2f);
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            //audio->playEffect("Sound/ButtonClick.mp3");
        } else if (type == ui::Widget::TouchEventType::ENDED) {
            const auto scene = SevenPokerScene::createScene();
            auto director = Director::getInstance();
            director->runWithScene(scene);
        } else if (type == ui::Widget::TouchEventType::CANCELED) {
            //close_button_->setScale(0.1f);
        }
    });


    // 네트워크 접속
    WebSocketManager::GetInstance().Initialize();
    WebSocketManager::GetInstance().Connect(this, "ws://127.0.0.1:3000");

    return true;
}

void LobbyScene::menuCloseCallback(Ref* pSender) {

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

    auto socket = WebSocketManager::GetInstance().socket();
    if (socket != nullptr) {
        socket->close();
    }
    Director::getInstance()->end();
}

// 네크워크 콜백
void LobbyScene::onOpen(network::WebSocket* ws) {
    WebSocketManager::GetInstance().Send(ReqUserInfo(true, 19, "").ToJson());
    CCLOG("onOpen");
}

void LobbyScene::onMessage(network::WebSocket* ws, const PacketType packet_id, const Payload& payload) {
    //CCLOG("onMessage: %s", payload);
    if (packet_id == kResUserInfo) {
        size_t id = std::stoll(payload["id"].string_value());
        int64_t money = std::stoll(payload["money"].string_value());
        std::string name = payload["name"].string_value();
    }
     
}

void LobbyScene::onClose(network::WebSocket* ws) {
    CCLOG("onClose");
}

void LobbyScene::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) {
    CCLOG("onError");
}
