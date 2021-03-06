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
	
	if(m_select)
		m_checkBox->setTexture(CCTextureCache::sharedTextureCache()->addImage("chk_2.png"));
	else
		m_checkBox->setTexture(CCTextureCache::sharedTextureCache()->addImage("chk_1.png"));
}

bool MagicGuard::isHit(cocos2d::CCPoint pt)
{
	if(::isHit(m_checkBox->getQuad(), m_checkBox->convertToNodeSpace(pt)))
	{
		setSelected(!m_select);
		
		return true;
	}
	
	return false;
}

void MagicGuard::setLabel(const std::string &label)
{
	m_label->setString(label.c_str());
}
///////////////////////////////////
CardGroupItem::CardGroupItem()
{
	
}

CardGroupItem::~CardGroupItem()
{
	
}

bool CardGroupItem::init()
{
	if(!CCNode::init())
		return false;
	
	readLayout(this, "SelectCardGroup.json", ccp(-626*0.5*0.98, -139*0.5*0.98));
	for (int i = 0; i < 5; i++)
	{
		m_card[i] = (CCSprite*)getChildByTag(i+3);
	}
	m_checkBox = (CCSprite*)getChildByTag(CardGroupItem::CheckBox);
	
	return true;
}

bool CardGroupItem::isHit(cocos2d::CCPoint pt)
{
	if(::isHit(m_checkBox->getQuad(), m_checkBox->convertToNodeSpace(pt)))
	{
		setSelected(!m_select);
		
		return true;
	}
	
	return false;
}

bool CardGroupItem::getSelected()
{
	return m_select;
}

void CardGroupItem::setSelected(bool select)
{
	m_select = select;
	
	if(m_select)
		m_checkBox->setTexture(CCTextureCache::sharedTextureCache()->addImage("chk_2.png"));
	else
		m_checkBox->setTexture(CCTextureCache::sharedTextureCache()->addImage("chk_1.png"));
}


///////////////////////////////////////////
std::vector<std::string> g_labelvec;

SelectBackGround::SelectBackGround()
:m_listviewLayer(NULL)
,m_selectIndex(-1)
{
	if(g_labelvec.empty())
	{
		g_labelvec.push_back("加速恢复");
		g_labelvec.push_back("增加魔法防御");
		g_labelvec.push_back("增加物理防御");
		g_labelvec.push_back("增加速度");
		g_labelvec.push_back("增加物理攻击");
		g_labelvec.push_back("增加魔法攻击");
		g_labelvec.push_back("增加暴击几率");
		g_labelvec.push_back("使己方攻击有一定几率吸血");
	}
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
		m_cardGroup[i] = CardGroupItem::create();
		m_cardGroup[i]->setPosition(ccpAdd(basePt, ccp(0, -i*135)));
		addChild(m_cardGroup[i]);
	}

	m_btnCancle = (CCSprite*)getChildByTag(SelectBackGround::BtnCancel);
	m_btnOK = (CCSprite*)getChildByTag(SelectBackGround::BtnOK);
	m_tabCardGroup = (CCSprite*)getChildByTag(SelectBackGround::TabCardGroup);
	m_tabTrap = (CCSprite*)getChildByTag(SelectBackGround::TabTrap);
	m_tabTrap->setVisible(false);
	
	m_tile = (CCSprite*)getChildByTag(SelectBackGround::TileType);
	m_label = (CCLabelTTF*)getChildByTag(SelectBackGround::DescriptionLabel);
	
	return true;
}

void SelectBackGround::resetCheckStatus()
{
	for (int i = 0; i < 3; i++)
	{
		m_cardGroup[i]->setSelected(false);
	}
	
	if(m_listviewLayer)
	{
		for (int i = 0; i < 8; i++)
		{
			m_magicGuard[i]->setSelected(false);
		}
	}
	
	m_selectIndex = -1;
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
	
	if(m_tabTrap->isVisible() && ::isHit(m_tabTrap->getQuad(), m_tabTrap->convertToNodeSpace(pt)))
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
		{
			m_selectIndex = i;
			return -1;
		}
	}
	
	if(m_listviewLayer && m_listviewLayer->isVisible())
	{
		for (int i = 0; i < 8; i++)
		{
			if(m_magicGuard[i]->isHit(pt))
			{
				m_selectIndex = 3+i;
				return -1;
			}
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
			guard->setLabel(g_labelvec[i]);
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

int SelectBackGround::getSelectIndex()
{
	return m_selectIndex;
}