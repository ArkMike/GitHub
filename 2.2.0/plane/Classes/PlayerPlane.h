#ifndef _PLAYERPLANE_H_
#define _PLAYERPLANE_H_

#include "cocos2d.h"
USING_NS_CC;

class PlayerPlane :
	public CCSprite
{
public:
	PlayerPlane(void);
	~PlayerPlane(void);

	static PlayerPlane* createPlaneWithName(const char *psname);
	void initPlaneWithName(const char *psname);

	void onEnter();
	void onExit();

	void PlaneFall();
	void Reset();

	static PlayerPlane *sharedPlane;
	bool isMove, isLive;
};

#endif