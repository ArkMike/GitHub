#ifndef _ENEMYSMALL_H_
#define _ENEMYSMALL_H_

#include "cocos2d.h"
USING_NS_CC;

class EnemySmall :
	public CCSprite
{
public:
	EnemySmall(void);
	~EnemySmall(void);

	static EnemySmall* createSmall(const char* psname);
	void update(float dt);
	void LoseHP();
	int GetHP();
	int GetScore();

private :
	int HP, score, speed;
};

#endif