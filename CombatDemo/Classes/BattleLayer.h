//
//  BattleLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__BattleLayer__
#define __CombatDemo__BattleLayer__

#include <iostream>
#include "cocos2d.h"
#include "CardBattleLayer.h"
#include "Tile.h"
#include "Card.h"

class BattleLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(BattleLayer);
	
	BattleLayer();
	~BattleLayer();
	
	bool init();
	
	void onEnter();
	void onExit();
	
	void copyTerrainTile(TerrainMap* terrain);

private:
	void readEnemyCards();
	void copyHeroCards();
	
	void fight();
	void cardBattleWin();
	void cardBattleLose();
	
private:
	TerrainMap* m_terrain;
	CardVector m_enemycards[3];
	CardVector m_herocards[3];
	
	int m_curEnemy;
	MapTile* m_curTile;
	cocos2d::CCLabelTTF* m_label;
	cocos2d::CCSprite* m_enemySprite;
	CardBattleLayer* m_cardbattleLayer;
};


#endif /* defined(__CombatDemo__BattleLayer__) */
