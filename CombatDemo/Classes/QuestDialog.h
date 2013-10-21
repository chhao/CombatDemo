//
//  QuestDialog.h
//  CombatDemo
//
//  Created by Hao Chen on 10/20/13.
//
//

#ifndef __CombatDemo__QuestDialog__
#define __CombatDemo__QuestDialog__

#include <iostream>
#include "cocos2d.h"
#include "Card.h"

class QuestDialog : public cocos2d::CCLayerColor
{
public:
	CREATE_FUNC(QuestDialog);
	
	QuestDialog();
	~QuestDialog();
	
	bool init();
	
	void onEnter();
	void onExit();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
private:
	void readEnemyCards();
	
	enum ItemTag
	{
		ItemBtnOK = 0,
		ItemCard1 = 1,
		ItemCard2 = 2,
		ItemCard3 = 3,
		ItemCard4 = 4,
		ItemLabel1 = 5,
		ItemLabel2 = 6,
		ItemLabel3 = 7,
	};
	
	cocos2d::CCSprite* m_card[4];
	cocos2d::CCSprite* m_btnOK;
};


#endif /* defined(__CombatDemo__QuestDialog__) */
