//
//  Card.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/5/13.
//
//

#include "Card.h"
#include "json_lib.h"
#include "cocos2d.h"
#include "HelperUtil.h"
#include <sstream>

using namespace cocos2d;

CardConfig::CardConfig()
{
	readConfig();
}

CardConfig::~CardConfig()
{
	for (auto itr = m_cardMap.begin(); itr != m_cardMap.end(); ++itr)
	{
		delete itr->second;
	}
}

void CardConfig::readConfig()
{
	CSJson::Value root;
	readJsonFile("cardConfig.json", root);
		
	for (int i = 0; i < root.size(); i++)
	{
		CSJson::Value value = root[i];
		Card* card = new Card;
		card->m_id = value["id"].asInt();
		card->m_name = value["name"].asString();
		card->m_quality = value["quality"].asInt();
		card->m_star = value["star"].asInt();
		card->m_nature = value["nature"].asInt();
		card->m_bexp = value["bexp"].asInt();
		card->m_egold = value["egold"].asInt();
		card->m_uhp = value["uhp"].asInt();
		card->m_bdmg = value["bdmg"].asInt();
		card->m_udmg = value["udmg"].asInt();
		card->m_evolve = value["evolve"].asInt();
		card->m_sp = value["sp"].asInt();
		card->m_usp = value["usp"].asInt();
		
		m_cardMap.insert(std::make_pair(card->m_id, card));
	}

}

Card* CardConfig::createCardByID(int id)
{
	auto itr = m_cardMap.find(id);
	if(itr != m_cardMap.end())
	{
		Card* card = new Card;
		card->clone(itr->second);
		return card;
	}
	
	return NULL;
}