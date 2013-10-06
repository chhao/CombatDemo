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
#include "Combat.h"

class CardSprite : public cocos2d::CCSprite
{
public:
	static CardSprite* createByID(int ID);
};

class BattleEvent
{
public:
	BattleEvent(CardSprite* card1, CardSprite* card2, Combat::ActionType type, std::string discription = "")
	:m_type(type)
	,m_discription(discription)
	,m_card1(card1)
	,m_card2(card2)
	{
		
	}
	
	Combat::ActionType m_type;
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
	void onExit();

	void setCardGroup(const std::vector<Card*>& card1, const std::vector<Card*>& card2);

	void clearEvents();
	void excuteEvents();
	void nextEvent();

private:
	void createSprite(Card* card, int i, bool bOnBottom);
	
private:
	typedef std::map<Card*, CardSprite*> CardSpriteMap;
	CardSpriteMap m_cardmap;
	
	cocos2d::CCSprite* m_attackEffect;
	cocos2d::CCLabelTTF* m_label;
	
	BattleEventList m_eventlist;
};


#endif /* defined(__CombatDemo__BattleLayer__) */
