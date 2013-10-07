//
//  CardBattleLayer.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/7/13.
//
//

#include "CardBattleLayer.h"
#include "HelperUtil.h"
#include "Game.h"
#include "GameScene.h"
#include "Combat.h"
#include <sstream>
#include <iomanip>

using namespace cocos2d;

const float c_attack = 0.4;
const float c_defense = 0.4;

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

CardBattleLayer::CardBattleLayer()
:m_finishcallback(NULL)
{
	
}

CardBattleLayer::~CardBattleLayer()
{
	
}

bool CardBattleLayer::init()
{
	if(!CCLayerColor::init())
		return false;
	
	setColor(ccc3(0,0,0));
	setOpacity(255);
	
	return true;
}

void CardBattleLayer::createSprite(Card *card, int i, bool bOnBottom)
{
	if(card == NULL)
		return;
	
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

int CardBattleLayer::setCardGroup(CardDeck* carddeck1, CardDeck* carddeck2)
{
	Combat* combat = new Combat;
	
	for (int i = 0; i < 6; i++)
	{
		createSprite(carddeck1->getCardByIndex(i), i, true);
		createSprite(carddeck2->getCardByIndex(i), i, false);
	}
	
	const Combat::CombatActionList& combatlist = combat->runCombat(carddeck1, carddeck2);
	for (auto itr = combatlist.begin(); itr != combatlist.end(); ++itr)
	{
		//TODO
		Combat::CombatAction* action = *itr;
		Card* card1 = action->card1;
		Card* card2 = action->resultlist.begin()->first;
		int hit = action->resultlist.begin()->second;
		
		std::stringstream ss;
		ss << hit;
		
		BattleEvent* event = new BattleEvent(m_cardmap[card1], m_cardmap[card2], action->type, ss.str());
		m_eventlist.push_back(event);
	}
	
	int result = combat->getResult();
	
	delete combat;
	
	return result;
}

void CardBattleLayer::onEnter()
{	
	m_attackEffect = CCSprite::create("effect_attack.png");
	addChild(m_attackEffect, 5);
	m_attackEffect->setVisible(false);
	
	m_label = CCLabelTTF::create("-15", "", 32);
	m_label->setColor(ccc3(255,0,0));
	m_label->setVisible(false);
	addChild(m_label, 5);
	
	excuteEvents();
	return CCLayer::onEnter();
}

void CardBattleLayer::onExit()
{
	removeAllChildren();
	
	m_cardmap.clear();
	
	return CCLayer::onExit();
}

void CardBattleLayer::excuteEvents()
{
	if(m_eventlist.empty())
		return;
	
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(CardBattleLayer::nextEvent));
	BattleEvent* event = *m_eventlist.begin();
	
	switch (event->m_type)
	{
		case Combat::NormalAttack:
		{
			event->m_card1->runAction(CCSequence::create(CCScaleTo::create(c_attack*0.5, 1.2*1.5), CCScaleTo::create(c_attack*0.5, 1.0*1.5),NULL));
			event->m_card2->runAction(CCSequence::create(CCDelayTime::create(c_attack),CCScaleTo::create(c_defense*0.5, 0.8*1.5), CCScaleTo::create(c_defense*0.5, 1.0*1.5),callback,NULL));
			
			m_attackEffect->setPosition(event->m_card2->getPosition());
			m_label->setPosition(event->m_card2->getPosition());
			
			m_attackEffect->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCShow::create(), CCScaleTo::create(c_defense*0.3, 1.2), CCScaleTo::create(c_defense*0.3, 1.0),CCHide::create(),NULL));
			
			m_label->setString(event->m_discription.c_str());
			m_label->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCShow::create(), CCMoveBy::create(c_defense, ccp(0, -60)), CCHide::create(),NULL));
		}
			break;
		case Combat::Dead:
		{
			event->m_card1->runAction(CCSequence::create(CCScaleTo::create(c_attack*0.5, 1.2*1.5), CCScaleTo::create(c_attack*0.5, 1.0*1.5),NULL));
			event->m_card2->runAction(CCSequence::create(CCDelayTime::create(c_attack),CCScaleTo::create(c_defense*0.5, 0.8*1.5), CCScaleTo::create(c_defense*0.5, 1.0*1.5), CCHide::create() ,callback,NULL));
			
			m_attackEffect->setPosition(event->m_card2->getPosition());
			m_label->setPosition(event->m_card2->getPosition());
			
			m_attackEffect->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCShow::create(), CCScaleTo::create(c_defense*0.3, 1.2), CCScaleTo::create(c_defense*0.3, 1.0),CCHide::create(),NULL));
			
			m_label->setString(event->m_discription.c_str());
			m_label->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCShow::create(), CCMoveBy::create(c_defense, ccp(0, -60)), CCHide::create(),NULL));
		}
			break;
	}
}

void CardBattleLayer::nextEvent()
{
	if(m_eventlist.empty())
	{
		if(m_finishcallback)
			m_finishcallback->execute();

		return;
	}
	
	assert(!m_eventlist.empty());
	m_eventlist.pop_front();
	
	if(m_eventlist.empty())
	{
		if(m_finishcallback)
			m_finishcallback->execute();
		
		return;
	}
	
	excuteEvents();
}

void CardBattleLayer::clearEvents()
{
	for (auto itr = m_eventlist.begin(); itr != m_eventlist.end(); ++itr)
	{
		delete (*itr);
	}
	m_eventlist.clear();
}

void CardBattleLayer::setBattleFinishCallback(cocos2d::CCCallFunc *callback)
{
	CC_SAFE_RELEASE_NULL(m_finishcallback);
	if(callback)
	{
		m_finishcallback = callback;
		m_finishcallback->retain();
	}
}