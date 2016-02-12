#include "SceneAP04.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include <audio/include/AudioEngine.h>
#include <MacroUtils.h>
#include <SceneAP05.h>

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SceneAP04::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SceneAP04::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneAP04::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto lAP = CSLoader::createNode("LayerAP04.csb");
    (lAP)->setAnchorPoint(Vec2(0.5f, 0.5f));
    (lAP)->setScale(SCREEN_SCALE_Y(lAP));
    (lAP)->setPosition(SCREEN_X(0.5f), SCREEN_Y(0.5f));
    addChild(lAP);

    auto lRecord = CSLoader::createNode("LayerRecord.csb");
    addChild(lRecord, 1);

    _audNarratorId = cocos2d::experimental::AudioEngine::play2d("AP04.mp3", false, 1.f);

    EventListenerTouchAllAtOnce *listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = [=, this](const std::vector<Touch*>& touches, Event *pEvent)
    {
        Director::getInstance()->replaceScene(SceneAP05::createScene());
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void SceneAP04::onExit()
{
    if(_audNarratorId != cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID)
    {
        cocos2d::experimental::AudioEngine::stop(_audNarratorId);
    }
    Node::onExit();
}
