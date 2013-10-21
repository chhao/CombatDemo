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
	
	enum TileMark
	{
		None = -1,
		Card1,
		Card2,
		Card3,
		Trap1,
		Trap2,
		Guard1,
		Guard2,
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

	void setMark(TileMark mark);
	TileMark getMark();
	
	void setCoordinate(int x, int y);
	int getXCoord() {return m_posX;}
	int getYCoord() {return m_posY;}
private:
	TileType m_type;
	TileMark m_mark;
	int m_id;
	int m_nextTile;
	
	int m_posX;
	int m_posY;
};

class TerrainMap : public cocos2d::CCNode
{
public:
	TerrainMap();
	~TerrainMap();
	
	static TerrainMap* createWithMap(const std::string& layout);
	
	void readLayout(const std::string& layout);
	
	int isHit(cocos2d::CCPoint pt);
	
	void markCurTile(MapTile::TileMark mark);
	
	MapTile* getTileByID(int ID);
	
	MapTile* getTileByCoordinate(int x, int y);
	
	void addTile(MapTile* tile);
	
private:
	std::list<MapTile*> m_tilelist;
	MapTile* m_curTile;
};

#endif /* defined(__CombatDemo__Tile__) */
