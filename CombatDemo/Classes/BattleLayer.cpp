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

const float c_trapDelayTime = 1.0;

BattleLayer::BattleLayer()
:m_terrain(NULL)
,m_curEnemy(0)
,m_cardbattleLayer(NULL)
,m_setTrapLayer(NULL)
,m_preventEnemyBuff(0)
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
	
	m_effectLabel = CCLabelTTF::create("", "", 30);
	m_effectLabel->setPosition(ccp(320,750));
	m_effectLabel->setColor(ccc3(255,0,0));
	addChild(m_effectLabel);
	
	m_guardLabel = CCLabelTTF::create("", "", 30);
	m_guardLabel->setPosition(ccp(320,700));
	m_guardLabel->setColor(ccc3(255,255,0));
	addChild(m_guardLabel);
	
	m_enemySprite = CCSprite::create("icons/0020.png");
	m_enemySprite->retain();
	addChild(m_enemySprite,SpritezOrder::Enemy);
	
	m_cardbattleLayer = CardBattleLayer::create();
	m_cardbattleLayer->retain();
	
	m_setTrapLayer = SetTrapLayer::create();
	addChild(m_setTrapLayer);
	
	return true;
}

void BattleLayer::copyHeroCards()
{
	for (int i = 0; i < 3; i++)
	{
		m_herocards[i] = Game::getInstance()->getCardDeck(i)->clone();
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
		m_enemycards[i] = CardDeck::createCardDeck(cards);
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
		MapTile* node = (MapTile*)children->objectAtIndex(i);
		node->retain();
		node->removeFromParent();
		m_terrain->addTile(node);
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
	
	setTouchEnabled(true);
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

	return CCLayer::onEnter();
}

void BattleLayer::onExit()
{
	m_terrain->removeFromParent();
	m_terrain = NULL;
	
	for(int i = 0; i < 3; i++)
	{
		delete m_enemycards[i];
	}

	for(int i = 0; i < 3; i++)
	{
		delete m_herocards[i];
	}
	
	m_setTrapLayer->resetCurSel();
	m_setTrapType = 0;
	
	return CCLayer::onExit();
}

void BattleLayer::fight()
{
	if(m_curTile->getType() == MapTile::End)
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Result_Lose);
		return;
	}
	
	//check if in guard
	int x = m_curTile->getXCoord();
	int y = m_curTile->getYCoord();
	checkGuardBuff(x-1,y-1);
	checkGuardBuff(x-1, y);
	checkGuardBuff(x-1, y+1);
	
	checkGuardBuff(x,y-1);
	checkGuardBuff(x,y);
	checkGuardBuff(x, y+1);
	
	checkGuardBuff(x+1,y-1);
	checkGuardBuff(x+1, y);
	checkGuardBuff(x+1, y+1);
	
	//check current tile
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
		case MapTile::Trap1:
		{
			MapTile* nextTile = m_terrain->getTileByID(m_curTile->getNextTile());
			m_enemySprite->runAction(CCSequence::create(CCDelayTime::create(c_trapDelayTime), CCMoveTo::create(1.0, nextTile->getPosition()),callback,NULL));
			m_curTile = nextTile;
			
			m_effectLabel->setString("尖刺陷阱, HP - 30%");
			m_effectLabel->runAction(CCSequence::create(CCShow::create(), CCDelayTime::create(c_trapDelayTime), CCHide::create(), NULL));
			
			m_enemycards[m_curEnemy]->buffHP(-0.3);
		}
			break;
		case MapTile::Trap2:
		{
			MapTile* nextTile = m_terrain->getTileByID(m_curTile->getNextTile());
			m_enemySprite->runAction(CCSequence::create(CCDelayTime::create(c_trapDelayTime), CCMoveTo::create(1.0, nextTile->getPosition()),callback,NULL));
			m_curTile = nextTile;
			
			m_effectLabel->setString("烈火陷阱, HP - 20%");
			m_effectLabel->runAction(CCSequence::create(CCShow::create(), CCDelayTime::create(c_trapDelayTime), CCHide::create(), NULL));
			m_enemycards[m_curEnemy]->buffHP(-0.2);
			m_preventEnemyBuff += 2;
		}
			break;
		default:
		{
			MapTile* nextTile = m_terrain->getTileByID(m_curTile->getNextTile());
			m_enemySprite->runAction(CCSequence::create(CCMoveTo::create(1.0, nextTile->getPosition()),callback,NULL));
			m_curTile = nextTile;
			
			if(m_preventEnemyBuff<=0)
				m_enemycards[m_curEnemy]->buffHP(0.2);
			else
			{
				m_preventEnemyBuff--;
			}
		}
			break;
	}
}

bool BattleLayer::checkGuardBuff(int x, int y)
{
	MapTile* tile = m_terrain->getTileByCoordinate(x, y);
	if(!tile)
		return false;
	
	if(tile->getMark() == MapTile::Guard1)
	{
		m_preventEnemyBuff++;
		m_enemycards[m_curEnemy]->buffHP(-0.1);
		MapTile::TileMark mark = m_curTile->getMark();
		if(mark == MapTile::Card1 || mark == MapTile::Card2 || mark == MapTile::Card3)
		{
			m_herocards[m_curTile->getMark()]->buffAtk(0.1);
		}
		
		m_guardLabel->setString("攻击守卫");
		m_guardLabel->runAction(CCSequence::create(CCShow::create(), CCDelayTime::create(c_trapDelayTime), CCHide::create(), NULL));
		
		
		return true;
	}
	
	if(tile->getMark() == MapTile::Guard2)
	{
		m_preventEnemyBuff++;
		MapTile::TileMark mark = m_curTile->getMark();
		if(mark == MapTile::Card1 || mark == MapTile::Card2 || mark == MapTile::Card3)
		{
			m_herocards[m_curTile->getMark()]->buffDef(0.1);
			m_herocards[m_curTile->getMark()]->buffHP(0.3);
		}
		
		m_guardLabel->setString("守护守卫");
		m_guardLabel->runAction(CCSequence::create(CCShow::create(), CCDelayTime::create(c_trapDelayTime), CCHide::create(), NULL));
		
		
		return true;
	}
	
	return true;
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

bool BattleLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void BattleLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint touchLocation = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	
	if(m_terrain && m_terrain->isVisible())
	{
		int hit = m_terrain->isHit(touchLocation);
		if(hit != -1)
		{
			if(m_setTrapType != 0) //select card
			{
				m_terrain->markCurTile((MapTile::TileMark)(m_setTrapType+2));
				m_setTrapType = 0;
				m_setTrapLayer->resetCurSel();
			}
		}
	}
		
	m_setTrapType = m_setTrapLayer->isHit(touchLocation);
}
