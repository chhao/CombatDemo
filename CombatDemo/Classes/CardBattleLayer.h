//
//  CardBattleLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/7/13.
//
//

#ifndef __CombatDemo__CardBattleLayer__
#define __CombatDemo__CardBattleLayer__

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

class CardBattleLayer : public cocos2d::CCLayerColor
{
public:
	CREATE_FUNC(CardBattleLayer);
	
	CardBattleLayer();
	~CardBattleLayer();
	
	bool init();
	
	void onEnter();
	void onExit();
	
	int setCardGroup(const std::vector<Card*>& card1, const std::vector<Card*>& card2);
	
	void clearEvents();
	void excuteEvents();
	void nextEvent();
	
	void setBattleFinishCallback(cocos2d::CCCallFunc* callback);
private:
	void createSprite(Card* card, int i, bool bOnBottom);
	
private:
	typedef std::map<Card*, CardSprite*> CardSpriteMap;
	CardSpriteMap m_cardmap;
	
	cocos2d::CCSprite* m_attackEffect;
	cocos2d::CCLabelTTF* m_label;
	
	BattleEventList m_eventlist;
	cocos2d::CCCallFunc* m_finishcallback;
};


#endif /* defined(__CombatDemo__CardBattleLayer__) */
