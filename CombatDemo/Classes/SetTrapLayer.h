//
//  SetTrapLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/20/13.
//
//

#ifndef __CombatDemo__SetTrapLayer__
#define __CombatDemo__SetTrapLayer__

#include <iostream>
#include "cocos2d.h"

class SetTrapLayer : public cocos2d::CCNode
{
public:
	CREATE_FUNC(SetTrapLayer);
	
	SetTrapLayer();
	~SetTrapLayer();
	
	bool init();
	
	int isHit(cocos2d::CCPoint pt);
	
	void resetCurSel();
private:
	cocos2d::CCSprite* getHitSprite(cocos2d::CCPoint pt);
	
	enum ItemTag
	{
		ItemTrapSpint = 1,
		ItemTrapFire = 2,
		ItemGuardAttack = 3,
		ItemGuardDefense = 4,
	};

	cocos2d::CCSprite* m_trapSpint;
	cocos2d::CCSprite* m_trapFire;
	cocos2d::CCSprite* m_guardAttack;
	cocos2d::CCSprite* m_guardDefense;
	
	cocos2d::CCSprite* m_curSel;
};
#endif /* defined(__CombatDemo__SetTrapLayer__) */
