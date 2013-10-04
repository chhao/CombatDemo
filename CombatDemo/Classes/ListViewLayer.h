//
//  ListViewLayer.h
//  FairyTales
//
//  Created by Hao Chen on 6/6/13.
//
//

#ifndef __FairyTales__ListViewLayer__
#define __FairyTales__ListViewLayer__

#include <iostream>
#include "cocos2d.h"
#include "CCScrollView.h"
#include <functional>

class ListViewItem : public cocos2d::CCNode
{
public:
	ListViewItem() { }
	virtual ~ListViewItem() { }
};

typedef std::vector<ListViewItem*> ListViewItemList;

class ListViewLayer : public cocos2d::CCNode ,public cocos2d::extension::CCScrollViewDelegate
{
public:
	CREATE_FUNC(ListViewLayer);
	ListViewLayer();
	~ListViewLayer();
	
    virtual bool init();

public:
	void setListViewRect(const cocos2d::CCRect& rect);
	const cocos2d::CCRect& getListViewRect();
	void setItemContent(int width, int height, int widthnum, int heightnum);
	void addItem(ListViewItem* item);
	void setScrollDirection(cocos2d::extension::CCScrollViewDirection dir);
    void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
	
	void setScrollCallback(cocos2d::CCCallFunc* callback);
	bool isScroll();
	
    ListViewItemList & getItemList() { return m_itemlist; }
private:
    void addItemToScrollView(ListViewItem *item);
	void adjustScrollView(float offset);
	cocos2d::extension::CCScrollView *m_pScrollView;
	cocos2d::CCPoint m_touchPoint;
	int m_curPage;
	int m_itemWidth;
	int m_itemHeight;
	ListViewItemList m_itemlist;
	
	int m_widthCount;
	int m_heightCount;
	cocos2d::extension::CCScrollViewDirection m_direction;
	
	float m_widthMargin, m_heightMargin;
	
	cocos2d::CCCallFunc* m_scrollCallback;
	
	cocos2d::CCRect m_listViewRect;
};


#endif /* defined(__FairyTales__ListViewLayer__) */
