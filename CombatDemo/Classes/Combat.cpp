//
//  Combat.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/6/13.
//
//

#include "Combat.h"
#include <algorithm>
#include <assert.h>

Combat::Combat()
{
	
}

Combat::~Combat()
{
	for (auto itr = m_actionlist.begin(); itr != m_actionlist.end(); ++itr)
	{
		delete (*itr);
	}
}


bool cmp(Card* card1, Card* card2)
{
	return card1->m_sp > card2->m_sp;
}

const Combat::CombatActionList& Combat::runCombat(const std::vector<Card*>& card1, const std::vector<Card*>& card2)
{
	m_cardgroup1.clear();
	m_cardgroup2.clear();
	m_attackQueue.clear();
	
	for (int i = 0; i < 6; i++)
	{
		if (card1[i])
		{
			m_cardgroup1.insert(std::make_pair(card1[i], i));
			m_attackQueue.push_back(card1[i]);
		}
		if (card2[i])
		{
			m_cardgroup2.insert(std::make_pair(card2[i], i));
			m_attackQueue.push_back(card2[i]);
		}
	}
	
	m_attackQueue.sort(cmp);

	auto itr = m_attackQueue.begin();
	while (true)
	{
		Card* card = *itr;
		
		singleRound(card);
		
		if(m_cardgroup1.empty() || m_cardgroup2.empty())
			break;
		
		++itr;
		if(itr == m_attackQueue.end())
		{
			itr = m_attackQueue.begin();
		}
	}

	
	return m_actionlist;
}

void Combat::singleRound(Card *card)
{
	Card* opcard = findOpponent(card);
	assert(opcard);
	
	opcard->m_bhp -= card->m_bdmg;
	
	if(opcard->m_bhp < 0)
	{
		m_attackQueue.erase(std::find(m_attackQueue.begin(), m_attackQueue.end(), opcard));
		auto itr = m_cardgroup1.find(opcard);
		if(itr != m_cardgroup1.end())
			m_cardgroup1.erase(itr);
		
		itr = m_cardgroup2.find(opcard);
		if(itr != m_cardgroup2.end())
			m_cardgroup2.erase(itr);
		
		CombatAction* action = new CombatAction;
		action->card1 = card;
		action->resultlist.push_back(std::make_pair(opcard, -card->m_bdmg));
		action->type = Combat::Dead;
		m_actionlist.push_back(action);
	}
	else
	{
		CombatAction* action = new CombatAction;
		action->card1 = card;
		action->resultlist.push_back(std::make_pair(opcard, -card->m_bdmg));
		action->type = Combat::NormalAttack;
		m_actionlist.push_back(action);
	}
}

Card* Combat::findOpponent(Card* card)
{
	if( m_cardgroup1.find(card) != m_cardgroup1.end() )  //in group1
	{
		for (auto itr = m_cardgroup2.begin(); itr != m_cardgroup2.end(); ++itr)
		{
			Card* opcard = itr->first;
			if(opcard->m_bhp > 0)
				return opcard;
		}
	}
	else  //in group2
	{
		for (auto itr = m_cardgroup1.begin(); itr != m_cardgroup1.end(); ++itr)
		{
			Card* opcard = itr->first;
			if(opcard->m_bhp > 0)
				return opcard;
		}
	}
	
	return NULL;
}




