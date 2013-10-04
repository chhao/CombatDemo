#include "HelloWorldScene.h"
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
    return true;
}

void GameScene::setActiveLayer(GameScene::LayerType type)
{
	removeAllChildren();
	switch (type)
	{
		case Layer_Main:
			addChild(m_mainlayer);
			break;
		case Layer_PreBattle:
			addChild(m_prebattlelayer);
			break;
		default:
			break;
	}
}
