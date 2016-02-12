#ifndef MACRO_UTILS_H
#define MACRO_UTILS_H

#define HEX_TO_R(hex) (((hex) & 0xFF0000U) >> 16)
#define HEX_TO_G(hex) (((hex) & 0xFF00U) >> 8)
#define HEX_TO_B(hex) (((hex) & 0xFFU))
#define RGB_TO_HEX(r,g,b) ( (((r)&0xFF)<<16) | (((g)&0xFF)<<8) | ((b)&0xFF) )
#define HEX_TO_C3B(hex) (cocos2d::Color3B(HEX_TO_R(hex), HEX_TO_G(hex), HEX_TO_B(hex)))

#define VISIBLE_SIZE (cocos2d::Director::getInstance()->getVisibleSize())
#define ORIGIN (cocos2d::Director::getInstance()->getVisibleOrigin())
#define WIN_SIZE (cocos2d::Director::getInstance()->getWinSize())

#define SCREEN_X(prop) ((VISIBLE_SIZE.width * (prop)) + (ORIGIN.x))
#define SCREEN_Y(prop) ((VISIBLE_SIZE.height * (prop)) + (ORIGIN.y))
#define SCREEN_SIZE(propX, propY)   cocos2d::Size(SCREEN_X(propX), SCREEN_Y(propY))
#define SCREEN_VEC2(propX, propY)   cocos2d::Vec2(SCREEN_X(propX), SCREEN_Y(propY))

#define CONTENT_X(nodePtr, prop) ((nodePtr)->getContentSize().width * (prop))
#define CONTENT_Y(nodePtr, prop) ((nodePtr)->getContentSize().height * (prop))

#define SCREEN_SCALE_X(nodePtr) (SCREEN_X(1) / CONTENT_X(nodePtr, 1))
#define SCREEN_SCALE_Y(nodePtr) (SCREEN_Y(1) / CONTENT_Y(nodePtr, 1))

#define BOUNDING_W(nodePtr, prop) ((nodePtr)->getBoundingBox().size.width * (prop))
#define BOUNDING_H(nodePtr, prop) ((nodePtr)->getBoundingBox().size.height * (prop))

#define CHILD_WPOS_BY_TAG(parent, tag) ((parent)->convertToWorldSpace((parent)->getChildByTag(tag)->getPosition()))

#define LOGI(format,...)            CCLOG("%s[%s][%d]: " format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LAYER_TAG   (0xFFFF)

#endif // MACRO_UTILS_H
