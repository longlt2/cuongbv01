#ifndef __SCENE_AP01_H__
#define __SCENE_AP01_H__

#include "cocos2d.h"

class SceneAP01 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    virtual void onExit() override;

    // implement the "static create()" method manually
    CREATE_FUNC(SceneAP01);

private:
    int _audNarratorId;
};

#endif // __SCENE_AP01_H__
