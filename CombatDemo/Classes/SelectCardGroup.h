//
//  SelectCardGroup.h
//  CombatDemo
//
//  Created by Hao Chen on 10/5/13.
//
//

#ifndef __CombatDemo__SelectCardGroup__
#define __CombatDemo__SelectCardGroup__

#include <iostream>
#include "cocos2d.h"
#include "Tile.h"

class SelectCardGroup : public cocos2d::CCNode
{
public:
	CREATE_FUNC(SelectCardGroup);
	
	SelectCardGroup();
	~SelectCardGroup();
	
	bool init();
	
	int isHit(cocos2d::CCPoint pt);

	enum ItemTag
	{
		Card1 = 1,
		Card2 = 2,
		Card3 = 3,
	};
};

class SelectBackGround : public cocos2d::CCNode
{
public:
	CREATE_FUNC(SelectBackGround);
	
	SelectBackGround();
	~SelectBackGround();
	
	bool init();
	
	int isHit(cocos2d::CCPoint pt);
	
	void setTab(int tab);
	
	void setInfo(int tiletype);
	
	enum ItemTag
	{
		TileType = 0,
		DescriptionLabel = 1,
		TabCardGroup = 2,
		TabTrap = 3,
		BtnCancel = 4,
		BtnOK = 5,
	};
	
private:
	SelectCardGroup* m_cardGroup;
	cocos2d::CCSprite* m_btnCancle;
	cocos2d::CCSprite* m_btnOK;
	cocos2d::CCSprite* m_tabCardGroup;
	cocos2d::CCSprite* m_tabTrap;
	cocos2d::CCSprite* m_tile;
	cocos2d::CCLabelTTF* m_label;
};

#endif /* defined(__CombatDemo__SelectCardGroup__) */
