#include "LayerGround.h"


LayerGround::LayerGround(void)
{
	//CCLog("LayerGround::LayerGround()");
}


LayerGround::~LayerGround(void)
{
	//CCLog("LayerGround::~LayerGround()");
}

bool LayerGround::init()
{
	//CCLog("LayerGround::init()");
	if(!CCLayer::init())	return false;

	back1 = CCSprite::createWithSpriteFrameName("background.png");
	back1->setAnchorPoint(CCPointZero);
	back1->setPosition(CCPointZero);
	addChild(back1);

	back2 = CCSprite::createWithSpriteFrameName("background.png");
	back2->setAnchorPoint(CCPointZero);
	back2->setPosition(ccp(0, back2->getContentSize().height-2));
	addChild(back2);

	// 调用更新
	scheduleUpdate();

	return true;
}

void LayerGround::update(float dt)
{
	//CCLog("LayerGround::update()");
	back1->setPositionY(back1->getPositionY() - 3);
	back2->setPositionY(back1->getPositionY() + back1->getContentSize().height - 2);

	if(back2->getPositionY() <= 0)
		back1->setPositionY(0);
}