//
//  Card.h
//  CombatDemo
//
//  Created by Hao Chen on 10/5/13.
//
//

#ifndef __CombatDemo__Card__
#define __CombatDemo__Card__

#include <iostream>
#include <map>
#include <vector>

class Card
{
public:
	Card()
	{
	}
	~Card()
	{
		
	}
	int m_id;
	std::string m_name;
	int m_quality;
	int m_nature;
	int m_bexp;
	int m_uexp;
	int m_egold;
	int m_uhp;
	int m_bdmg;
	int m_udmg;
	int m_evolve;
	int m_star;
	int m_sp;
	int m_usp;
	int m_bhp;
	
	void clone(Card* card)
	{
		m_id = card->m_id;
		m_name = card->m_name;
		m_quality = card->m_quality;
		m_nature = card->m_nature;
		m_bexp = card->m_bexp;
		m_uexp = card->m_uexp;
		m_egold = card->m_egold;
		m_uhp = card->m_uhp;
		m_bdmg = card->m_bdmg;
		m_udmg = card->m_udmg;
		m_evolve = card->m_evolve;
		m_star = card->m_star;
		m_sp = card->m_sp;
		m_usp = card->m_usp;
		m_bhp = card->m_bhp;
	}
};
typedef std::vector<Card*> CardVector;

class CardConfig
{
public:
	static CardConfig* getInstance()
	{
		static CardConfig s_config;
		return &s_config;
	}
	
	~CardConfig();
	
	void readConfig();
	
	Card* createCardByID(int ID);
private:
	CardConfig();
	
	std::map<int, Card*> m_cardMap;
};

#endif /* defined(__CombatDemo__Card__) */
