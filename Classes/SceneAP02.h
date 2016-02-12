#ifndef __SCENE_AP02_H__
#define __SCENE_AP02_H__

#include "cocos2d.h"

class SceneAP02 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SceneAP02);

    virtual void onExit() override;

private:
    int _audNarratorId;
};

#endif // __SCENE_AP02_H__
