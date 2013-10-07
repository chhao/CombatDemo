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
#include "Combat.h"
#include <sstream>
#include <iomanip>

using namespace cocos2d;

enum SpritezOrder
{
	Enemy = 10,
	CardBattle = 100,
};

BattleLayer::BattleLayer()
:m_terrain(NULL)
,m_curEnemy(0)
,m_cardbattleLayer(NULL)
{
	
}

BattleLayer::~BattleLayer()
{
	m_cardbattleLayer->release();
	m_label->release();
	m_enemySprite->release();
}

bool BattleLayer::init()
{
	if(!CCLayer::init())
		return false;
	
	m_label = CCLabelTTF::create("第1波", "", 40);
	m_label->setPosition(ccp(320,800));
	m_label->retain();
	addChild(m_label);
	
	m_enemySprite = CCSprite::create("icons/0020.png");
	m_enemySprite->retain();
	addChild(m_enemySprite,SpritezOrder::Enemy);
	
	m_cardbattleLayer = CardBattleLayer::create();
	m_cardbattleLayer->retain();
	
	return true;
}

void BattleLayer::copyHeroCards()
{
	for (int i = 0; i < 3; i++)
	{
		const CardVector& cards = Game::getInstance()->getCardGroup(i);
		
		for (int j = 0; j < 6; j++)
		{
			if(cards[j])
			{
				Card* card = new Card;
				card->clone(cards[j]);
				m_herocards[i].push_back(card);
				
			}
			else
			{
				m_herocards[i].push_back(NULL);
			}
		}
	}
}

void BattleLayer::readEnemyCards()
{
	std::stringstream ss;
	ss << "cardGroup_map" << Game::getInstance()->getCurrentWorld() << ".json";
	
	CSJson::Value root;
	readJsonFile(ss.str(), root);
	
	int level = Game::getInstance()->getCurrentLevel();
	CSJson::Value levelvalue = root[level];
	
	for (int i = 0; i < levelvalue.size(); i++)
	{
		CSJson::Value cards = levelvalue[i];
		for (int j = 0; j < cards.size(); j++)
		{
			if(cards[j] == 0)
			{
				m_enemycards[i].push_back(NULL);
			}
			else
			{
				m_enemycards[i].push_back(CardConfig::getInstance()->createCardByID(cards[j].asInt()));
			}
		}
	}
}

void BattleLayer::copyTerrainTile(TerrainMap *terrain)
{
	if(m_terrain)
	{
		m_terrain->removeFromParent();
		m_terrain = NULL;
	}
	
	m_terrain = new TerrainMap;
	m_terrain->autorelease();
	addChild(m_terrain);
	
	CCArray* children = terrain->getChildren();
	for (int i = children->count()-1; i > -1; i--)
	{
		CCNode* node = (CCNode*)children->objectAtIndex(i);
		node->retain();
		node->removeFromParent();
		m_terrain->addChild(node);
		node->release();
	}
}

void BattleLayer::onEnter()
{
	readEnemyCards();
	copyHeroCards();
	
	m_curTile = m_terrain->getTileByID(0);
	m_enemySprite->setPosition(m_curTile->getPosition());
	m_curEnemy = 0;
	m_label->setString("第1波");

	fight();
	
	return CCLayer::onEnter();
}

void BattleLayer::onExit()
{
	m_terrain->removeFromParent();
	m_terrain = NULL;
	
	for(int i = 0; i < 3; i++)
	{
		m_enemycards[i].clear();
	}

	for(int i = 0; i < 3; i++)
	{
		m_herocards[i].clear();
	}
	
	return CCLayer::onExit();
}

void BattleLayer::fight()
{
	if(m_curTile->getType() == MapTile::End)
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Result_Lose);
		return;
	}
	
	cocos2d::CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(BattleLayer::fight));
	switch (m_curTile->getMark())
	{
		case MapTile::Card1:
		case MapTile::Card2:
		case MapTile::Card3:
		{
			int result = m_cardbattleLayer->setCardGroup(m_herocards[m_curTile->getMark()], m_enemycards[m_curEnemy]);
			if(result == 1)
				m_cardbattleLayer->setBattleFinishCallback(CCCallFunc::create(this, callfunc_selector(BattleLayer::cardBattleWin)));
			else
				m_cardbattleLayer->setBattleFinishCallback(CCCallFunc::create(this, callfunc_selector(BattleLayer::cardBattleLose)));
			addChild(m_cardbattleLayer, SpritezOrder::CardBattle);
		}
			break;
		default:
		{
			MapTile* nextTile = m_terrain->getTileByID(m_curTile->getNextTile());
			m_enemySprite->runAction(CCSequence::create(CCMoveTo::create(1.0, nextTile->getPosition()),callback,NULL));
			m_curTile = nextTile;
		}
			break;
	}
}

void BattleLayer::cardBattleWin()
{
	removeChild(m_cardbattleLayer);
	
	m_curTile = m_terrain->getTileByID(0);
	m_enemySprite->setPosition(m_curTile->getPosition());
	m_curEnemy++;
	std::stringstream ss;
	ss << "第" << m_curEnemy+1 << "波";
	m_label->setString(ss.str().c_str());
	
	fight();
	
	if(m_curEnemy == 3)
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Result_Win);
	}
}

void BattleLayer::cardBattleLose()
{
	removeChild(m_cardbattleLayer);
	
	cocos2d::CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(BattleLayer::fight));
	MapTile* nextTile = m_terrain->getTileByID(m_curTile->getNextTile());
	m_enemySprite->runAction(CCSequence::create(CCMoveTo::create(1.0, nextTile->getPosition()),callback,NULL));
	m_curTile = nextTile;
}
