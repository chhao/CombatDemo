//
//  PrepareBattleLayer.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#include "PrepareBattleLayer.h"
#include "HelperUtil.h"
#include "Game.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

PrepareBattleLayer::PrepareBattleLayer()
{
	
}

PrepareBattleLayer::~PrepareBattleLayer()
{
	
}

bool PrepareBattleLayer::init()
{
	if(!CCLayer::init())
		return false;
	
	
	readLayout(this, "PreBattleLayer.json");
	
	m_startSprite = (CCSprite*)getChildByTag(PrepareBattleLayer::Start);
	m_backSprite = (CCSprite*)getChildByTag(PrepareBattleLayer::Back);
	
	return true;
}

void PrepareBattleLayer::onEnter()
{
	setTouchEnabled(true);
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	
	return CCLayer::onEnter();
}

bool PrepareBattleLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void PrepareBattleLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint touchLocation = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	
	if(isHit(m_startSprite->getQuad(), m_startSprite->convertToNodeSpace(touchLocation)))
	{
		//start
	}
	
	if(isHit(m_backSprite->getQuad(), m_backSprite->convertToNodeSpace(touchLocation)))
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Main);
	}
	
}