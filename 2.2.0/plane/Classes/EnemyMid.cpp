#include "EnemyMid.h"


EnemyMid::EnemyMid(void)
{
	HP = 3;
	score = 30;
	speed = rand()%5 + 4;
	//scheduleUpdate();
}


EnemyMid::~EnemyMid(void)
{
}

EnemyMid* EnemyMid::createMid(const char* psname)
{
	EnemyMid *mid = new EnemyMid();
	mid->initWithSpriteFrameName(psname);
	mid->autorelease();
	return mid;
}

void EnemyMid::update(float dt)
{
	if(GetHP() > 0)
		setPositionY(getPositionY() - speed * 50 * dt);
}
void EnemyMid::LoseHP()
{
	HP -= 1;
}

int EnemyMid::GetHP()
{
	return HP;
}

int EnemyMid::GetScore()
{
	return score;
}