//
//  Combat.h
//  CombatDemo
//
//  Created by Hao Chen on 10/6/13.
//
//

#ifndef __CombatDemo__Combat__
#define __CombatDemo__Combat__

#include <iostream>
#include <vector>
#include <list>
#include "Card.h"

class Combat
{
public:
	Combat();
	~Combat();

	enum ActionType
	{
		NormalAttack,
		Dead,
	};

	struct CombatAction
	{
		Card* card1;
		ActionType type;
		
		std::list<std::pair<Card*, int>> resultlist;
	};
	typedef std::list<CombatAction*> CombatActionList;

	const CombatActionList& runCombat(CardDeck* carddeck1, CardDeck* carddeck2);

	int getResult();
private:
	Card* findOpponent(Card* card);
	void singleRound(Card* card);

private:
	typedef std::map<Card*, int> CardGroup;
	CardGroup m_cardgroup1;
	CardGroup m_cardgroup2;

	std::list<Card*> m_attackQueue;

	CombatActionList m_actionlist;
};

#endif /* defined(__CombatDemo__Combat__) */
