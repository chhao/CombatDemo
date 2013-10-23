//
//  FTUELayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/22/13.
//
//

#ifndef __CombatDemo__FTUELayer__
#define __CombatDemo__FTUELayer__

#include <iostream>
#include "cocos2d.h"

class FTUENode : public cocos2d::CCNode
{
public:
	CREATE_FUNC(FTUENode);
	
	FTUENode();
	~FTUENode();
	
	bool init();

	enum FTUEStep
	{
		Info = 0,
		ClickTile,
//		TerrainInfo,
		SelectCard,
		FinishSelectCard,
		SelectTrap,
		SelectGuard,
		Start,
		Succeed,
	};

	void showFTUE(FTUEStep step);
private:
	cocos2d::CCLabelTTF* m_label;
};


#endif /* defined(__CombatDemo__FTUELayer__) */
