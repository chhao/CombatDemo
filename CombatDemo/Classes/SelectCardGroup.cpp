//
//  SelectCardGroup.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/5/13.
//
//

#include "SelectCardGroup.h"
#include "HelperUtil.h"

using namespace cocos2d;

MagicGuard::MagicGuard()
{
	
}

MagicGuard::~MagicGuard()
{
	
}

bool MagicGuard::init()
{
	if(!CCNode::init())
		return false;
	
	readLayout(this, "SelectGuard.json", ccp(-626*0.5*0.98, -139*0.5*0.98));
	m_checkBox = (CCSprite*)getChildByTag(MagicGuard::CheckBox);
	m_label = (CCLabelTTF*)getChildByTag(MagicGuard::Label);
	
	return true;
}

bool MagicGuard::getSelected()
{
	return m_select;
}

void MagicGuard::setSelected(bool select)
{
	m_select = select;
}

bool MagicGuard::isHit(cocos2d::CCPoint pt)
{
	if(::isHit(m_checkBox->getQuad(), m_checkBox->convertToNodeSpace(pt)))
	{
		m_select = !m_select;
		if(m_select)
			m_checkBox->setTexture(CCTextureCache::sharedTextureCache()->addImage("chk_2.png"));
		else
			m_checkBox->setTexture(CCTextureCache::sharedTextureCache()->addImage("chk_1.png"));
		
		return true;
	}
	
	return false;
}
///////////////////////////////////
CardGroup::CardGroup()
{
	
}

CardGroup::~CardGroup()
{
	
}

bool CardGroup::init()
{
	if(!CCNode::init())
		return false;
	
	readLayout(this, "SelectCardGroup.json", ccp(-626*0.5*0.98, -139*0.5*0.98));
	for (int i = 0; i < 5; i++)
	{
		m_card[i] = (CCSprite*)getChildByTag(i+3);
	}
	m_checkBox = (CCSprite*)getChildByTag(CardGroup::CheckBox);
	
	return true;
}

bool CardGroup::isHit(cocos2d::CCPoint pt)
{
	if(::isHit(m_checkBox->getQuad(), m_checkBox->convertToNodeSpace(pt)))
	{
		m_select = !m_select;
		if(m_select)
			m_checkBox->setTexture(CCTextureCache::sharedTextureCache()->addImage("chk_2.png"));
		else
			m_checkBox->setTexture(CCTextureCache::sharedTextureCache()->addImage("chk_1.png"));
		
		return true;
	}
	
	return false;
}

bool CardGroup::getSelected()
{
	return m_select;
}

void CardGroup::setSelected(bool select)
{
	m_select = select;
}


///////////////////////////////////////////
SelectBackGround::SelectBackGround()
:m_listviewLayer(NULL)
{
	
}

SelectBackGround::~SelectBackGround()
{
	
}

bool SelectBackGround::init()
{
	if(!CCNode::init())
		return false;
	
	readLayout(this, "SelectBackgroud.json");
	
	CCPoint basePt = ccp(320, 550);
	for(int i = 0; i<3; i++)
	{
		m_cardGroup[i] = CardGroup::create();
		m_cardGroup[i]->setPosition(ccpAdd(basePt, ccp(0, -i*135)));
		addChild(m_cardGroup[i]);
	}

	m_btnCancle = (CCSprite*)getChildByTag(SelectBackGround::BtnCancel);
	m_btnOK = (CCSprite*)getChildByTag(SelectBackGround::BtnOK);
	m_tabCardGroup = (CCSprite*)getChildByTag(SelectBackGround::TabCardGroup);
	m_tabTrap = (CCSprite*)getChildByTag(SelectBackGround::TabTrap);
	
	m_tile = (CCSprite*)getChildByTag(SelectBackGround::TileType);
	m_label = (CCLabelTTF*)getChildByTag(SelectBackGround::DescriptionLabel);
	
	return true;
}

