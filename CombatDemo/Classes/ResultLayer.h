//
//  ResultLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__ResultLayer__
#define __CombatDemo__ResultLayer__

#include <iostream>
#include "cocos2d.h"

class ResultLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(ResultLayer);
	
	ResultLayer();
	~ResultLayer();
	
	bool init();
	
	void onEnter();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void setResult(bool bWin);
private:
	enum ItemTag
	{
		BackSprite = 0,
		HpLabel = 1,
		GoldLabel = 2,
	};
	
	cocos2d::CCSprite* m_backSprite;
	cocos2d::CCSprite* m_banner;
};

#endif /* defined(__CombatDemo__ResultLayer__) */
