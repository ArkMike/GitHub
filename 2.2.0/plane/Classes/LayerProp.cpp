#include "LayerProp.h"


LayerProp::LayerProp(void)
{
	propArray = CCArray::create();
	propArray->retain();
}


LayerProp::~LayerProp(void)
{
	propArray->release();
	propArray = NULL;
}

bool LayerProp::init()
{
	if(!CCLayer::init())	return false;

	CCTexture2D *propElement = CCTextureCache::sharedTextureCache()->addImage("shoot.png");
	propBatch = CCSpriteBatchNode::createWithTexture(propElement);
	addChild(propBatch);

	schedule(schedule_selector(LayerProp::createDouble), 10);
	schedule(schedule_selector(LayerProp::createBomb), 29);
	scheduleUpdate();
	return true;
}

void LayerProp::update(float dt)
{
	for(int i=0; i<propArray->count(); i++)
	{
		CCSprite *prop = (CCSprite*)propArray->objectAtIndex(i);
		prop->setPositionY(prop->getPositionY() - 500 *dt);
		if(prop->getPositionY() <= 100)
			RemoveProp(prop);
	}
}

CCSize LayerProp::getSize()
{
	return CCDirector::sharedDirector()->getWinSize();
}

void LayerProp::createDouble(float dt)
{
	CCSprite *prop = CCSprite::createWithSpriteFrameName("ufo1.png");
	prop->setTag(11);
	float randX = rand()%(int)(getSize().width
		- prop->getContentSize().width) + prop->boundingBox().size.width/2;
	prop->setPosition(ccp(randX, 800));
	propBatch->addChild(prop);
	propArray->addObject(prop);
}

void LayerProp::createBomb(float dt)
{
	CCSprite *prop = CCSprite::createWithSpriteFrameName("ufo2.png");
	prop->setTag(12);
	float randX = rand()%(int)(getSize().width
		- prop->getContentSize().width) + prop->boundingBox().size.width/2;
	prop->setPosition(ccp(randX, 800));
	propBatch->addChild(prop);
	propArray->addObject(prop);
}

void LayerProp::RemoveProp(CCSprite *psender)
{
	propBatch->removeChild(psender, true);
	propArray->removeObject(psender, true);
}

void LayerProp::PropPause()
{
	unschedule(schedule_selector(LayerProp::createDouble));
	unschedule(schedule_selector(LayerProp::createBomb));
	unscheduleUpdate();
}

void LayerProp::PropResume()
{
	schedule(schedule_selector(LayerProp::createDouble), 10);
	schedule(schedule_selector(LayerProp::createBomb), 30);
	scheduleUpdate();
}