void SelectBackGround::setInfo(int tiletype)
{
	std::string label = "普通泥土地";
	std::string image = "block/box1.png";
	switch (tiletype)
	{
		case MapTile::Wind:
			image = "block/box2.png";
			label = "风-魔草地：增加风属性卡牌法术攻击，降低其他属性卡牌法术攻击";
			break;
		case MapTile::Water:
			image = "block/box3.png";
			label = "水-泥潭，水潭：增加水属性卡牌速度，降低其他属性卡牌速度";
			break;
		case MapTile::Fire:
			label = "火-岩浆: 增加火属性物理攻击，降低其他属性卡牌物理攻击";
			image = "block/box4.png";
			break;
		case MapTile::Wood:
			label = "木-灌木，荒木：增加木属性卡牌物理和法术防御，降低其他属性卡牌防御";
			image = "block/box5.png";
			break;
		case MapTile::End:
			label = "宝箱";
			image = "block/box7.png";
			break;
		default:
			break;
	}

	m_tile->setTexture(CCTextureCache::sharedTextureCache()->addImage(image.c_str()));
	m_label->setString(label.c_str());

}

int SelectBackGround::isHit(cocos2d::CCPoint pt)
{
	if(::isHit(m_tabCardGroup->getQuad(), m_tabCardGroup->convertToNodeSpace(pt)))
	{
		setTab(0);
		return -1;
	}
	
	if(::isHit(m_tabTrap->getQuad(), m_tabTrap->convertToNodeSpace(pt)))
	{
		setTab(1);
		return -1;
	}
	
	if(::isHit(m_btnCancle->getQuad(), m_btnCancle->convertToNodeSpace(pt)))
	{
		return BtnCancel;
	}
	
	if(::isHit(m_btnOK->getQuad(), m_btnOK->convertToNodeSpace(pt)))
	{
		return BtnOK;
	}
	
	for (int i = 0; i < 3; i++)
	{
		if(m_cardGroup[i]->isVisible() && m_cardGroup[i]->isHit(pt))
			return -1;
	}
	
	if(m_listviewLayer && m_listviewLayer->isVisible())
	{
		for (int i = 0; i < 8; i++)
		{
			if(m_magicGuard[i]->isHit(pt))
				return -1;
		}
	}
	
	return -1;
}

void SelectBackGround::updateMagicGuard(bool show)
{
	if(!m_listviewLayer)
	{
		//init items
		CCSize itemsize = CCSizeMake(626*0.98, 139*0.98);
		m_listviewLayer = ListViewLayer::create();
		
		m_listviewLayer->setListViewRect(CCRectMake(10, 210,itemsize.width,itemsize.height* 1.01 * 3));
		m_listviewLayer->setScrollDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
		m_listviewLayer->setItemContent(itemsize.width,itemsize.height,1,3);
		
		addChild(m_listviewLayer);
		
		for(int i = 0; i < 8; i++)
		{
			MagicGuard* guard = MagicGuard::create();
			m_listviewLayer->addItem(guard);
			m_magicGuard[i] = guard;
		}
	}
	
	if (show)
	{
		m_listviewLayer->setVisible(true);
	}
	else
	{
		m_listviewLayer->setVisible(false);
	}
}

void SelectBackGround::updateCardGroup(bool show)
{
	if(!show)
	{
		for (int i = 0; i < 3; i++)
		{
			m_cardGroup[i]->setVisible(false);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			m_cardGroup[i]->setVisible(true);
		}
	}
}

void SelectBackGround::setTab(int tab)
{
	if(tab == 0)
	{
		m_tabCardGroup->setZOrder(5);
		m_tabTrap->setZOrder(0);
		updateCardGroup(true);
		updateMagicGuard(false);
	}
	else
	{
		m_tabCardGroup->setZOrder(0);
		m_tabTrap->setZOrder(5);
		updateCardGroup(false);
		updateMagicGuard(true);
	}
}
