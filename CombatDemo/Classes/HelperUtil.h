//
//  HelperUtil.h
//  FairyTales
//
//  Created by Hao Chen on 3/31/13.
//
//

#ifndef __FairyTales__HelperUtil__
#define __FairyTales__HelperUtil__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "json_lib.h"

typedef std::vector<std::string> StringVector;
typedef std::list<std::string> StringList;


bool isHit(cocos2d::CCSprite* sprite, cocos2d::CCTouch *pTouch);
bool isHit(cocos2d::CCSprite* sprite, const cocos2d::CCPoint& pt, int exten_width, int exten_height);
bool isHit(cocos2d::extension::CCScale9Sprite* sprite,const cocos2d::CCPoint& pt);
bool isHit(const cocos2d::ccV3F_C4B_T2F_Quad& quad, const cocos2d::CCPoint& pt);
bool isHit(const cocos2d::CCRect& rect, const cocos2d::CCPoint& pt);

void split(std::string src, const char* token, StringVector& vect);
bool isPointInRect(const cocos2d::CCPoint& pt, const cocos2d::CCRect& rect);

void addAnimationFiles(const std::string& name);

void addAnimationFrames(cocos2d::CCArray* frames, int startIndex, int endIndex, const std::string& prestr, const std::string& suffixstr);

cocos2d::CCParticleSystemQuad* createParticle(const std::string &particle, const cocos2d::CCPoint &pos);

int getRandomPercentage();

cocos2d::CCNode* createNodeFromLayout(const std::string& layoutFileName, cocos2d::CCPoint offset);

bool readLayout(cocos2d::CCNode* parent, const std::string& layoutFileName, cocos2d::CCPoint offset = cocos2d::CCPointZero);

std::string getMD2ResourceFullPath(const std::string& file);
std::string getUIResourceFullPath(const std::string& file);
std::string getSpriteFrameResourceFullPath(const std::string& file);

const char* getResolutionPath();
bool isHighResolution();
float getResolutionScale();

void readJsonFile(const std::string& filename, CSJson::Value& root);

#endif /* defined(__FairyTales__HelperUtil__) */
