#include "LayerBullet.h"
//#include "proj.win32\PlayerPlane.h"
#include "PlayerPlane.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

LayerBullet::LayerBullet(void)
{
	bulletArray = CCArray::create();
	bulletArray->retain();
}


LayerBullet::~LayerBullet(void)
{
	bulletArray->release();
	bulletArray = NULL;
}

bool LayerBullet::init()
{
	if(!CCLayer::init())	return false;

	CCTexture2D *bulletElement = CCTextureCache::sharedTextureCache()->addImage("shoot.png");
	bulletBatch = CCSpriteBatchNode::createWithTexture(bulletElement);
	addChild(bulletBatch);

	fire = false;

	SingleStart(1);

	scheduleUpdate();
	return true;
}

void LayerBullet::update(float dt)
{
	for(int i=0; i<bulletArray->count(); i++)
	{
		CCSprite *bullet = (CCSprite*)bulletArray->objectAtIndex(i);
		bullet->setPositionY(bullet->getPositionY() + 600 * dt);
		if(bullet->getPositionY() >= CCDirector::sharedDirector()->getWinSize().height)
			RemoveBullet(bullet);
	}
}

void LayerBullet::SingleStart(float delay)
{
	schedule(schedule_selector(LayerBullet::SingleLaunch), 0.2f, kCCRepeatForever, delay);
}

void LayerBullet::SingleLaunch(float dt)
{
	if(fire)
		DoubleStop();
	else
	{
		CCSprite *bullet = CCSprite::createWithSpriteFrameName("bullet1.png");
		//bullet->setPosition(ccp(PlayerPlane::sharedPlane->getPositionX(), 	PlayerPlane::sharedPlane->getPositionY() 
		//	+ PlayerPlane::sharedPlane->getChildByTag(10)->getContentSize().height/2));
		bullet->setPosition(ccp(PlayerPlane::sharedPlane->getPositionX(), 	
			PlayerPlane::sharedPlane->getPositionY() + PlayerPlane::sharedPlane->getContentSize().height/2));
		bulletBatch->addChild(bullet);
		bulletArray->addObject(bullet);
		SimpleAudioEngine::sharedEngine()->playEffect("bullet.mp3");
	}
}

void LayerBullet::SingleStop()
{
	unschedule(schedule_selector(LayerBullet::SingleLaunch));
}

void LayerBullet::DoubleStart()
{
	schedule(schedule_selector(LayerBullet::DoubleLaunch), 0.2f);
	fire = true;
}

void LayerBullet::DoubleLaunch(float dt)
{
	CCSprite *left = CCSprite::createWithSpriteFrameName("bullet2.png");
	CCSprite *right = CCSprite::createWithSpriteFrameName("bullet2.png");
	//left->setPosition(ccp(PlayerPlane::sharedPlane->getPositionX() - 20, 
	//	PlayerPlane::sharedPlane->getPositionY() 	+ PlayerPlane::sharedPlane->getChildByTag(10)->getContentSize().height/2));
	//right->setPosition(ccp(PlayerPlane::sharedPlane->getPositionX() + 20,
	//	PlayerPlane::sharedPlane->getPositionY() 	+ PlayerPlane::sharedPlane->getChildByTag(10)->getContentSize().height/2));
	left->setPosition(ccp(PlayerPlane::sharedPlane->getPositionX() - 20, 
		PlayerPlane::sharedPlane->getPositionY() 	+ PlayerPlane::sharedPlane->getContentSize().height/2));
	right->setPosition(ccp(PlayerPlane::sharedPlane->getPositionX() + 20,
		PlayerPlane::sharedPlane->getPositionY() 	+ PlayerPlane::sharedPlane->getContentSize().height/2));
	bulletBatch->addChild(left);
	bulletBatch->addChild(right);
	bulletArray->addObject(left);
	bulletArray->addObject(right);
		SimpleAudioEngine::sharedEngine()->playEffect("bullet.mp3");
}

void LayerBullet::DoubleStop()
{
	unschedule(schedule_selector(LayerBullet::DoubleLaunch));
	fire = false;
}

void LayerBullet::RemoveBullet(CCSprite *psender)
{
	bulletBatch->removeChild(psender, true);
	bulletArray->removeObject(psender, true);
}

void LayerBullet::RemoveAll()
{
	for(int i=0; i<bulletArray->count(); i++)
	{
		CCSprite *bullet = (CCSprite*)bulletArray->objectAtIndex(i);
		if(bullet != NULL)
		{
			RemoveBullet(bullet);
		}
	}
}

void LayerBullet::BulletPause()
{
	SingleStop();
	DoubleStop();
	unscheduleUpdate();
}

void LayerBullet::BulletResume()
{
	if(fire)
		DoubleStart();
	else
		SingleStart(0);
	scheduleUpdate();
}