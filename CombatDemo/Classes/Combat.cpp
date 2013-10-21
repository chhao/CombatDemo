//
//  Combat.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/6/13.
//
//

#include "Combat.h"
#include "Skill.h"
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

const Combat::CombatActionList& Combat::runCombat(CardDeck* carddeck1, CardDeck* carddeck2)
{
	m_cardgroup1.clear();
	m_cardgroup2.clear();
	m_attackQueue.clear();
	
	for (int i = 0; i < 6; i++)
	{
		Card* card = carddeck1->getCardByIndex(i);
		if (card && card->getHP() > 0)
		{
			m_cardgroup1.insert(std::make_pair(card, i));
			m_attackQueue.push_back(card);
		}
		
		card = carddeck2->getCardByIndex(i);
		if (card && card->getHP() > 0)
		{
			m_cardgroup2.insert(std::make_pair(card, i));
			m_attackQueue.push_back(card);
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
	Skill* skill = SkillConfig::getInstance()->getSkillByID(card->m_skilln);
	Card* opcard = findOpponent(card,skill->m_targetType);
	assert(opcard);
	
	int dmg = SkillConfig::getInstance()->calHurt(skill->m_id, card, opcard);
	opcard->m_HP += dmg;
	
	if(opcard->m_HP <= 0)
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
		action->description = skill->m_name;
		action->resultlist.push_back(std::make_pair(opcard, dmg));
		action->type = Combat::Dead;
		m_actionlist.push_back(action);
	}
	else
	{
		CombatAction* action = new CombatAction;
		action->card1 = card;
		action->description = skill->m_name;
		action->resultlist.push_back(std::make_pair(opcard, dmg));
		action->type = Combat::NormalAttack;
		m_actionlist.push_back(action);
	}
}

Card* Combat::findOpponent(Card* card, int targetType)
{
	if( m_cardgroup1.find(card) != m_cardgroup1.end() )  //in group1
	{
		if(targetType == 7)
		{
			for (auto itr = m_cardgroup1.begin(); itr != m_cardgroup1.end(); ++itr)
			{
				Card* opcard = itr->first;
				if(opcard->m_bhp > 0)
					return opcard;
			}
		}
		
		for (auto itr = m_cardgroup2.begin(); itr != m_cardgroup2.end(); ++itr)
		{
			Card* opcard = itr->first;
			if(opcard->m_bhp > 0)
				return opcard;
		}
	}
	else  //in group2
	{
		if(targetType == 7)
		{
			for (auto itr = m_cardgroup2.begin(); itr != m_cardgroup2.end(); ++itr)
			{
				Card* opcard = itr->first;
				if(opcard->m_bhp > 0)
					return opcard;
			}
		}
		
		for (auto itr = m_cardgroup1.begin(); itr != m_cardgroup1.end(); ++itr)
		{
			Card* opcard = itr->first;
			if(opcard->m_bhp > 0)
				return opcard;
		}
	}
	
	return NULL;
}

int Combat::getResult()
{
	if(m_cardgroup1.empty())
		return 2;
	else
		return 1;
}


