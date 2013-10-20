//
//  Skill.h
//  CombatDemo
//
//  Created by Hao Chen on 10/10/13.
//
//

#ifndef __CombatDemo__Skill__
#define __CombatDemo__Skill__
 
#include <iostream>
#include <map>

class Card;
class Skill
{
public:
	Skill() {}
	~Skill() {}
	
	int m_id;
	std::string m_name;
	int m_cooldown;
	int m_targetType;
	int m_targetNumber;

	
	std::string m_effectType;
	std::string m_effectValue;
	
	int m_skillType;
	std::string m_condition;
};

class SkillConfig
{
public:
	static SkillConfig* getInstance()
	{
		static SkillConfig s_config;
		return &s_config;
	}
	
	~SkillConfig();
	
	void readConfig();
	
	Skill* getSkillByID(int ID);

	//TODO: analyze skill calculate formula
	int calHurt(int skillID, Card* card, Card* opcard);
private:
	SkillConfig();
	std::map<int, Skill*> m_skillMap;
};

#endif /* defined(__CombatDemo__Skill__) */
