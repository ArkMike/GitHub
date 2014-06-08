#include "LayerEnemy.h"
//#include "proj.win32\LayerUI.h"
#include "LayerUI.h"
//#include "PlayerPlane.h"

LayerEnemy::LayerEnemy(void)
{
	// small
	smallArray = CCArray::create();
	smallArray->retain();
	// mid
	midArray = CCArray::create();
	midArray->retain();
	// big
	bigArray = CCArray::create();
	bigArray->retain();
}


LayerEnemy::~LayerEnemy(void)
{
	smallArray->release();
	smallArray = NULL;
	midArray->release();
	midArray = NULL;
	bigArray->release();
	bigArray = NULL;
}

bool LayerEnemy::init()
{
	if(!CCLayer::init())	return false;

	CCTexture2D *enemyElement = CCTextureCache::sharedTextureCache()->addImage("shoot.png");
	enemyBatch = CCSpriteBatchNode::createWithTexture(enemyElement);
	addChild(enemyBatch);

	CCAnimation *smallDeath = CCAnimation::create();
	smallDeath->setDelayPerUnit(0.1f);
	smallDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
	smallDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
	smallDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
	smallDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));

	CCAnimation *midDeath = CCAnimation::create();
	midDeath->setDelayPerUnit(0.1f);
	midDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
	midDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
	midDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
	midDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));

	CCAnimation *bigDeath = CCAnimation::create();
	bigDeath->setDelayPerUnit(0.1f);
	bigDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
	bigDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
	bigDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
	bigDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
	bigDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
	bigDeath->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));

	CCAnimationCache::sharedAnimationCache()->addAnimation(smallDeath, "DEATH_SMALL");
	CCAnimationCache::sharedAnimationCache()->addAnimation(midDeath, "DEATH_MID");
	CCAnimationCache::sharedAnimationCache()->addAnimation(bigDeath, "DEATH_BIG");
	
	// 分别以不同的间隔生成npc
	schedule(schedule_selector(LayerEnemy::SmallCreate), 0.2f);
	schedule(schedule_selector(LayerEnemy::SmallCreate), 0.3f);
	schedule(schedule_selector(LayerEnemy::SmallCreate), 0.5f);
	schedule(schedule_selector(LayerEnemy::SmallCreate), 1);
	schedule(schedule_selector(LayerEnemy::MidCreate), 3);
	schedule(schedule_selector(LayerEnemy::MidCreate), 5);
	schedule(schedule_selector(LayerEnemy::BigCreate), 8);
	schedule(schedule_selector(LayerEnemy::BigCreate), 15);

	scheduleUpdate();
	return true;
}

void LayerEnemy::update(float dt)
{
	for(int i=0; i<smallArray->count(); i++)
	{
		EnemySmall *enemy = (EnemySmall*)smallArray->objectAtIndex(i);
		if(enemy != NULL && enemy->getPositionY() <= -100)
			SmallNative(enemy);
		else
			enemy->update(dt);
	}

	for(int i=0; i<midArray->count(); i++)
	{
		EnemyMid *enemy = (EnemyMid*)midArray->objectAtIndex(i);
		if(enemy != NULL && enemy->getPositionY() <= -100)
			MidNative(enemy);
		else
			enemy->update(dt);
	}

	for(int i=0; i<bigArray->count(); i++)
	{
		EnemyBig *enemy = (EnemyBig*)bigArray->objectAtIndex(i);
		if(enemy != NULL && enemy->getPositionY() <= -100)
			BigNative(enemy);
		else
			enemy->update(dt);
	}
}

void LayerEnemy::SmallCreate(float dt)
{
	EnemySmall *enemy = EnemySmall::createSmall("enemy1.png");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int mix = enemy->getContentSize().width/2;
	int max = CCDirector::sharedDirector()->getWinSize().width
		- enemy->getContentSize().width/2;
	float randX = (rand()%(max - mix)) + mix;
	enemy->setPosition(ccp(randX, size.height + enemy->getContentSize().height));
	enemyBatch->addChild(enemy);
	smallArray->addObject(enemy);
}

void LayerEnemy::SmallNative(CCSprite *psender)
{
	EnemyBatch(psender);
	SmallArray(psender);
}

void LayerEnemy::SmallBomb(EnemySmall *enemy)
{
	CCAnimate *death = CCAnimate::create(
		CCAnimationCache::sharedAnimationCache()->animationByName("DEATH_SMALL"));
	CCCallFuncND *remove = CCCallFuncND::create(this, 
		callfuncND_selector(LayerEnemy::SmallRemove), (void *)enemy);
	enemy->runAction(CCSequence::create(death, remove, NULL));
}

void LayerEnemy::SmallRemove(CCNode *psender, void *date)
{
	EnemySmall *enemy = (EnemySmall*)date;
	EnemyBatch(enemy);
	SmallArray(enemy);
}

void LayerEnemy::SmallArray(CCSprite *psender)
{
	smallArray->removeObject(psender);
}

void LayerEnemy::MidCreate(float dt)
{
	EnemyMid *enemy = EnemyMid::createMid("enemy2.png");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int mix = enemy->getContentSize().width/2;
	int max = CCDirector::sharedDirector()->getWinSize().width
		- enemy->getContentSize().width/2;
	float randX = (rand()%(max - mix)) + mix;
	enemy->setPosition(ccp(randX, size.height + enemy->getContentSize().height));
	enemyBatch->addChild(enemy);
	midArray->addObject(enemy);
}

