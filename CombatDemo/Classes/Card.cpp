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
#include <iomanip>

using namespace cocos2d;

std::string Card::getImageNameByID(int ID)
{
	std::stringstream ss;
	ss << "cards/" << std::setfill('0') << std::setw(4) << ID << ".png";
	return ss.str();
}

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

		card->m_bdef = value["bdef"].asFloat();
		card->m_bdmg = value["bdmg"].asInt();
		card->m_bexp = value["bexp"].asInt();
		card->m_bhp = value["bhp"].asInt();
		card->m_bmdf = value["bmdf"].asFloat();
		card->m_class = value["class"].asInt();
		card->m_crp = value["crp"].asFloat();
		card->m_crt = value["crt"].asFloat();
		card->m_desc = value["desc"].asString();
		card->m_egold = value["egold"].asInt();
		card->m_evolve = value["evolve"].asInt();
		card->m_hit = value["hit"].asInt();
		card->m_id = value["id"].asInt();
		card->m_lc = value["lc"].asInt();
		card->m_miss = value["miss"].asFloat();
		card->m_name = value["name"].asString();
		card->m_nature = value["nature"].asInt();
		card->m_quality = value["quality"].asInt();
		card->m_skilla = value["skilla"].asInt();
		card->m_skillb = value["skillb"].asInt();
		card->m_skilln = value["skilln"].asInt();
		card->m_skillp = value["skillp"].asInt();
		card->m_sp = value["sp"].asInt();
		card->m_star = value["star"].asInt();
		card->m_udef = value["udef"].asInt();
		card->m_udmg = value["udmg"].asInt();
		card->m_uexp = value["uexp"].asInt();
		card->m_uhp = value["uhp"].asInt();
		card->m_uid = value["uid"].asString();
		card->m_umdf = value["umdf"].asFloat();
		card->m_usp = value["usp"].asFloat();
		card->m_vo = value["vo"].asString();
		
		card->m_HP = card->m_bhp + card->m_level * card->m_uhp;
		
		m_cardMap.insert(std::make_pair(card->m_id, card));
	}

}

Card* CardConfig::createCardByID(int id)
{
	auto itr = m_cardMap.find(id);
	if(itr != m_cardMap.end())
	{
		return itr->second->clone();
	}
	
	return NULL;
}


CardDeck::CardDeck()
{
	
}

CardDeck::~CardDeck()
{
	for (int i = 0; i < 6; i++)
	{
		if(m_cards[i])
			delete m_cards[i];
	}
}

CardDeck* CardDeck::createCardDeck(CSJson::Value &deckvalue)
{
	CardDeck* deck = new CardDeck;
	
	for (int i = 0; i < deckvalue.size(); i++)
	{
		if(deckvalue[i] == 0)
		{
			deck->m_cards[i] = NULL;
		}
		else
		{
			deck->m_cards[i] = CardConfig::getInstance()->createCardByID(deckvalue[i].asInt());
		}
	}
	
	return deck;
}

CardDeck* CardDeck::clone()
{
	CardDeck* deck = new CardDeck;
	
	for (int i = 0; i < 6; i++)
	{
		if(m_cards[i])
		{
			deck->m_cards[i] = m_cards[i]->clone();
		}
	}
	
	return deck;
}

Card* CardDeck::getCardByIndex(int iIndex)
{
	assert(iIndex >= 0 && iIndex < 6);
	return m_cards[iIndex];
}

void CardDeck::buffHP(float buff)
{
	for (int i = 0; i < 6; i++)
	{
		if(m_cards[i])
		{
			m_cards[i]->buffHP(buff);
		}
	}
}