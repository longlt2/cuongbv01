#include "SceneAP01.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include <audio/include/AudioEngine.h>
#include <MacroUtils.h>
#include "SceneAP02.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SceneAP01::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SceneAP01::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneAP01::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size const &vis = VISIBLE_SIZE;
    Vec2 const &ori = ORIGIN;
    Size const &win = WIN_SIZE;
    Size const &winp = cocos2d::Director::getInstance()->getWinSizeInPixels();

    auto lAP = CSLoader::createNode("LayerAP01.csb");
    (lAP)->setAnchorPoint(Vec2(0.5f, 0.5f));
    (lAP)->setScale(SCREEN_SCALE_Y(lAP));
    (lAP)->setPosition(SCREEN_X(0.5f), SCREEN_Y(0.5f));
    addChild(lAP);

    _audNarratorId = cocos2d::experimental::AudioEngine::play2d("AP01.mp3", false, 1.f);

    EventListenerTouchAllAtOnce *listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = [=, this](const std::vector<Touch*>& touches, Event *pEvent)
    {
        Director::getInstance()->replaceScene(SceneAP02::createScene());
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void SceneAP01::onExit()
{
    if(_audNarratorId != cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID)
    {
        cocos2d::experimental::AudioEngine::stop(_audNarratorId);
    }
    Node::onExit();
}
