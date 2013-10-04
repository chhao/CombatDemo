//
//  HUDLayer.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#include "HUDLayer.h"
#include "HelperUtil.h"

HUDLayer::HUDLayer()
{
	
}

HUDLayer::~HUDLayer()
{
	
}

bool HUDLayer::init()
{
	if(!CCLayer::init())
		return false;
	
	readLayout(this, "HudLayer.json");
	
	return true;
}
