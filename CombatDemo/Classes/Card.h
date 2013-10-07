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
#include <list>
#include "json_lib.h"

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
	
	Card* clone()
	{
		Card* card = new Card;
		card->m_id = m_id;
		card->m_name = m_name;
		card->m_quality = m_quality;
		card->m_nature = m_nature;
		card->m_bexp = m_bexp;
		card->m_uexp = m_uexp;
		card->m_egold = m_egold;
		card->m_uhp = m_uhp;
		card->m_bdmg = m_bdmg;
		card->m_udmg = m_udmg;
		card->m_evolve = m_evolve;
		card->m_star = m_star;
		card->m_sp = m_sp;
		card->m_usp = m_usp;
		card->m_bhp = m_bhp;
		
		return card;
	}
};
typedef std::vector<Card*> CardVector;
typedef std::list<Card*> CardList;

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


class CardDeck
{
public:
	CardDeck();
	~CardDeck();
	
	static CardDeck* createCardDeck(CSJson::Value& deckvalue);
	CardDeck* clone();
	
	Card* getCardByIndex(int iIndex);
private:
	Card* m_cards[6];
};
typedef std::vector<CardDeck*> CardDeckVector;

#endif /* defined(__CombatDemo__Card__) */
