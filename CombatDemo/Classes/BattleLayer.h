//
//  BattleLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__BattleLayer__
#define __CombatDemo__BattleLayer__

#include <iostream>
#include "cocos2d.h"

class BattleLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(BattleLayer);
	
	BattleLayer();
	~BattleLayer();
	
	bool init();
	
	void onEnter();
	
	void battleEnd();
};


#endif /* defined(__CombatDemo__BattleLayer__) */
