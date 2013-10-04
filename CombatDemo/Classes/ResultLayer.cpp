//
//  ResultLayer.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#include "ResultLayer.h"
#include "HelperUtil.h"
#include "Game.h"
#include "GameScene.h"

using namespace cocos2d;

ResultLayer::ResultLayer()
{
	
}

ResultLayer::~ResultLayer()
{
	
}

bool ResultLayer::init()
{
	if(!CCLayer::init())
		return false;
	
	readLayout(this, "ResultLayer.json");
	
	m_backSprite = (CCSprite*)getChildByTag(ResultLayer::BackSprite);
	
	return true;
}

void ResultLayer::onEnter()
{
	setTouchEnabled(true);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

	return CCLayer::onEnter();
}

bool ResultLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void ResultLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint touchLocation = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	
	if(isHit(m_backSprite->getQuad(), m_backSprite->convertToNodeSpace(touchLocation)))
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Main);
	}
}
