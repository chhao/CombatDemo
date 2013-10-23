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
#include "QuestDialog.h"
#include "FTUELayer.h"
using namespace cocos2d;

PrepareBattleLayer::PrepareBattleLayer()
:m_terrain(NULL)
,m_selectGroup(NULL)
{
	
}

PrepareBattleLayer::~PrepareBattleLayer()
{
	m_ftueNode->release();
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
	
	m_setTrapLayer = SetTrapLayer::create();
	addChild(m_setTrapLayer);
	
	m_ftueNode = FTUENode::create();
	m_ftueNode->retain();
	
	return true;
}

void PrepareBattleLayer::onEnter()
{
	setTouchEnabled(true);
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	
	updateTerrain();

	if(Game::getInstance()->isInFTUE())
	{
		m_ftueStep = 0;
		m_ftueNode->showFTUE(FTUENode::Info);
		addChild(m_ftueNode,100);		
	}
	
	QuestDialog* questdlg = QuestDialog::create();
	m_pParent->addChild(questdlg, 5);
	
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
	m_ftueNode->removeFromParent();
	
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
	
	if(Game::getInstance()->isInFTUE())
	{
		switch (m_ftueStep)
		{
			case 0:
			case 3:
			case 4:
			case 5:
			{
				m_ftueStep++;
				m_ftueNode->showFTUE(FTUENode::FTUEStep(m_ftueStep));
			}
				break;
			default:
				break;
		}
	}
	
	
	if(m_terrain && m_terrain->isVisible())
	{
		int hit = m_terrain->isHit(touchLocation);
		if(hit != -1)
		{
			if(m_setTrapType == 0) //select card
			{
				ShowPage(SelectCard);
				m_selectGroup->setInfo(hit);
				if(Game::getInstance()->isInFTUE())
				{
					m_ftueNode->showFTUE(FTUENode::SelectCard);
					m_ftueStep++;
				}
				return;
			}
			else  //put trap
			{
				m_terrain->markCurTile((MapTile::TileMark)(m_setTrapType+2));
				m_setTrapType = 0;
				m_setTrapLayer->resetCurSel();
			}
		}
	}

	if(m_selectGroup && m_selectGroup->isVisible())
	{
		int hit = m_selectGroup->isHit(touchLocation);
		if(hit == SelectBackGround::BtnOK)
		{
			int selectIndex = m_selectGroup->getSelectIndex();
			if(selectIndex != -1)
			{
				m_terrain->markCurTile((MapTile::TileMark)selectIndex);
			}
			
			ShowPage(Terrain);
			if(Game::getInstance()->isInFTUE())
			{
				m_ftueNode->showFTUE(FTUENode::FinishSelectCard);
				m_ftueStep++;
			}
			return;
		}
		else if(hit == SelectBackGround::BtnCancel)
		{
			ShowPage(Terrain);
			return;			
		}
	}
	
	if(isHit(m_startSprite->getQuad(), m_startSprite->convertToNodeSpace(touchLocation)))
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Battle);
		return;
	}
	
	if(isHit(m_backSprite->getQuad(), m_backSprite->convertToNodeSpace(touchLocation)))
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Main);
		return;
	}
	
	m_setTrapType = m_setTrapLayer->isHit(touchLocation);
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
			m_selectGroup->resetCheckStatus();
			m_terrain->setVisible(false);
			break;
		default:
			break;
	}
}

TerrainMap* PrepareBattleLayer::getTerrain()
{
	return m_terrain;
}