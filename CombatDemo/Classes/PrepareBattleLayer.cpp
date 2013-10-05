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
#include "GameScene.h"
using namespace cocos2d;

PrepareBattleLayer::PrepareBattleLayer()
:m_terrain(NULL)
,m_selectGroup(NULL)
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
	
	m_selectGroup = SelectBackGround::create();
	addChild(m_selectGroup);
	m_selectGroup->setVisible(false);
	
	return true;
}

void PrepareBattleLayer::onEnter()
{
	setTouchEnabled(true);
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	
	updateTerrain();
	
	return CCLayer::onEnter();
}

void PrepareBattleLayer::onExit()
{
	if(m_terrain)
	{
		m_terrain->removeFromParent();
		m_terrain = NULL;
	}
	m_selectGroup->setVisible(false);
	
	return CCLayer::onExit();
}

void PrepareBattleLayer::updateTerrain()
{
	if(m_terrain)
	{
		m_terrain->removeFromParent();
		m_terrain = NULL;
	}
	
	int world = Game::getInstance()->getCurrentWorld();
	std::stringstream ss;
	ss << "map" << world << ".json";
	m_terrain = TerrainMap::createWithMap(ss.str().c_str());
	addChild(m_terrain);
}

bool PrepareBattleLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void PrepareBattleLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint touchLocation = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	
	int hit = m_terrain->isHit(touchLocation);
	if(m_terrain && m_terrain->isVisible() && hit != -1)
	{
		ShowPage(SelectCard);
		m_selectGroup->setInfo(hit);
		return;
	}

	hit = m_selectGroup->isHit(touchLocation);
	if(m_selectGroup && m_selectGroup->isVisible() && (hit== SelectBackGround::BtnCancel || hit== SelectBackGround::BtnOK))
	{
		ShowPage(Terrain);
		return;
	}
	
	if(isHit(m_startSprite->getQuad(), m_startSprite->convertToNodeSpace(touchLocation)))
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Battle);
		return;
	}
	
	if(isHit(m_backSprite->getQuad(), m_backSprite->convertToNodeSpace(touchLocation)))
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Main);
	}
	
}

void PrepareBattleLayer::ShowPage(PrepareBattleLayer::PageType type)
{
	switch (type)
	{
		case Terrain:
			m_selectGroup->setVisible(false);
			m_terrain->setVisible(true);
			break;
		case SelectCard:
			m_selectGroup->setVisible(true);
			m_terrain->setVisible(false);
			break;
		default:
			break;
	}
}