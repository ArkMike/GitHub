#include "SceneGame.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

SceneGame::SceneGame(void)
{
	//CCLog("SceneGame::SceneGame()");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist", "shoot.png");
}


SceneGame::~SceneGame(void)
{
	//CCLog("SceneGame::~SceneGame()");
}

bool SceneGame::init()
{
	//CCLog("SceneGame::init()");
	if(!CCScene::init())	return false;

	// background
	groundLayer = LayerGround::create();
	addChild(groundLayer, 0);

	// game
	//gameLayer = LayerGame::create();
	gameLayer = LayerGame::getLayerGame();
	addChild(gameLayer, 1);

	// ui
	uiLayer = LayerUI::getLayerUIShared();
	addChild(uiLayer, 2);

	
	// ÔÝÍ£°´Å¥
	CCSprite *paNor = CCSprite::createWithSpriteFrameName("game_pause_nor.png");
	CCSprite *paPre = CCSprite::createWithSpriteFrameName("game_pause_pressed.png");
	pause = CCMenuItemImage::create();
	pause->initWithNormalSprite(paNor, paPre, NULL, this, menu_selector(SceneGame::GamePause));
	pause->setPosition(ccp(getSize().width/10, getSize().height*0.95f));

	CCSprite *reNor = CCSprite::createWithSpriteFrameName("game_resume_nor.png");
	CCSprite *rePre = CCSprite::createWithSpriteFrameName("game_resume_pressed.png");
	resume = CCMenuItemImage::create();
	resume->initWithNormalSprite(reNor, rePre, NULL, this, menu_selector(SceneGame::GameResume));
	resume->setPosition(ccp(getSize().width/10, getSize().height*0.95f));
	resume->setVisible(false);

	//CCMenuItemToggle *gamepause = CCMenuItemToggle::createWithTarget(this,
	//	NULL,//menu_selector(SceneGame::GameControl), 
	//	pause, resume, NULL);
	//gamepause->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/10,
	//	CCDirector::sharedDirector()->getWinSize().height*0.95f));

	CCMenu *buttons = CCMenu::create(pause, resume, NULL);
	buttons->setPosition(CCPointZero);
	addChild(buttons);

	return true;
}

CCScene* SceneGame::getGame()
{
	//CCLog("SceneGame::getGame()");
	CCScene *scene = CCScene::create();
	SceneGame *game = SceneGame::create();
	scene->addChild(game);

	return scene;
}

CCSize SceneGame::getSize()
{
	return CCDirector::sharedDirector()->getWinSize();
}

void SceneGame::GamePause(CCObject *obj)
{
	//gameLayer->isGamePause = !gameLayer->isGamePause;
	gameLayer->GamePause();
	pause->setVisible(false);
	resume->setVisible(true);
	groundLayer->unscheduleUpdate();
	gameLayer->unscheduleUpdate();
	//CCLog("game pause");
	gameLayer->enemyLayer->EnemyPause();
	gameLayer->propLayer->PropPause();
	gameLayer->bulletLayer->BulletPause();
}

void SceneGame::onEnter()
{
	CCScene::onEnter();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_music.mp3", true);
	//CCLog("game scene enter");
}

void SceneGame::onExit()
{
	CCScene::onExit();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	//CCLog("game scene exit");
}

void SceneGame::GameResume(CCObject *obj)
{
	//gameLayer->isGamePause = !gameLayer->isGamePause;
	gameLayer->GamePause();
	pause->setVisible(true);
	resume->setVisible(false);
	groundLayer->scheduleUpdate();
	gameLayer->scheduleUpdate();
	//CCLog("game resume");
	gameLayer->enemyLayer->EnemyResume();
	gameLayer->propLayer->PropResume();
	gameLayer->bulletLayer->BulletResume();
}

void SceneGame::GameControl(CCObject *obj)
{
	gameLayer->isGamePause = !gameLayer->isGamePause;
	if(!gameLayer->isGamePause)
	{
		groundLayer->unscheduleUpdate();
		gameLayer->unscheduleUpdate();
		//CCLog("game pause in control");
	}
	else
	{
		groundLayer->scheduleUpdate();
		gameLayer->scheduleUpdate();
		//CCLog("game resume in control");
	}
}