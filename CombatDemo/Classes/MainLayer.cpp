//
//  MainLayer.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/4/13.
//
//

#include "MainLayer.h"
#include "HelperUtil.h"
#include "Game.h"
#include "HelloWorldScene.h"
#include <sstream>

using namespace cocos2d;

AdventureItem::AdventureItem()
{
	
}

AdventureItem::~AdventureItem()
{
	
}

bool AdventureItem::init()
{
	if(!ListViewItem::init())
	{
		return false;
	}
	
	readLayout(this, "ListItem.json", ccp(-281, -52));
	
	m_enterSprite = (CCSprite*)getChildByTag(AdventureItem::Enter);
	
	return true;
}

void AdventureItem::setInfo(const std::string &description, int ID)
{
	((CCLabelTTF*)getChildByTag(AdventureItem::Name))->setString(description.c_str());
	m_ID = ID;
}

int AdventureItem::getID()
{
	return m_ID;
}

bool AdventureItem::isHit(const cocos2d::CCPoint &pt)
{
	if(::isHit(m_enterSprite->getQuad(),m_enterSprite->convertToNodeSpace(pt)))
	{
		return true;
	}
	
	return false;
}

/////////////////////////////
MainLayer::MainLayer()
:m_listview(NULL)
{
	
}

MainLayer::~MainLayer()
{
	
}

bool MainLayer::init()
{
	if(!CCLayer::init())
		return false;
	
	readLayout(this, "MainLayer.json");
	
	m_AdventureSprite = (CCSprite*)getChildByTag(MainLayer::AdventureSprite);
	m_backSprite = (CCSprite*)getChildByTag(MainLayer::BackSprite);
	
	updateListView();
	
	return true;
}

void MainLayer::onEnter()
{
	setTouchEnabled(true);
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	
	return CCLayer::onEnter();
}

bool MainLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_touchPt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	
	return true;
}

void MainLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint touchLocation = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	
	if(isHit(m_backSprite->getQuad(), m_backSprite->convertToNodeSpace(touchLocation)))
	{
		Game::getInstance()->setCurrentWorld(-1);
		Game::getInstance()->setCurrentLevel(-1);
		updateListView();
		return;
	}
	
	if(fabs(touchLocation.x - m_touchPt.x) > 10 || fabs(touchLocation.y - m_touchPt.y) > 10)
		return;
	
	CCRect listviewRect = m_listview->getListViewRect();
	if(!isHit(listviewRect, touchLocation))  //touchLocation not in list
		return;
	
	for (ItemList::iterator itr = m_itemlist.begin(); itr != m_itemlist.end(); ++itr)
	{
		if((*itr)->isHit(touchLocation))
		{
			Game* game = Game::getInstance();
			if(game->getCurrentWorld() == -1)
				game->setCurrentWorld((*itr)->getID());
			else
			{
				game->setCurrentLevel((*itr)->getID());
				Game::getInstance()->getGameScene()->setActiveLayer(GameScene::Layer_PreBattle);
			}
			
			updateListView();
			return;
		}
	}
}

void MainLayer::updateListView()
{
	if(m_listview)
	{
		m_listview->removeFromParent();
		m_listview = NULL;
		m_itemlist.clear();
	}
	
	//init items
	CCSize itemsize = CCSizeMake(566, 102);
	m_listview = ListViewLayer::create();
	
	m_listview->setListViewRect(CCRectMake(38, 150,itemsize.width,itemsize.height * 1.05 * 5));
	m_listview->setScrollDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_listview->setItemContent(itemsize.width,itemsize.height,1,5);
	
	addChild(m_listview);

	int world = Game::getInstance()->getCurrentWorld();
	if (world == -1)
	{
		m_backSprite->setVisible(false);

		AdventureItem* item = AdventureItem::create();
		item->setInfo("魔法森林", 0);
		m_listview->addItem(item);
		m_itemlist.push_back(item);

		item = AdventureItem::create();
		item->setInfo("烈焰沙漠", 1);
		m_listview->addItem(item);
		m_itemlist.push_back(item);

	}
	else if(world == 0)
	{
		m_backSprite->setVisible(true);
		for (int i = 0; i < 6; i++)
		{
			AdventureItem* item = AdventureItem::create();
			std::stringstream ss;
			ss << "魔法森林-" << i;
			item->setInfo(ss.str(), i);
			m_listview->addItem(item);
			m_itemlist.push_back(item);
		}		
	}
	else if(world == 1)
	{
		m_backSprite->setVisible(true);
		for (int i = 0; i < 3; i++)
		{
			AdventureItem* item = AdventureItem::create();
			std::stringstream ss;
			ss << "烈焰沙漠-" << i;
			item->setInfo(ss.str(), i);
			m_listview->addItem(item);
			m_itemlist.push_back(item);
		}
	}
}
