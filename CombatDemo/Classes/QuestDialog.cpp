//
//  QuestDialog.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/20/13.
//
//

#include "QuestDialog.h"
#include "HelperUtil.h"
#include "Game.h"
#include "Card.h"

using namespace cocos2d;

QuestDialog::QuestDialog()
{
	
}

QuestDialog::~QuestDialog()
{
	
}

bool QuestDialog::init()
{
	if(!CCLayerColor::init())
		return false;
	
	setColor(ccc3(0,0,0));
	setOpacity(150);
	
	readLayout(this, "QuestDialog.json");
	
	m_btnOK = (CCSprite*)getChildByTag(ItemBtnOK);
	for (int i = 0; i < 4; i++)
	{
		m_card[i] = (CCSprite*)getChildByTag(i+ItemCard1);
	}
	
	return true;
}

void QuestDialog::readEnemyCards()
{
	std::stringstream ss;
	ss << "cardGroup_map" << Game::getInstance()->getCurrentWorld() << ".json";
	
	CSJson::Value root;
	readJsonFile(ss.str(), root);
	
	int level = Game::getInstance()->getCurrentLevel();
	CSJson::Value levelvalue = root[level];

	std::set<int> cardset;
	for (int i = 0; i < levelvalue.size(); i++)
	{
		CSJson::Value cards = levelvalue[i];
		for (int j = 0; j < cards.size(); j++)
		{
			int cardID = cards[j].asInt();
			if(cardID != 0 && cardset.find(cardID) == cardset.end())
			{
				int index = cardset.size();
				if(index < 4)
				{
					m_card[index]->setTexture(CCTextureCache::sharedTextureCache()->addImage(Card::getImageNameByID(cardID).c_str()));
					cardset.insert(cardID);
				}
			}
		}
	}
}


void QuestDialog::onEnter()
{
	setTouchEnabled(true);
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	
	readEnemyCards();
	
	return CCLayer::onEnter();
}

void QuestDialog::onExit()
{
	return CCLayer::onExit();
}

bool QuestDialog::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void QuestDialog::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(isHit(m_btnOK, pTouch))
	{
		removeFromParent();
		return;
	}
}