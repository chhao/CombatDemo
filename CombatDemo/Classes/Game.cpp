//
//  Game.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#include "Game.h"
#include "GameScene.h"
#include "HelperUtil.h"
#include <assert.h>

using namespace cocos2d;

Game::Game()
:m_world(-1)
,m_level(-1)
{
	init();
}

Game::~Game()
{
	
}

void Game::init()
{
	CSJson::Value root;
	readJsonFile("heroCardGroup.json", root);
	
	assert(root.size() == 3);
	for (int i = 0; i < root.size(); i++)
	{
		CSJson::Value value = root[i];
		for (int j = 0; j < value.size(); j++)
		{
			int cardid = value[j].asInt();
			m_cardgroup[i].push_back(CardConfig::getInstance()->createCardByID(cardid));
		}
	}
}

void Game::setCurrentLevel(int level)
{
	m_level = level;
}

int Game::getCurrentLevel()
{
	return m_level;
	
}

void Game::setCurrentWorld(int world)
{
	m_world = world;
}

int Game::getCurrentWorld()
{
	return m_world;
}

GameScene* Game::getGameScene()
{
	return (GameScene*)CCDirector::sharedDirector()->getRunningScene();
}

const CardVector& Game::getCardGroup(int i)
{
	return m_cardgroup[i];
}
