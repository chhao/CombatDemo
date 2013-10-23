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
	m_ftueNode->release();
}

bool ResultLayer::init()
{
	if(!CCLayer::init())
		return false;
	
	readLayout(this, "ResultLayer.json");
	
	m_backSprite = (CCSprite*)getChildByTag(ResultLayer::BackSprite);
	
	m_banner = CCSprite::create("win.png");
	m_banner->setPosition(ccp(320, 360));
	addChild(m_banner);
	
	m_ftueNode = FTUENode::create();
	m_ftueNode->retain();
	
	return true;
}

void ResultLayer::onEnter()
{
	setTouchEnabled(true);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

	if(Game::getInstance()->isInFTUE())
	{
		m_ftueNode->showFTUE(FTUENode::Succeed);
		addChild(m_ftueNode);
	}
	
	return CCLayer::onEnter();
}

void ResultLayer::onExit()
{
	m_ftueNode->removeFromParent();
	
	return CCLayer::onExit();
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

void ResultLayer::setResult(bool bWin)
{
	if(bWin)
	{
		((CCLabelTTF*)getChildByTag(1))->setString("100");
		((CCLabelTTF*)getChildByTag(2))->setString("500");
		
		m_banner->setTexture(CCTextureCache::sharedTextureCache()->addImage("win.png"));
	}
	else
	{
		((CCLabelTTF*)getChildByTag(1))->setString("0");
		((CCLabelTTF*)getChildByTag(2))->setString("0");
		
		m_banner->setTexture(CCTextureCache::sharedTextureCache()->addImage("lose.png"));
	}
}
