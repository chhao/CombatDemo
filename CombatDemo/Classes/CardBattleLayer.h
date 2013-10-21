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
	void setCardInfo(int hp, int dmg, int def, int mdef);
	void updateHP(int deltaHp);

private:
	cocos2d::CCNode* addCardInfo(const std::string& info, int num, cocos2d::CCPoint pos, int tag = -1);
	void updateHPLabel();
private:
	int m_HP;
	int m_maxHP;
	cocos2d::CCProgressTimer* m_hpbar;
};

class BattleEvent
{
public:
	BattleEvent(CardSprite* card1, CardSprite* card2, Combat::ActionType type, int number, const std::string& skill = "")
	:m_type(type)
	,m_number(number)
	,m_skill(skill)
	,m_card1(card1)
	,m_card2(card2)
	{
		
	}
	
	Combat::ActionType m_type;
	int m_number;
	std::string m_skill;
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
	
	int setCardGroup(CardDeck* card1, CardDeck* card2);
	
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

	cocos2d::CCLabelTTF* m_skillName;
	
	BattleEventList m_eventlist;
	cocos2d::CCCallFunc* m_finishcallback;
};


#endif /* defined(__CombatDemo__CardBattleLayer__) */
