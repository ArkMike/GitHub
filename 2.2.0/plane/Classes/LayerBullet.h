#ifndef _LAYERBULLET_H_
#define _LAYERBULLET_H_

#include "cocos2d.h"
USING_NS_CC;

class LayerBullet :
	public CCLayer
{
public:
	LayerBullet(void);
	~LayerBullet(void);

	bool init();
	CREATE_FUNC(LayerBullet);
	void update(float dt);

	// single bullet
	void SingleStart(float delay);
	void SingleLaunch(float dt);
	void SingleStop();

	// double bullets
	void DoubleStart();
	void DoubleLaunch(float dt);
	void DoubleStop();

	void RemoveBullet(CCSprite *psender);
	void RemoveAll();

	void BulletPause();
	void BulletResume();

	CCSpriteBatchNode *bulletBatch;
	CCArray *bulletArray;

private :
	bool fire;
};

#endif