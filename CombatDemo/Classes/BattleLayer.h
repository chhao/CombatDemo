//
//  BattleLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__BattleLayer__
#define __CombatDemo__BattleLayer__

#include <iostream>
#include "cocos2d.h"
#include "Card.h"

class CardSprite : public cocos2d::CCSprite
{
public:
	static CardSprite* createByID(int ID);
};

class BattleEvent
{
public:
	enum EventType
	{
		NormalAttack = 1,
		Dead = 2,
	};
	
	BattleEvent(CardSprite* card1, CardSprite* card2, EventType type, std::string discription = "")
	:m_type(type)
	,m_discription(discription)
	,m_card1(card1)
	,m_card2(card2)
	{
		
	}
	
	EventType m_type;
	std::string m_discription;
	CardSprite* m_card1;
	CardSprite* m_card2;
};

typedef std::list<BattleEvent*> BattleEventList;

class BattleLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(BattleLayer);
	
	BattleLayer();
	~BattleLayer();
	
	bool init();
	
	void onEnter();

	void setCardGroup(const std::vector<Card*>& card1, const std::vector<Card*>& card2);

	void clearEvents();
	void excuteEvents();
	void nextEvent();

private:
	
	void getAttackQueue();
	
	void caculate();
	
	void createSprite(Card* card, int i, bool bOnBottom);
	
private:
	typedef std::map<Card*, int> CardGroup;
	typedef std::map<Card*, CardSprite*> CardSpriteMap;
	CardGroup m_cardgroup1;
	CardGroup m_cardgroup2;
	CardSpriteMap m_cardmap;
	
	cocos2d::CCSprite* m_attackEffect;
	cocos2d::CCLabelTTF* m_label;
	
	BattleEventList m_eventlist;
};


#endif /* defined(__CombatDemo__BattleLayer__) */
