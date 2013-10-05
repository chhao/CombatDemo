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

SelectCardGroup::SelectCardGroup()
{
	
}

SelectCardGroup::~SelectCardGroup()
{
	
}

bool SelectCardGroup::init()
{
	if(!CCNode::init())
		return false;
	
	readLayout(this, "SelectCardGroup.json");
	
	return true;
}

int SelectCardGroup::isHit(cocos2d::CCPoint pt)
{
	return -1;
}

///////////////////////////////////////////
SelectBackGround::SelectBackGround()
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
	
	m_cardGroup = SelectCardGroup::create();
	addChild(m_cardGroup);
	
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
			label = "终点";
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
	
	return -1;
}

void SelectBackGround::setTab(int tab)
{
	if(tab == 0)
	{
		m_tabCardGroup->setZOrder(5);
		m_tabTrap->setZOrder(0);
		m_cardGroup->setVisible(true);
	}
	else
	{
		m_tabCardGroup->setZOrder(0);
		m_tabTrap->setZOrder(5);
		m_cardGroup->setVisible(false);
	}
}
