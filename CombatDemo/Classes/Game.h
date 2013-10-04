//
//  Game.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__Game__
#define __CombatDemo__Game__

#include <iostream>

class GameScene;
class Game
{
public:
	static Game* getInstance()
	{
		static Game s_game;
		return &s_game;
	}
	
	~Game();
	
	void setCurrentWorld(int world);
	int getCurrentWorld();
	
	void setCurrentLevel(int level);
	int getCurrentLevel();
	
	GameScene* getGameScene();
private:
	Game();
	
	int m_world;
	int m_level;
};

#endif /* defined(__CombatDemo__Game__) */