void LayerEnemy::MidNative(CCSprite *psender)
{
	EnemyBatch(psender);
	MidArray(psender);
}

void LayerEnemy::MidBomb(EnemyMid *enemy)
{
	CCAnimate *death = CCAnimate::create(
		CCAnimationCache::sharedAnimationCache()->animationByName("DEATH_MID"));
	CCCallFuncND *remove = CCCallFuncND::create(this, 
		callfuncND_selector(LayerEnemy::MidRemove), (void*)enemy);
	enemy->runAction(CCSequence::create(death, remove, NULL));
}

void LayerEnemy::MidRemove(CCNode *psender, void *date)
{
	EnemyMid *enemy = (EnemyMid*)date;
	EnemyBatch(enemy);
	MidArray(enemy);
}

void LayerEnemy::MidArray(CCSprite *psender)
{
	midArray->removeObject(psender, true);
}

void LayerEnemy::BigCreate(float dt)
{
	EnemyBig *enemy = EnemyBig::createBig("enemy3_n1.png");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int mix = enemy->getContentSize().width/2;
	int max = CCDirector::sharedDirector()->getWinSize().width
		- enemy->getContentSize().width/2;
	float randX = (rand()%(max - mix)) + mix;
	enemy->setPosition(ccp(randX, size.height + enemy->getContentSize().height));
	enemyBatch->addChild(enemy);
	bigArray->addObject(enemy);
}

void LayerEnemy::BigNative(CCSprite *psender)
{
	EnemyBig *enemy = (EnemyBig*)psender;
	EnemyBatch(enemy);
	BigArray(enemy);
}

void LayerEnemy::BigBomb(EnemyBig *enemy)
{
	CCAnimate *death = CCAnimate::create(
		CCAnimationCache::sharedAnimationCache()->animationByName("DEATH_BIG"));
	CCCallFuncND *remove = CCCallFuncND::create(this, 
		callfuncND_selector(LayerEnemy::BigRemove), (void*)enemy);
	enemy->runAction(CCSequence::create(death, remove, NULL));
}

void LayerEnemy::BigRemove(CCNode *psender, void *date)
{
	EnemyBig *enemy = (EnemyBig*)date;
	EnemyBatch(enemy);
	BigArray(enemy);
}

void LayerEnemy::BigArray(CCSprite *psender)
{
	bigArray->removeObject(psender, true);
}

void LayerEnemy::EnemyBatch(CCSprite *psender)
{
	enemyBatch->removeChild(psender, true);
}

void LayerEnemy::CleanSmall()
{
	// clean small
	for(int i=0; i<smallArray->count(); i++)
	{
		EnemySmall *enemy = (EnemySmall*)smallArray->objectAtIndex(i);
		if(enemy->GetHP() > 0)
		{
			if(PlayerPlane::sharedPlane->isLive)
				LayerUI::getLayerUIShared()->AddScore(enemy->GetScore());
			SmallBomb(enemy);
		}
	}
}

void LayerEnemy::CleanMid()
{
	// clean mid
	for(int i=0; i<midArray->count(); i++)
	{
		EnemyMid *enemy = (EnemyMid*)midArray->objectAtIndex(i);
		if(enemy->GetHP() > 0)
		{
			if(PlayerPlane::sharedPlane->isLive)
				LayerUI::getLayerUIShared()->AddScore(enemy->GetScore());
			MidBomb(enemy);
		}
	}
}

void LayerEnemy::CleanBig()
{
	// clean big
	for(int i=0; i<bigArray->count(); i++)
	{
		EnemyBig *enemy = (EnemyBig*)bigArray->objectAtIndex(i);
		if(enemy->GetHP())
		{
			if(PlayerPlane::sharedPlane->isLive)
				LayerUI::getLayerUIShared()->AddScore(enemy->GetScore());
			BigBomb(enemy);
		}
	}
}

void LayerEnemy::CleanAllEnemies()
{
	CleanSmall();
	CleanMid();
	CleanBig();
}

void LayerEnemy::EnemyPause()
{
	unschedule(schedule_selector(LayerEnemy::SmallCreate));
	unschedule(schedule_selector(LayerEnemy::SmallCreate));
	unschedule(schedule_selector(LayerEnemy::SmallCreate));
	unschedule(schedule_selector(LayerEnemy::SmallCreate));
	unschedule(schedule_selector(LayerEnemy::MidCreate));
	unschedule(schedule_selector(LayerEnemy::MidCreate));
	unschedule(schedule_selector(LayerEnemy::BigCreate));
	unschedule(schedule_selector(LayerEnemy::BigCreate));
	unscheduleUpdate();
}

void LayerEnemy::EnemyResume()
{
	schedule(schedule_selector(LayerEnemy::SmallCreate), 0.2f);
	schedule(schedule_selector(LayerEnemy::SmallCreate), 0.3f);
	schedule(schedule_selector(LayerEnemy::SmallCreate), 0.5f);
	schedule(schedule_selector(LayerEnemy::SmallCreate), 1);
	schedule(schedule_selector(LayerEnemy::MidCreate), 3);
	schedule(schedule_selector(LayerEnemy::MidCreate), 5);
	schedule(schedule_selector(LayerEnemy::BigCreate), 8);
	schedule(schedule_selector(LayerEnemy::BigCreate), 15);
	scheduleUpdate();
}

void LayerEnemy::GameNewStart()
{
}