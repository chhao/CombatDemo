//
//  FTUELayer.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/22/13.
//
//

#include "FTUELayer.h"

using namespace cocos2d;

FTUENode::FTUENode()
{
	
}

FTUENode::~FTUENode()
{
	
}

bool FTUENode::init()
{
	if(!CCNode::init())
		return false;
	
	CCSprite* bg = CCSprite::create("card_set.png");
	bg->setScale(2.0);
	bg->setOpacity(180);
	addChild(bg);
	CCSprite* guide = CCSprite::create("Guide.png");
	guide->setPosition(ccp(-196,0));
	addChild(guide);
	m_label = CCLabelTTF::create("", "", 24,CCSize(400,200),kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
	m_label->setPosition(ccp(74,0));
	addChild(m_label);
	
	return true;
}

void FTUENode::showFTUE(FTUENode::FTUEStep step)
{
	std::string str;
	CCPoint pos = ccp(320,212);
	switch (step)
	{
		case Info:
			str = "你好，大魔王！贪婪的英雄们马上就要进犯我们的地下城了。不同的是，这次有你领导我们，快带领地下城的生物们一起来防御人类的掠夺吧。";
			break;
		case ClickTile:
			str = "点击地形路径上的格子来布防我们的第一只防守部队。";
			break;
//		case TerrainInfo:
//			str = "注意地形属性与角色属性，相同属性的地形对角色有增强，安置部队时要注意哦！";
//			break;
		case SelectCard:
			str = "选择你所需要放置的部队";
			pos = ccp(320,700);
			break;
		case FinishSelectCard:
			str = "现在我们布置好了第一组部队。为了抵御强大的英雄们，还可以布置陷阱和守卫。";
			break;
		case SelectTrap:
			str = "选择一个烈火陷阱吧。烈火陷阱可以对敌人造成伤害，还能阻止他们恢复生命。";
			break;
		case SelectGuard:
			str = "攻击守卫会增强周围防守部队的攻击力，削弱敌军战斗力";
			break;
		case Start:
			str = "我们的防守部队已就位，现在该是让自大的英雄们尝尝苦果的时候了。开始吧！";
			break;
		case Succeed:
			str = "恭喜你防守住了三波敌人的进攻，这个区域已经安全了，大魔王，快去帮助其他小伙伴吧。";
			break;
		default:
			break;
	}
	m_label->setString(str.c_str());
	setPosition(pos);
}
