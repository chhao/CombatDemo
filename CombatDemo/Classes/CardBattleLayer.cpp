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


using namespace cocos2d;

const float c_attack = 0.4;
const float c_defense = 0.4;

CardSprite* CardSprite::createByID(int ID)
{
	CardSprite* sprite = new CardSprite;
	if(sprite->initWithFile(Card::getImageNameByID(ID).c_str()))
	{
		sprite->autorelease();
		sprite->setScale(1.5);
		
		CCSprite* hpbg = CCSprite::create("hpbar_bg.png");
		hpbg->setScale(0.8);
		CCProgressTimer* hpbar = CCProgressTimer::create(CCSprite::create("hpbar_fore.png"));
		hpbar->setScale(0.8);
		hpbg->setPosition(ccp(50,100));
		hpbar->setPosition(ccp(50,100));
		hpbar->setType(kCCProgressTimerTypeBar);
		hpbar->setBarChangeRate(ccp(1,0));
		hpbar->setPercentage(100);
		hpbar->setMidpoint(CCPointZero);
		sprite->addChild(hpbg);
		sprite->addChild(hpbar);
		sprite->m_hpbar = hpbar;
		
		return sprite;
	}
	
	delete sprite;
	return NULL;
}
void CardSprite::setCardInfo(int hp, int maxhp, int dmg, int def, int mdef)
{
	addChild(addCardInfo("HP:", hp, ccp(80,80), 0));
	addChild(addCardInfo("DMG:", dmg, ccp(80,60)));
	addChild(addCardInfo("DEF:", def, ccp(80,40)));
	addChild(addCardInfo("MDEF:", mdef, ccp(80,20)));
	m_HP = hp;
	m_maxHP = maxhp;
	
	updateHPLabel();
}

void CardSprite::updateHP(int deltaHp)
{
	m_HP += deltaHp;
	
	runAction(CCSequence::create(CCDelayTime::create(c_attack+c_defense*0.3), CCCallFunc::create(this, callfunc_selector( CardSprite::updateHPLabel)),NULL));
}
void CardSprite::updateHPLabel()
{
	CCLabelTTF* label = (CCLabelTTF*)getChildByTag(0);
	std::stringstream ss;
	ss << "HP: " << m_HP;
	label->setString(ss.str().c_str());
	
	m_hpbar->setPercentage(float(m_HP*100)/m_maxHP);
}

CCNode* CardSprite::addCardInfo(const std::string &info, int num, cocos2d::CCPoint pos, int tag)
{
	std::stringstream ss;
	ss << info << " " << num;
	CCLabelTTF* label = CCLabelTTF::create(ss.str().c_str(), "", 15);
	label->setPosition(pos);
	label->setTag(tag);
	return label;
}


CardBattleLayer::CardBattleLayer()
:m_finishcallback(NULL)
,m_skillName(NULL)
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
	
	if(card->getHP() < 0)
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
		
	sprite->setCardInfo(card->getHP(), card->getMaxHP(), card->getDmg(), card->getDef(), card->getMDef());
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
	
		BattleEvent* event = new BattleEvent(m_cardmap[card1], m_cardmap[card2], action->type, hit, action->description);
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
	
	m_skillName = CCLabelTTF::create("", "", 42);
	m_skillName->setPosition(ccp(320,480));
	m_skillName->setVisible(false);
	addChild(m_skillName, 5);
	
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

		}
			break;
		case Combat::Dead:
		{
			event->m_card1->runAction(CCSequence::create(CCScaleTo::create(c_attack*0.5, 1.2*1.5), CCScaleTo::create(c_attack*0.5, 1.0*1.5),NULL));
			event->m_card2->runAction(CCSequence::create(CCDelayTime::create(c_attack),CCScaleTo::create(c_defense*0.5, 0.8*1.5), CCScaleTo::create(c_defense*0.5, 1.0*1.5), CCHide::create() ,callback,NULL));
		}
			break;
	}
	
	m_attackEffect->setPosition(event->m_card2->getPosition());
	m_label->setPosition(event->m_card2->getPosition());
	
	m_attackEffect->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCShow::create(), CCScaleTo::create(c_defense*0.3, 1.2), CCScaleTo::create(c_defense*0.3, 1.0),CCHide::create(),NULL));
	
	std::stringstream ss;
	ss << event->m_number;
	m_label->setString(ss.str().c_str());
	m_label->runAction(CCSequence::create(CCDelayTime::create(c_attack), CCShow::create(), CCMoveBy::create(c_defense, ccp(0, -60)), CCHide::create(),NULL));
	
	m_skillName->setString(event->m_skill.c_str());
	m_skillName->runAction(CCSequence::create(CCShow::create(), CCDelayTime::create(1.5), CCHide::create(),NULL));
	
	//update card info
	event->m_card2->updateHP(event->m_number);
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