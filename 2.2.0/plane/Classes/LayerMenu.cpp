#include "LayerMenu.h"


LayerMenu::LayerMenu(void)
{
	//CCLog("LayerMenu::LayerMenu()");
}


LayerMenu::~LayerMenu(void)
{
	//CCLog("LayerMenu::~LayerMenu()");
}

bool LayerMenu::init()
{
	//CCLog("LayerMenu::init()");
	if(!CCLayer::init())	return false;

	// background 
	background = CCSprite::createWithSpriteFrameName("background.png");
	background->setPosition(ccp(getSize().width/2, getSize().height/2));
	addChild(background, 0);

	// title
	title = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
	title->setAnchorPoint(ccp(0.5f, 0));
	title->setPosition(ccp(getSize().width/2, getSize().height*0.7f));
	addChild(title, 1);

	// loading 
	loading = CCSprite::createWithSpriteFrameName("game_loading1.png");
	loading->setPosition(ccp(getSize().width/2, getSize().height*0.4f));
	addChild(loading, 1);

	CCAnimation *loadAct = CCAnimation::create();
	loadAct->setDelayPerUnit(0.25f);
	loadAct->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
	loadAct->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
	loadAct->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
	loadAct->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));

	CCRepeat *repeat = CCRepeat::create(CCAnimate::create(loadAct), 2);
	CCCallFuncN *nextscene = CCCallFuncN::create(this, callfuncN_selector(LayerMenu::nextScene));

	loading->runAction(CCSequence::create(repeat, nextscene, NULL));

	return true;
}

CCSize LayerMenu::getSize()
{
	return CCDirector::sharedDirector()->getWinSize();
}

void LayerMenu::nextScene(CCNode *node)
{
	//CCLog("jump to game scene");
	CCTransitionMoveInB *move = CCTransitionMoveInB::create(0.5f, SceneGame::getGame());
	CCDirector::sharedDirector()->replaceScene(move);
	//CCDirector::sharedDirector()->pushScene(move);
}