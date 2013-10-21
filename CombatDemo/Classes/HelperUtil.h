

#ifndef ____HelperUtil__
#define ____HelperUtil__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "json_lib.h"

bool isHit(cocos2d::CCSprite* sprite, cocos2d::CCTouch *pTouch);
bool isHit(cocos2d::CCSprite* sprite, const cocos2d::CCPoint& pt, int exten_width, int exten_height);
bool isHit(cocos2d::extension::CCScale9Sprite* sprite,const cocos2d::CCPoint& pt);
bool isHit(const cocos2d::ccV3F_C4B_T2F_Quad& quad, const cocos2d::CCPoint& pt);
bool isHit(const cocos2d::CCRect& rect, const cocos2d::CCPoint& pt);

bool isPointInRect(const cocos2d::CCPoint& pt, const cocos2d::CCRect& rect);

bool readLayout(cocos2d::CCNode* parent, const std::string& layoutFileName, cocos2d::CCPoint offset = cocos2d::CCPointZero);

void readJsonFile(const std::string& filename, CSJson::Value& root);

#endif /* defined(____HelperUtil__) */
