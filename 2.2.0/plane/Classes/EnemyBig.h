#ifndef _ENEMYBIG_H_
#define _ENEMYBIG_H_

#include "cocos2d.h"
USING_NS_CC;

class EnemyBig :
	public CCSprite
{
public:
	EnemyBig(void);
	~EnemyBig(void);

	static EnemyBig* createBig(const char* psname);
	void BigFly();
	void update(float dt);
	void LoseHP();
	int GetHP();
	int GetScore();

private :
	int HP, score, speed;
};

#endif