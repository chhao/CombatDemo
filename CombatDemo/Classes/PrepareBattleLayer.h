//
//  PrepareBattleLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__PrepareBattleLayer__
#define __CombatDemo__PrepareBattleLayer__

#include <iostream>
#include "cocos2d.h"

class PrepareBattleLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(PrepareBattleLayer);
	
	PrepareBattleLayer();
	~PrepareBattleLayer();

	bool init();
	
	void onEnter();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	
	void setMap(int ID);
private:
	enum ItemTag
	{
		Back = 0,
		Start = 1,
	};
	
	cocos2d::CCSprite* m_backSprite;
	cocos2d::CCSprite* m_startSprite;
};

#endif /* defined(__CombatDemo__PrepareBattleLayer__) */
