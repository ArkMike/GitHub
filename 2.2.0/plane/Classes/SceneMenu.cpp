#include "SceneMenu.h"
#include "SceneOver.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

SceneMenu::SceneMenu(void)
{
	//CCLog("SceneMenu::SceneMenu()");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot_background.plist",
		"shoot_background.png");
}


SceneMenu::~SceneMenu(void)
{
	//CCLog("SceneMenu::~SceneMenu()");
}

bool SceneMenu::init()
{
	//CCLog("SceneMenu::init()");
	if(!CCScene::init())	return false;

	// menu layer
	menuLayer = LayerMenu::create();
	addChild(menuLayer);

	return true;
}

CCScene* SceneMenu::getMenu()
{
	//CCLog("SceneMenu::getMenu()");
	CCScene *scene = CCScene::create();
	SceneMenu *menu = SceneMenu::create();
	scene->addChild(menu);

	return scene;
}

void SceneMenu::LoadSound()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("game_music.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("enemy1_down.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("enemy2_down.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("enemy3_down.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("game_over.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("get_bomb.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("get_double_laser.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("bullet.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("use_bomb.mp3");
}

bool SceneMenu::isSaveHeight()
{
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isSave"))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("isSave", true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighScore", 0);
		CCUserDefault::sharedUserDefault()->flush();
		return false;
	}
	else	return true;
}

void SceneMenu::getHeight()
{
	if(isSaveHeight())
		SceneOver::hightest_current = CCUserDefault::sharedUserDefault()->getIntegerForKey("HighScore", 0);
}