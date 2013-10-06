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
		tile->setPositionX(320 + (value["posX"].asInt() - 2)*101);
		tile->setPositionY(480 - (value["posY"].asInt() - 2)*101);
		tile->setTileID(value["id"].asInt());
		tile->setNextTile(value["nextId"].asInt());
		
		addChild(tile);
		m_tilelist.push_back(tile);
	}
}

int TerrainMap::isHit(cocos2d::CCPoint pt)
{
	for (std::list<MapTile*>::iterator itr = m_tilelist.begin(); itr != m_tilelist.end(); ++itr)
	{
		MapTile* tile = *itr;
		if(tile->isHit(pt))
			return tile->getType();
	}
	
	return -1;
}