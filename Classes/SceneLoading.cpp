#include "SceneLoading.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MacroUtils.h"
#include "SceneAP01.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SceneLoading::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SceneLoading::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneLoading::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto lLoading = CSLoader::createNode("LayerLoading.csb");
    (lLoading)->setAnchorPoint(Vec2(0.5f, 0.5f));
    (lLoading)->setScale(SCREEN_SCALE_Y(lLoading));
    (lLoading)->setPosition(SCREEN_X(0.5f), SCREEN_Y(0.5f));

    addChild(lLoading);

    EventListenerTouchAllAtOnce *listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = [=, this](const std::vector<Touch*>& touches, Event *pEvent)
    {
        Director::getInstance()->replaceScene(SceneAP01::createScene());
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
