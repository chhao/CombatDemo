//
//  PrepareBattleLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__PrepareBattleLayer__
#define __CombatDemo__PrepareBattleLayer__

#include <iostream>
#include "cocos2d.h"
#include "Tile.h"
#include "SelectCardGroup.h"

class PrepareBattleLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(PrepareBattleLayer);
	
	PrepareBattleLayer();
	~PrepareBattleLayer();

	bool init();
	
	void onEnter();
	void onExit();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	TerrainMap* getTerrain();
private:
	void updateTerrain();
	
	enum PageType
	{
		Terrain = 1,
		SelectCard = 2,
	};
	
	void ShowPage(PageType type);
private:
	enum ItemTag
	{
		Back = 0,
		Start = 1,
	};

	cocos2d::CCSprite* m_backSprite;
	cocos2d::CCSprite* m_startSprite;
	TerrainMap* m_terrain;
	SelectBackGround* m_selectGroup;
};

#endif /* defined(__CombatDemo__PrepareBattleLayer__) */
