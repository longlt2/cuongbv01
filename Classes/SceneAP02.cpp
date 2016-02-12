#include "SceneAP02.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include <audio/include/AudioEngine.h>
#include <audio/include/SimpleAudioEngine.h>
#include <MacroUtils.h>
#include "SceneAP03.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SceneAP02::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SceneAP02::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneAP02::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto lAP = CSLoader::createNode("LayerAP02.csb");
    (lAP)->setAnchorPoint(Vec2(0.5f, 0.5f));
    (lAP)->setScale(SCREEN_SCALE_Y(lAP));
    (lAP)->setPosition(SCREEN_X(0.5f), SCREEN_Y(0.5f));
    addChild(lAP);

    _audNarratorId = cocos2d::experimental::AudioEngine::play2d("AP02.mp3", false, 1.f);

    EventListenerTouchAllAtOnce *listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = [=, this](const std::vector<Touch*>& touches, Event *pEvent)
    {
        int tagLeft = 41;
        int tagRight = 40;
        for (auto touch: touches)
        {
            // if (pRedVirgin)
            // {
                float lenWithLeft = (CHILD_WPOS_BY_TAG(lAP, tagLeft) - touch->getLocation()).length();
                float lenWithRight = (CHILD_WPOS_BY_TAG(lAP, tagRight) - touch->getLocation()).length();
                float contentSizeLeft = BOUNDING_W(lAP->getChildByTag(tagLeft), 1);
                float contentSizeRight = BOUNDING_W(lAP->getChildByTag(tagRight), 1);
                if (lenWithLeft <= BOUNDING_W(lAP->getChildByTag(tagLeft), 1))
                {
                    Director::getInstance()->replaceScene(SceneAP03::createScene());
                    CocosDenshion::SimpleAudioEngine::end();
                    return;
                }

                if (lenWithRight <= BOUNDING_W(lAP->getChildByTag(tagRight), 1))
                {
                    // Director::getInstance()->replaceScene(SceneAP04::createScene());
                    return;
                }
            // }
        }
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void SceneAP02::onExit()
{
    if(_audNarratorId != cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID)
    {
        cocos2d::experimental::AudioEngine::stop(_audNarratorId);
    }
    Node::onExit();
}
