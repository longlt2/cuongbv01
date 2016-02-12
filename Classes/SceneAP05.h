#ifndef __SCENE_AP05_H__
#define __SCENE_AP05_H__

#include "cocos2d.h"

enum STATE
{
    STATE_BEGIN = 0,
    STATE_ELEPHANT,
    STATE_CRYING_WOLF,
    STATE_PICKING_FRUIT,
    STATE_END,
};

class SceneAP05 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SceneAP05);

    virtual void onExit() override;

    virtual void update(float delta) override;

private:
    int _audNarratorId;
    float _interval;
    int _state;
    bool _stateDirty;

    static const int _sSpriteRedVirginTag;
    static const int _sSpriteWolfTag;
    static const float _sFadingTime;
};

#endif // __SCENE_AP05_H__
