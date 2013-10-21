//
//  ListViewLayer.cpp
//
//  Created by Hao Chen on 6/6/13.
//
//

#include "ListViewLayer.h"

using namespace cocos2d;
using namespace cocos2d::extension;

//TODO: only maintain 3 pages: prePage, curPage, postPage

ListViewLayer::ListViewLayer()
:m_curPage(0)
,m_widthCount(3)
,m_heightCount(3)
,m_direction(kCCScrollViewDirectionVertical)
,m_scrollCallback(NULL)
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	m_pScrollView = CCScrollView::create(winsize);
	m_pScrollView->setContentOffset(CCPointZero);
	m_pScrollView->setTouchEnabled(true);
	m_pScrollView->setDelegate(this);
	m_pScrollView->setDirection(m_direction);
	
	this->addChild(m_pScrollView);
}

ListViewLayer::~ListViewLayer()
{
	
}

bool ListViewLayer::init()
{
	if(!CCNode::init())
		return false;
	
//	setColor(ccc3(255,255,255));
//	setOpacity(200);
	
	return true;
}

void ListViewLayer::scrollViewDidScroll(cocos2d::extension::CCScrollView *view)
{
	if(m_scrollCallback)
	{
		m_scrollCallback->execute();
	}
}

void ListViewLayer::scrollViewDidZoom(cocos2d::extension::CCScrollView *view)
{
    CCLOG("zoom");
}

void ListViewLayer::setItemContent(int width, int height, int widthnum, int heightnum)
{
	m_itemWidth = width;
	m_itemHeight = height;
	
	m_widthCount = widthnum;
	m_heightCount = heightnum;
	
	if(m_direction == kCCScrollViewDirectionVertical)
	{
		CCSize size = m_pScrollView->getViewSize();
		m_widthMargin = (float)(size.width - width * widthnum) / (widthnum + 1);
		m_heightMargin = (float)(size.height - height * heightnum) / heightnum;
	}
	else
	{
		CCSize size = m_pScrollView->getViewSize();
		m_widthMargin = (float)(size.width - width * widthnum) / (widthnum);
		m_heightMargin = (float)(size.height - height * heightnum) / (heightnum + 1);
	}
}

void ListViewLayer::addItem(ListViewItem *item)
{
	m_itemlist.push_back(item);
    addItemToScrollView(item);
}

void ListViewLayer::addItemToScrollView(ListViewItem *item) {
	m_pScrollView->addChild(item);
	
	//calculate the position of item
	int size = m_itemlist.size();
	int page = (float)(size-1)/(float)(m_widthCount * m_heightCount);
	CCSize viewsize = m_pScrollView->getViewSize();
	if(m_direction == kCCScrollViewDirectionVertical)
	{
		int maxPage = m_pScrollView->getContentSize().height / viewsize.height;
		if(page+1 > maxPage)
		{
			CCSize size = CCSizeMake(viewsize.width, viewsize.height * (page+1));
			m_pScrollView->setContentSize(size);
			
			CCArray* children = m_pScrollView->getContainer()->getChildren();
			for (int i = 0; i < children->count(); i++)
			{
				CCNode* node = (CCNode*)children->objectAtIndex(i);
				node->setPosition(ccpAdd(node->getPosition(), ccp(0, viewsize.height)));
			}
			
			m_pScrollView->setContentOffset(ccp(0, -page*viewsize.height));
		}
		
		int indexInPage = size - page * m_widthCount * m_heightCount;
		int yIndex = (float)(indexInPage - 1) / m_widthCount;
		int xIndex = indexInPage - 1 - yIndex * m_widthCount;
		int x = xIndex * m_itemWidth + xIndex * m_widthMargin + m_itemWidth * 0.5;
		int y = viewsize.height - yIndex * m_itemHeight - (yIndex +1) * m_heightMargin - m_itemHeight * 0.5;
		item->setPosition(ccp(x,y));
	}
	else
	{
		int maxPage = m_pScrollView->getContentSize().width / viewsize.width;
		if(page+1 > maxPage)
		{
			m_pScrollView->setContentSize(CCSizeMake(viewsize.width * (page+1), viewsize.height));
		}
		
		int indexInPage = size - page * m_widthCount * m_heightCount;
		int yIndex = (float)(indexInPage - 1) / m_widthCount;
		int xIndex = indexInPage - 1 - yIndex * m_widthCount;
		int x = viewsize.width * page + xIndex * m_itemWidth + xIndex * m_widthMargin + m_itemWidth * 0.5;
		int y = viewsize.height - yIndex * m_itemHeight - (yIndex +1) * m_heightMargin - m_itemHeight * 0.5;
		item->setPosition(ccp(x,y));

	}
}

void ListViewLayer::setScrollDirection(CCScrollViewDirection dir)
{
	m_direction = dir;
	m_pScrollView->setDirection(dir);
}

void ListViewLayer::setListViewRect(const CCRect &rect)
{
	m_listViewRect = rect;
	m_pScrollView->setPosition(rect.origin);
	m_pScrollView->setViewSize(rect.size);
	m_pScrollView->setContentSize(CCSizeMake(rect.size.width, rect.size.height));
}

void ListViewLayer::setScrollCallback(cocos2d::CCCallFunc *callback)
{
	CC_SAFE_RELEASE_NULL(m_scrollCallback);
	if (callback)
	{
		m_scrollCallback = callback;
		m_scrollCallback->retain();
	}
}

bool ListViewLayer::isScroll()
{
	return m_pScrollView->isTouchMoved();
}

const cocos2d::CCRect& ListViewLayer::getListViewRect()
{
	return m_listViewRect;
}