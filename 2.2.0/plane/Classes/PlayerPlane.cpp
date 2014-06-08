#include "PlayerPlane.h"
#include "LayerGame.h"

PlayerPlane::PlayerPlane(void)
{
	isMove = false;
	isLive = true;
}


PlayerPlane::~PlayerPlane(void)
{
}

PlayerPlane* PlayerPlane::sharedPlane = NULL;

PlayerPlane* PlayerPlane::createPlaneWithName(const char *psname)
{
	PlayerPlane *plane = new PlayerPlane();
	plane->initPlaneWithName(psname);
	sharedPlane = plane;
	plane->autorelease();
	return plane;
}

void PlayerPlane::initPlaneWithName(const char *psname)
{
	CCSprite::initWithSpriteFrameName(psname);

	//CCSprite *icon1 = CCSprite::create("icon.png");
	//icon1->setScale(0.1f);
	//addChild(icon1);
	//CCSprite *icon2 = CCSprite::create("icon.png");
	//icon2->setScale(0.1f);
	//icon2->setPosition(ccp(0, getContentSize().height));
	//addChild(icon2);
	//CCSprite *icon3 = CCSprite::create("icon.png");
	//icon3->setScale(0.1f);
	//icon3->setPosition(ccp(getContentSize().width, getContentSize().height));
	//addChild(icon3);
	//CCSprite *icon4 = CCSprite::create("icon.png");
	//icon4->setScale(0.1f);
	//icon4->setPosition(ccp(getContentSize().width, 0));
	//addChild(icon4);
}

void PlayerPlane::onEnter()
{
	CCSprite::onEnter();
	//CCLog("player plane onenter.");
	CCAnimation *fly = CCAnimation::create();
	fly->setDelayPerUnit(0.15f);
	fly->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
	fly->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
	runAction(CCRepeatForever::create(CCAnimate::create(fly)));
}

void PlayerPlane::onExit()
{
	CCSprite::onExit();
	//CCLog("player plane onexit.");
}

void PlayerPlane::PlaneFall()
{
	isLive = false;

	CCAnimation *fall = CCAnimation::create();
	fall->setDelayPerUnit(0.2f);
	fall->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
	fall->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
	fall->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
	fall->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));

	CCCallFunc *change = CCCallFunc::create(LayerGame::getLayerGame(), callfunc_selector(LayerGame::GameOver));
	runAction(CCSequence::create(CCAnimate::create(fall), change, NULL));
}

void PlayerPlane::Reset()
{
	isLive = true;
}