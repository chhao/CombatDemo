//
//  BattleLayer.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#include "BattleLayer.h"
#include "HelperUtil.h"
#include "Game.h"
#include "GameScene.h"

using namespace cocos2d;

BattleLayer::BattleLayer()
{
	
}

BattleLayer::~BattleLayer()
{
	
}

bool BattleLayer::init()
{
	if(!CCLayer::init())
		return false;
	
	return true;
}

void BattleLayer::onEnter()
{
	runAction(CCSequence::create(CCDelayTime::create(2.0),CCCallFunc::create(this, callfunc_selector(BattleLayer::battleEnd)),NULL));
	
	return CCLayer::onEnter();
}

void BattleLayer::battleEnd()
{
	Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Result);
}