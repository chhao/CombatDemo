//
//  HUDLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__HUDLayer__
#define __CombatDemo__HUDLayer__

#include <iostream>
#include "cocos2d.h"

class HUDLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(HUDLayer);
	
	HUDLayer();
	~HUDLayer();
	
	bool init();
};

#endif /* defined(__CombatDemo__HUDLayer__) */
