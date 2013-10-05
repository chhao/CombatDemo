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
#include "ListViewLayer.h"

class MagicGuard : public ListViewItem
{
public:
	CREATE_FUNC(MagicGuard);
	
	MagicGuard();
	~MagicGuard();
	
	bool init();
	
	bool isHit(cocos2d::CCPoint pt);
	
	void setSelected(bool select);
	bool getSelected();
	
	enum ItemTag
	{
		CheckBox = 2,
		Label = 1,
	};
	
private:
	cocos2d::CCSprite* m_checkBox;
	cocos2d::CCLabelTTF* m_label;
	bool m_select;
};

class CardGroup : public cocos2d::CCNode
{
public:
	CREATE_FUNC(CardGroup);
	
	CardGroup();
	~CardGroup();
	
	bool init();
	
	bool isHit(cocos2d::CCPoint pt);
	
	void setSelected(bool select);
	bool getSelected();

	enum ItemTag
	{
		CheckBox = 2,
		Card1 = 3,
		Card2 = 4,
		Card3 = 5,
		Card4 = 6,
		Card5 = 7,
	};

private:
	cocos2d::CCSprite* m_card[5];
	cocos2d::CCSprite* m_checkBox;
	bool m_select;
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
	
	void updateCardGroup(bool show);
	void updateMagicGuard(bool show);
	
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
	CardGroup* m_cardGroup[3];
	
	MagicGuard* m_magicGuard[8];
	ListViewLayer* m_listviewLayer;
	
	cocos2d::CCSprite* m_btnCancle;
	cocos2d::CCSprite* m_btnOK;
	cocos2d::CCSprite* m_tabCardGroup;
	cocos2d::CCSprite* m_tabTrap;
	cocos2d::CCSprite* m_tile;
	cocos2d::CCLabelTTF* m_label;
};

#endif /* defined(__CombatDemo__SelectCardGroup__) */
