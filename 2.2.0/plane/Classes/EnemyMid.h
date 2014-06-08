#ifndef _ENEMYMID_H_
#define _ENEMYMID_H_

#include "cocos2d.h"
USING_NS_CC;

class EnemyMid :
	public CCSprite
{
public:
	EnemyMid(void);
	~EnemyMid(void);

	static EnemyMid* createMid(const char* psname);
	void update(float dt);
	void LoseHP();
	int GetHP();
	int GetScore();

private :
	int HP, score, speed;
};

#endif