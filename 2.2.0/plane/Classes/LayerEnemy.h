#ifndef _LAYERENEMY_H_
#define _LAYERENEMY_H_

#include "cocos2d.h"
USING_NS_CC;
//#include "proj.win32\EnemySmall.h"
//#include "proj.win32\EnemyMid.h"
//#include "proj.win32\EnemyBig.h"
#include "EnemySmall.h"
#include "EnemyMid.h"
#include "EnemyBig.h"

class LayerEnemy :
	public CCLayer
{
public:
	LayerEnemy(void);
	~LayerEnemy(void);

	bool init();
	CREATE_FUNC(LayerEnemy);
	void update(float dt);

	// small
	void SmallCreate(float dt);
	void SmallNative(CCSprite *psender);
	void SmallBomb(EnemySmall *enemy);
	void SmallRemove(CCNode *psender, void *date);
	void SmallArray(CCSprite *psender);

	// mid
	void MidCreate(float dt);
	void MidNative(CCSprite *psender);
	void MidBomb(EnemyMid *enemy);
	void MidRemove(CCNode *psender, void *date);
	void MidArray(CCSprite *psender);

	// big
	void BigCreate(float dt);
	void BigNative(CCSprite *psender);
	void BigBomb(EnemyBig *enemy);
	void BigRemove(CCNode *psender, void *date);
	void BigArray(CCSprite *psender);

	// remove the enemy from batch
	void EnemyBatch(CCSprite *psender);

	// clear all enemies
	void CleanSmall();
	void CleanMid();
	void CleanBig();
	void CleanAllEnemies();

	void EnemyPause();
	void EnemyResume();

	void GameNewStart();

	CCSpriteBatchNode *enemyBatch;
	CCArray *smallArray;
	CCArray *midArray;
	CCArray *bigArray;
	//CCArray *smallArray = CCArray::create();
	//CCArray *midArray = CCArray::create();
	//CCArray *bigArray = CCArray::create();
};

#endif