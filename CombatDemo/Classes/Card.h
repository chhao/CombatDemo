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
	:m_level(0)
	,m_HP(-1)
	,m_atkRatio(1.0)
	,m_defRatio(1.0)
	{
	}
	
	~Card()
	{
		
	}
	
	static std::string getImageNameByID(int ID);
	
	int getDmg()
	{
		return (m_bdmg + m_level*m_udmg)*m_atkRatio;
	}
	
	int getHP()
	{
		return m_HP;
	}
	
	int getMaxHP()
	{
		return m_bhp + m_level * m_uhp;
	}
	
	int getDef()
	{
		return (m_bdef + m_level*m_udef)*m_defRatio;
	}
	
	int getMDef()
	{
		return (m_bmdf + m_level * m_umdf)*m_defRatio;
	}
	
	void buffHP(float buff)  //0~1, percentage of max hp
	{
		int maxHP = getMaxHP();
		int newHP = m_HP + maxHP * buff;
		m_HP = newHP > maxHP ? maxHP : newHP;
	}
	
	void buffAtk(float buff)
	{
		m_atkRatio *= (1+buff);
	}
	
	void buffDef(float buff)
	{
		m_defRatio *= (1+buff);
	}
	
	Card* clone()
	{
		Card* card = new Card;
		
		card->m_bdef = m_bdef;
		card->m_bdmg = m_bdmg;
		card->m_bexp = m_bexp;
		card->m_bhp = m_bhp;
		card->m_bmdf = m_bmdf;
		card->m_class = m_class;
		card->m_crp = m_crp;
		card->m_crt = m_crt;
		card->m_desc = m_desc;
		card->m_egold = m_egold;
		card->m_evolve = m_evolve;
		card->m_hit = m_hit;
		card->m_id = m_id;
		card->m_lc = m_lc;
		card->m_miss = m_miss;
		card->m_name = m_name;
		card->m_nature = m_nature;
		card->m_quality = m_quality;
		card->m_skilla = m_skilla;
		card->m_skillb = m_skillb;
		card->m_skilln = m_skilln;
		card->m_skillp = m_skillp;
		card->m_sp = m_sp;
		card->m_star = m_star;
		card->m_udef = m_udef;
		card->m_udmg = m_udmg;
		card->m_uexp = m_uexp;
		card->m_uhp = m_uhp;
		card->m_uid = m_uid;
		card->m_umdf = m_umdf;
		card->m_usp = m_usp;
		card->m_vo = m_vo;
		
		card->m_level = m_level;
		card->m_HP = m_HP;
		card->m_atkRatio = m_atkRatio;
		card->m_defRatio = m_defRatio;
		
		return card;
	}
public:
	int m_level;
	int m_HP;
	float m_atkRatio;
	float m_defRatio;
	
	float m_bdef;
	int m_bdmg;
	int m_bexp;
	int m_bhp;
	float m_bmdf;
	int m_class;
	float m_crp;
	float m_crt;
	std::string m_desc;
	int m_egold;
	int m_evolve;
	int m_hit;
	int m_id;
	int m_lc;
	float m_miss;
	std::string m_name;
	int m_nature;
	int m_quality;
	int m_skilla;
	int m_skillb;
	int m_skilln;
	int m_skillp;
	int m_sp;
	int m_star;
	float m_udef;
	int m_udmg;
	int m_uexp;
	int m_uhp;
	std::string m_uid;
	float m_umdf;
	float m_usp;
	std::string m_vo;
	
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
	
	void buffHP(float buff);  //0~1, percentage of max hp
	
	void buffAtk(float buff);
	void buffDef(float buff);
	
	float getHPPercentage();
	
	bool isDead();
private:
	Card* m_cards[6];
};
typedef std::vector<CardDeck*> CardDeckVector;

#endif /* defined(__CombatDemo__Card__) */
