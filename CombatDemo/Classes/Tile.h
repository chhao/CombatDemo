//
//  Tile.h
//  CombatDemo
//
//  Created by Hao Chen on 10/5/13.
//
//

#ifndef __CombatDemo__Tile__
#define __CombatDemo__Tile__

#include <iostream>
#include "cocos2d.h"

class MapTile : public cocos2d::CCSprite
{
public:
	enum TileType
	{
		Normal = 1,
		Wind = 2,
		Fire = 3,
		Water = 4,
		Wood = 5,
		End = 6,
	};
	
	MapTile();
	~MapTile();
	
	static MapTile* create(TileType type);

	TileType getType();

	bool isHit(cocos2d::CCPoint pt);
	
	int getNextTile() {return m_nextTile;}
	int getTileID() {return m_id;}
	
	void setTileID(int ID) {m_id = ID;}
	void setNextTile(int ID) {m_nextTile = ID;}
	
private:
	TileType m_type;
	int m_id;
	int m_nextTile;
};

class TerrainMap : public cocos2d::CCNode
{
public:
	TerrainMap();
	~TerrainMap();
	
	static TerrainMap* createWithMap(const std::string& layout);
	
	void readLayout(const std::string& layout);
	
	int isHit(cocos2d::CCPoint pt);
	
private:
	std::list<MapTile*> m_tilelist;
};

#endif /* defined(__CombatDemo__Tile__) */
