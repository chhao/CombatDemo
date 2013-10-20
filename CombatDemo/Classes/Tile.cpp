//
//  Tile.cpp
//  CombatDemo
//
//  Created by Hao Chen on 10/5/13.
//
//

#include "Tile.h"
#include "HelperUtil.h"
#include "json_lib.h"

using namespace cocos2d;

MapTile* MapTile::create(MapTile::TileType type)
{
	MapTile* tile = new MapTile;
	std::string image = "block/box1.png";
	switch (type)
	{
		case Wind:
			image = "block/box2.png";
			break;
		case Water:
			image = "block/box3.png";
			break;
		case Fire:
			image = "block/box4.png";
			break;
		case Wood:
			image = "block/box5.png";
			break;
		case End:
			image = "block/box7.png";
			break;
		default:
			break;
	}
	
	if(tile && tile->initWithFile(image.c_str()))
	{
		tile->autorelease();
		tile->m_type = type;
		return tile;
	}
	
	delete tile;
	return NULL;
}


MapTile::MapTile()
:m_mark(MapTile::None)
,m_type(MapTile::Normal)
{
	
}

MapTile::~MapTile()
{
	
}

MapTile::TileType MapTile::getType()
{
	return m_type;
}

bool MapTile::isHit(cocos2d::CCPoint pt)
{
	if(::isHit(getQuad(), convertToNodeSpace(pt)))
		return true;
	
	return false;
}

MapTile::TileMark MapTile::getMark()
{
	return m_mark;
}

void MapTile::setMark(MapTile::TileMark mark)
{
	m_mark = mark;
	std::stringstream ss;
	switch (m_mark)
	{
		case Card1:
		case Card2:
		case Card3:
		{
			ss << "C" << m_mark+1;
		}
			break;
			
		case Trap1:
		case Trap2:
		{
			ss << "T" << m_mark-2;
		}
			break;
			
		case Guard1:
		case Guard2:
		{
			ss << "G" << m_mark-4;
		}
			break;
		default:
			break;
	}
	CCSize size = getContentSize();
	CCLabelTTF* label = CCLabelTTF::create(ss.str().c_str(), "", 30,size,kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	label->setPosition(ccp(size.width*0.5, size.height*0.5));
	addChild(label, 5);
}

///////////////////////////////
TerrainMap* TerrainMap::createWithMap(const std::string &layout)
{
	TerrainMap* terrain = new TerrainMap;
	if(terrain && terrain->init())
	{
		terrain->autorelease();
		terrain->readLayout(layout);
		return terrain;
	}
	
	return NULL;
}

TerrainMap::TerrainMap()
{
	
}

TerrainMap::~TerrainMap()
{
	
}

void TerrainMap::readLayout(const std::string &layout)
{
	CSJson::Value root;
	readJsonFile(layout, root);
	
	for (int i = 0; i < root.size(); i++)
	{
		CSJson::Value value = root[i];
		
		MapTile* tile = MapTile::create(MapTile::TileType(value["type"].asInt()));
		tile->setPositionX(320 + (value["posX"].asInt() - 2)*100);
		tile->setPositionY(480 - (value["posY"].asInt() - 2)*100);
		tile->setTileID(value["id"].asInt());
		tile->setNextTile(value["nextId"].asInt());
		tile->setTag(value["id"].asInt());
		
		addTile(tile);
	}
}

int TerrainMap::isHit(cocos2d::CCPoint pt)
{
	for (std::list<MapTile*>::iterator itr = m_tilelist.begin(); itr != m_tilelist.end(); ++itr)
	{
		MapTile* tile = *itr;
		if(tile->isHit(pt))
		{
			m_curTile = tile;
			return tile->getType();
		}
	}
	
	m_curTile = NULL;
	return -1;
}

void TerrainMap::markCurTile(MapTile::TileMark mark)
{
	m_curTile->setMark(mark);
}

MapTile* TerrainMap::getTileByID(int ID)
{
	return (MapTile*)getChildByTag(ID);
}

void TerrainMap::addTile(MapTile *tile)
{
	addChild(tile);
	m_tilelist.push_back(tile);
}
