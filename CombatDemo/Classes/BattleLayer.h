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
#include "SetTrapLayer.h"

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

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	void readEnemyCards();
	void copyHeroCards();
	
	void fight();
	void cardBattleWin();
	void cardBattleLose();
	
	bool checkGuardBuff(int x,int y);
	
	bool isEnemyLive();
	void updateEnemyHpBar();
	void nextEnemyGroup();
private:
	TerrainMap* m_terrain;
	CardDeck* m_enemycards[3];
	CardDeck* m_herocards[3];
	
	int m_curEnemy;
	MapTile* m_curTile;
	cocos2d::CCLabelTTF* m_label;
	cocos2d::CCLabelTTF* m_effectLabel;
	cocos2d::CCLabelTTF* m_guardLabel;
	cocos2d::CCSprite* m_enemySprite;
	CardBattleLayer* m_cardbattleLayer;
	
	SetTrapLayer* m_setTrapLayer;
	int m_setTrapType;
	int m_preventEnemyBuff;
	
	bool m_bPause;
	cocos2d::CCSprite* m_pauseSprite;
};


#endif /* defined(__CombatDemo__BattleLayer__) */
