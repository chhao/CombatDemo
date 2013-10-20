//
//  Skill.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/10/13.
//
//

#include "Skill.h"
#include "HelperUtil.h"
#include "Card.h"

SkillConfig::SkillConfig()
{
	readConfig();
}

SkillConfig::~SkillConfig()
{
	
}

void SkillConfig::readConfig()
{
	CSJson::Value root;
	readJsonFile("skill.json", root);
	
	for (int i = 0; i < root.size(); i++)
	{
		CSJson::Value value = root[i];
		Skill* skill = new Skill;
		
		skill->m_id = value["id"].asInt();
		skill->m_cooldown = value["CD"].asInt();
		skill->m_name = value["name"].asString();
		skill->m_targetType = value["TargetValue"].asInt();
		skill->m_targetNumber = value["TargetNumber"].asInt();
		
		skill->m_effectType = value["EffectType"].asString();
		skill->m_effectValue = value["EffectValue"].asString();
		
		m_skillMap.insert(std::make_pair(skill->m_id, skill));
	}
}

Skill* SkillConfig::getSkillByID(int ID)
{
	auto itr = m_skillMap.find(ID);
	if(itr != m_skillMap.end())
		return itr->second;
	
	return NULL;
}

int SkillConfig::calHurt(int skillID, Card* card, Card* opcard)
{
	switch (skillID)
	{
		case 1:
		{
			return -(card->getDmg() - opcard->getDef());
		}
		case 2:
		{
			return -(card->getDmg() - opcard->getDef())*1.5;
		}
		case 3:
		{
			return -(card->getDmg() - opcard->getMDef());
		}
		case 4:
		{
			return -(card->getDmg() - opcard->getMDef()) * 1.5;
		}
		case 5:
		{
			return -(card->getDmg() - opcard->getDef())*0.6;
		}
		case 6:
		{
			return -(card->getDmg() - opcard->getDef()) * 0.8;
		}
		case 7:
		{
			return -(card->getDmg() - opcard->getDef());
		}
		case 8:
		{
			return -(card->getDmg() - opcard->getDef());
		}
		case 9:
		{
			return -(card->getDmg() - opcard->getDef() * 2);
		}
		case 10:
		{
			return card->getDmg();
		}
		case 11:
		{
			return card->getDmg()*1.4;
		}
		case 12:
		{
			return card->getDmg();
		}
		case 13:
		{
			return -(card->getDmg() - opcard->getDef());
		}
		case 14:
		{
			return -(card->getDmg() - opcard->getDef()) * 1.3;
		}
		case 15:
		{
			return -(card->getDmg() - opcard->getDef()) * 1.7;
		}
		case 16:
		{
			return -(card->getDmg() - opcard->getMDef());
		}
		case 17:
		{
			return 0;
		}
		case 18:
		{
			return -(card->getDmg() - opcard->getDef())*0.6;
		}
		case 19:
		{
			return -(card->getDmg() - opcard->getMDef());
		}
		case 20:
		{
			return -(card->getDmg() - opcard->getMDef());
		}
		default:
			return -(card->getDmg() - opcard->getDef());
	}
}

