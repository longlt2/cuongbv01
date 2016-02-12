#include "SceneAP05.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include <audio/include/AudioEngine.h>
#include <MacroUtils.h>

USING_NS_CC;

using namespace cocostudio::timeline;

const int SceneAP05::_sSpriteRedVirginTag = 45;
const int SceneAP05::_sSpriteWolfTag = 46;
const float SceneAP05::_sFadingTime = .5f;

Scene* SceneAP05::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SceneAP05::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneAP05::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    _state = STATE_BEGIN;
    _stateDirty = false;

    auto lAP = CSLoader::createNode("LayerAP05.csb");
    (lAP)->setAnchorPoint(Vec2(0.5f, 0.5f));
    (lAP)->setScale(SCREEN_SCALE_Y(lAP));
    (lAP)->setPosition(SCREEN_X(0.5f), SCREEN_Y(0.5f));
    lAP->setTag(LAYER_TAG);
    addChild(lAP);

    auto lRecord = CSLoader::createNode("LayerRecord.csb");
    addChild(lRecord, 1);

    _audNarratorId = cocos2d::experimental::AudioEngine::play2d("AP05.mp3", false, 1.f);

    EventListenerTouchAllAtOnce *listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = [=, this](const std::vector<Touch*>& touches, Event *pEvent)
    {
        if(lAP == nullptr)
        {
            return;
        }
        cocos2d::experimental::AudioEngine::pause(_audNarratorId);
        cocos2d::experimental::AudioEngine::setCurrentTime(_audNarratorId, 27.f);
        cocos2d::experimental::AudioEngine::resume(_audNarratorId);
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->schedule(CC_CALLBACK_1(SceneAP05::update, this), 1.f, "update_state");

    return true;
}

void SceneAP05::onExit()
{
    Node::onExit();
    if(_audNarratorId != cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID)
    {
        cocos2d::experimental::AudioEngine::stop(_audNarratorId);
    }
}

void SceneAP05::update(float delta)
{
    Node::update(delta);
    auto lAP = this->getChildByTag(LAYER_TAG);
    if(lAP == nullptr)
    {
        return;
    }
    if(_state < STATE_PICKING_FRUIT && cocos2d::experimental::AudioEngine::getCurrentTime(_audNarratorId) >= 46.f)
    {
        _stateDirty = true;
        _state = STATE_PICKING_FRUIT;
    }
    else if(_state < STATE_CRYING_WOLF && cocos2d::experimental::AudioEngine::getCurrentTime(_audNarratorId) >= 37.f)
    {
        _stateDirty = true;
        _state = STATE_CRYING_WOLF;
    }
    else if(_state < STATE_ELEPHANT && cocos2d::experimental::AudioEngine::getCurrentTime(_audNarratorId) >= 27.f)
    {
        _stateDirty = true;
        _state = STATE_ELEPHANT;
    }

    if(_stateDirty == true)
    {
        switch(_state)
        {
            case STATE_ELEPHANT:
            {
                Sprite *spriteRedVirgin = dynamic_cast<Sprite *>(lAP->getChildByTag(SceneAP05::_sSpriteRedVirginTag));
                spriteRedVirgin->runAction(Sequence::create(
                    FadeOut::create(SceneAP05::_sFadingTime),
                    CallFunc::create( [=, this]() {
                        spriteRedVirgin->setTexture("voi.png");
                        spriteRedVirgin->setPositionY( spriteRedVirgin->getPositionY() + BOUNDING_H(spriteRedVirgin, .25f));
                        spriteRedVirgin->setScale(spriteRedVirgin->getScale() * 2);
                    }),
                    spriteRedVirgin->runAction(FadeIn::create(SceneAP05::_sFadingTime)),
                    nullptr
                    ));

                break;
            }
            case STATE_CRYING_WOLF:
            {
                Sprite *spriteWolf = dynamic_cast<Sprite *>(lAP->getChildByTag(SceneAP05::_sSpriteWolfTag));
                spriteWolf->runAction(Sequence::create(
                    FadeOut::create(SceneAP05::_sFadingTime),
                    CallFunc::create( [=, this]() {
                        spriteWolf->setTexture("soi02khocnhe.png");
                    }),
                    spriteWolf->runAction(FadeIn::create(SceneAP05::_sFadingTime)),
                    nullptr
                    ));
                break;
            }
            case STATE_PICKING_FRUIT:
            {
                Sprite *spriteWolf = dynamic_cast<Sprite *>(lAP->getChildByTag(SceneAP05::_sSpriteWolfTag));
                Sprite *spriteRedVirgin = dynamic_cast<Sprite *>(lAP->getChildByTag(SceneAP05::_sSpriteRedVirginTag));
                spriteRedVirgin->runAction(Sequence::create(
                    FadeOut::create(SceneAP05::_sFadingTime),
                    CallFunc::create( [=, this]() {
                        spriteRedVirgin->setTexture("khando.png");
                        spriteRedVirgin->setScale(spriteRedVirgin->getScale() / 2);
                        spriteRedVirgin->setPositionY( spriteRedVirgin->getPositionY() - BOUNDING_H(spriteRedVirgin, .25f));
                    }),
                    spriteRedVirgin->runAction(FadeIn::create(SceneAP05::_sFadingTime)),
                    nullptr
                    ));
                spriteWolf->runAction(FadeOut::create(SceneAP05::_sFadingTime));
                break;
            }
            case STATE_END:
            {
                break;
            }
        }
        _stateDirty = false;
    }
}
