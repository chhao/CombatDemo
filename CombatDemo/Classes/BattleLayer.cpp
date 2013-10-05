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
#include <sstream>
#include <iomanip>

using namespace cocos2d;

CardSprite* CardSprite::createByID(int ID)
{
	std::stringstream ss;
	ss << "cards/" << std::setfill('0') << std::setw(4) << ID << ".png";
	
	CardSprite* sprite = new CardSprite;
	if(sprite->initWithFile(ss.str().c_str()))
	{
		sprite->autorelease();
		sprite->setScale(1.5);
		return sprite;
	}

	delete sprite;
	return NULL;
}

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
	
	m_attackEffect = CCSprite::create("effect_attack.png");
	addChild(m_attackEffect, 5);
	m_attackEffect->setVisible(false);
	
	m_label = CCLabelTTF::create("-15", "", 32);
	m_label->setColor(ccc3(255,0,0));
	m_label->setVisible(false);
	addChild(m_label, 5);
	
	std::vector<Card *> card1, card2;
	for (int i = 1; i < 7; i++)
	{
		card1.push_back(CardConfig::getInstance()->getCardByID(i));
		card2.push_back(CardConfig::getInstance()->getCardByID(i + 10));
	}
	
	setCardGroup(card1, card2);
	caculate();
	
	return true;
}

void BattleLayer::onEnter()
{
//	runAction(CCSequence::create(CCDelayTime::create(2.0),CCCallFunc::create(this, callfunc_selector(BattleLayer::battleEnd)),NULL));
	
	excuteEvents();
	return CCLayer::onEnter();
}

const float c_attack = 0.4;
const float c_defense = 0.4;

void BattleLayer::excuteEvents()
{
	if(m_eventlist.empty())
		return;
	
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(BattleLayer::nextEvent));
	BattleEvent* event = *m_eventlist.begin();
	
	switch (event->m_type)
	{
		case BattleEvent::NormalAttack:
		{
			event->m_card1->runAction(CCSequence::create(CCScaleTo::create(c_attack*0.5, 1.2*1.5), CCScaleTo::create(c_attack*0.5, 1.0*1.5),NULL));
			event->m_card2->runAction(CCSequence::create(CCDelayTime::create(c_attack),CCScaleTo::create(c_defense*0.5, 0.8*1.5), CCScaleTo::create(c_defense*0.5, 1.0*1.5),callback,NULL));

			m_attackEffect->setPosition(event->m_card2->getPosition());
			m_label->setPosition(event->m_card2->getPosition());
			
			m_attackEffect->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCShow::create(), CCScaleTo::create(c_defense*0.3, 1.2*1.5), CCScaleTo::create(c_defense*0.3, 1.0*1.5),CCHide::create(),NULL));
			
			m_label->setString(event->m_discription.c_str());
			m_label->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCShow::create(), CCMoveBy::create(c_defense*0.3, ccp(0, -50)), CCHide::create(),NULL));
		}
			break;
		case BattleEvent::Dead:
		{
			event->m_card1->runAction(CCSequence::create(CCScaleTo::create(1.2, c_attack*0.5), CCScaleTo::create(1.0, c_attack*0.5),NULL));
			event->m_card2->runAction(CCSequence::create(CCDelayTime::create(c_attack),CCScaleTo::create(0.8, c_defense*0.5), CCScaleTo::create(1.0, c_defense*0.5),CCHide::create(), callback, NULL));
			
			m_attackEffect->setPosition(event->m_card2->getPosition());
			m_label->setPosition(event->m_card2->getPosition());
			
			m_attackEffect->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCScaleTo::create(1.2, c_defense*0.2), CCScaleTo::create(1.0, c_defense*0.2), CCShow::create(),CCHide::create(),NULL));
			
			m_label->setString(event->m_discription.c_str());
			m_label->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCMoveBy::create(1.2, ccp(0, 100)), CCShow::create(),CCHide::create(),NULL));
		}
			break;
	}
}

void BattleLayer::nextEvent()
{
	if(m_eventlist.empty())
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Result);
		return;
	}
	
	assert(!m_eventlist.empty());
	m_eventlist.pop_front();
	
	if(m_eventlist.empty())
	{
		Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_Result);
		return;
	}
	
	excuteEvents();
}

void BattleLayer::clearEvents()
{
	for (auto itr = m_eventlist.begin(); itr != m_eventlist.end(); ++itr)
	{
		delete (*itr);
	}
	m_eventlist.clear();
}

void BattleLayer::createSprite(Card *card, int i, bool bOnBottom)
{
	CardSprite* sprite = CardSprite::createByID(card->m_id);
	if(bOnBottom)
	{
		int row = i / 3;
		sprite->setPositionX( 120 + (i%3) * 180 );
		sprite->setPositionY(100 + row * 180);
	}
	else
	{
		int row = i / 3;
		sprite->setPositionX( 120 + (i%3) * 180 );
		sprite->setPositionY(960 - 100 - row * 180);
	}
	addChild(sprite);
	m_cardmap.insert(std::make_pair(card, sprite));
}

void BattleLayer::setCardGroup(const std::vector<Card *> &card1, const std::vector<Card *> &card2 )
{
	m_cardgroup1.clear();
	m_cardgroup2.clear();
	
	for (int i = 0; i < 6; i++)
	{
		if (card1[i])
		{
			m_cardgroup1.insert(std::make_pair(card1[i], i));
			createSprite(card1[i], i, true);
		}
		if (card2[i])
		{
			m_cardgroup2.insert(std::make_pair(card2[i], i));
			createSprite(card2[i], i, false);
		}
	}
	
	caculate();
}

void BattleLayer::caculate()
{
	
	m_eventlist.push_back(new BattleEvent(m_cardmap[m_cardgroup1.begin()->first], m_cardmap[m_cardgroup2.begin()->first], BattleEvent::NormalAttack, "-15"));
	m_eventlist.push_back(new BattleEvent(m_cardmap[m_cardgroup2.begin()->first], m_cardmap[m_cardgroup1.begin()->first], BattleEvent::NormalAttack, "-30"));
}


