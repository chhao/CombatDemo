//
//  Game.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#include "Game.h"
#include "GameScene.h"

using namespace cocos2d;

Game::Game()
:m_world(-1)
,m_level(-1)
{
	
}

Game::~Game()
{
	
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