#include "EnemyBig.h"


EnemyBig::EnemyBig(void)
{
	HP = 6;
	score = 100;
	speed = rand()%4 + 3;
	//scheduleUpdate();
}


EnemyBig::~EnemyBig(void)
{
}

EnemyBig* EnemyBig::createBig(const char* psname)
{
	EnemyBig *big = new EnemyBig();
	big->initWithSpriteFrameName(psname);
	big->BigFly();
	big->autorelease();
	return big;
}

void EnemyBig::BigFly()
{
	CCAnimation *fly = CCAnimation::create();
	fly->setDelayPerUnit(0.15f);
	fly->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png"));
	fly->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png"));
	runAction(CCRepeatForever::create(CCAnimate::create(fly)));
}

void EnemyBig::update(float dt)
{
	if(GetHP() > 0)
		setPositionY(getPositionY() - speed * 50 * dt);
}

void EnemyBig::LoseHP()
{
	HP -= 1;
}

int EnemyBig::GetHP()
{
	return HP;
}

int EnemyBig::GetScore()
{
	return score;
}