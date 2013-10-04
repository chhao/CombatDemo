#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MainLayer.h"
#include "PrepareBattleLayer.h"
#include "ResultLayer.h"
#include "BattleLayer.h"
#include "HUDLayer.h"

class GameScene : public cocos2d::CCScene
{
public:
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameScene);

	bool init();
	
	enum LayerType
	{
		Layer_Main = 1,
		Layer_PreBattle = 2,
		Layer_Battle = 3,
		Layer_Result = 4,
	};

	void setActiveLayer(LayerType type);

private:
	MainLayer* m_mainlayer;
	PrepareBattleLayer* m_prebattlelayer;
	BattleLayer* m_battlelayer;
	ResultLayer* m_resultlayer;
	HUDLayer* m_hudlayer;
};

#endif // __HELLOWORLD_SCENE_H__
