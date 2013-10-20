//
//  SetTrapLayer.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/20/13.
//
//

#include "SetTrapLayer.h"
#include "HelperUtil.h"

using namespace cocos2d;

SetTrapLayer::SetTrapLayer()
:m_curSel(NULL)
{
	
}

SetTrapLayer::~SetTrapLayer()
{
	
}

bool SetTrapLayer::init()
{
	if(!CCNode::init())
		return false;
	
	readLayout(this, "SetTrapAndGuard.json");
	
	m_trapSpint = (CCSprite*)getChildByTag(ItemTrapSpint);
	m_trapFire = (CCSprite*)getChildByTag(ItemTrapFire);
	m_guardAttack = (CCSprite*)getChildByTag(ItemGuardAttack);
	m_guardDefense = (CCSprite*)getChildByTag(ItemGuardDefense);
	
	return true;
}

cocos2d::CCSprite* SetTrapLayer::getHitSprite(cocos2d::CCPoint pt)
{
	if(::isHit(m_trapSpint->getQuad(), m_trapSpint->convertToNodeSpace(pt)))
		return m_trapSpint;
	
	if(::isHit(m_trapFire->getQuad(), m_trapFire->convertToNodeSpace(pt)))
		return m_trapFire;
	
	if(::isHit(m_guardAttack->getQuad(), m_guardAttack->convertToNodeSpace(pt)))
		return m_guardAttack;
	
	if(::isHit(m_guardDefense->getQuad(), m_guardDefense->convertToNodeSpace(pt)))
		return m_guardDefense;
	
	return NULL;
}

int SetTrapLayer::isHit(cocos2d::CCPoint pt)
{
	CCSprite* hitSprite = getHitSprite(pt);
	if(hitSprite)
	{
		if(hitSprite == m_curSel)
		{
			m_curSel->setColor(ccc3(255,255,255));
			m_curSel = NULL;
		}
		else
		{
			if(m_curSel)
				m_curSel->setColor(ccc3(255,255,255));
			
			m_curSel = hitSprite;
			
			if(m_curSel)
				m_curSel->setColor(ccc3(255,0,0));
		}
	}
	
	
	if(m_curSel == NULL)
		return NULL;
	
	return m_curSel->getTag();
}

void SetTrapLayer::resetCurSel()
{
	if(m_curSel)
		m_curSel->setColor(ccc3(255,255,255));
	
	m_curSel = NULL;
}