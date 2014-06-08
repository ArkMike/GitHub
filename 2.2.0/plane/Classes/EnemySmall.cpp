#include "EnemySmall.h"


EnemySmall::EnemySmall(void)
{
	HP = 1;
	score = 10;
	speed = rand()%5 + 5;
	//scheduleUpdate();
}


EnemySmall::~EnemySmall(void)
{
}

EnemySmall* EnemySmall::createSmall(const char* psname)
{
	EnemySmall *smallenemy = new EnemySmall();
	smallenemy->initWithSpriteFrameName(psname);
	smallenemy->autorelease();
	return smallenemy;
}

void EnemySmall::update(float dt)
{
	if(GetHP() > 0)
		setPositionY(getPositionY() - speed * 50 * dt);
}

void EnemySmall::LoseHP()
{
	HP -= 1;
}

int EnemySmall::GetHP()
{
	return HP;
}

int EnemySmall::GetScore()
{
	return score;
}