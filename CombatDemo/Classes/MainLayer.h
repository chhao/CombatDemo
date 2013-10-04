//
//  MainLayer.h
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#ifndef __CombatDemo__MainLayer__
#define __CombatDemo__MainLayer__

#include <iostream>
#include "cocos2d.h"
#include "ListViewLayer.h"

class AdventureItem : public ListViewItem
{
public:
	CREATE_FUNC(AdventureItem);
	
	AdventureItem();
	~AdventureItem();
	
	bool init();
	
	bool isHit(const cocos2d::CCPoint& pt);
	
	void setInfo(const std::string& description, int ID);

	int getID();
private:
	enum ItemTag
	{
		Name = 0,
		Enter = 1,
	};
	
	cocos2d::CCSprite* m_enterSprite;
	int m_ID;
};
typedef std::list<AdventureItem*> ItemList;

class MainLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(MainLayer);
	
	MainLayer();
	~MainLayer();
	
	bool init();
	
	void onEnter();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
private:
	void updateListView();
	
private:
	enum Tag
	{
		BackSprite = 1,
		AdventureSprite = 0,
	};
	
	cocos2d::CCSprite* m_backSprite;
	cocos2d::CCSprite* m_AdventureSprite;
	ListViewLayer* m_listview;
	
	ItemList m_itemlist;
	cocos2d::CCPoint m_touchPt;
};

#endif /* defined(__CombatDemo__MainLayer__) */
