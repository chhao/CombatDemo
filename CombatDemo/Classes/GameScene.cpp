#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !CCScene::init() )
    {
        return false;
    }

	m_mainlayer = MainLayer::create();
	m_mainlayer->retain();
	addChild(m_mainlayer);
    
	m_prebattlelayer = PrepareBattleLayer::create();
	m_prebattlelayer->retain();
	
	m_battlelayer = BattleLayer::create();
	m_battlelayer->retain();
	
	m_resultlayer = ResultLayer::create();
	m_resultlayer->retain();
	
	m_hudlayer = HUDLayer::create();
	m_hudlayer->retain();
	addChild(m_hudlayer);
	
    return true;
}

void GameScene::setActiveLayer(GameScene::LayerType type)
{
	removeAllChildren();
	switch (type)
	{
		case Layer_Main:
		{
			addChild(m_mainlayer);
			addChild(m_hudlayer);
		}
			break;
		case Layer_PreBattle:
		{
			addChild(m_prebattlelayer);
			addChild(m_hudlayer);
		}
			break;
		case Layer_Battle:
			addChild(m_battlelayer);
			break;
		case Layer_Result:
		{
			addChild(m_resultlayer);
			addChild(m_hudlayer);
		}
			break;
		default:
			break;
	}
	
	
}
