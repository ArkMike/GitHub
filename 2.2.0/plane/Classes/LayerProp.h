#ifndef _LAYERPROP_H_
#define _LAYERPROP_H_

#include "cocos2d.h"
USING_NS_CC;

class LayerProp :
	public CCLayer
{
public:
	LayerProp(void);
	~LayerProp(void);

	bool init();
	CREATE_FUNC(LayerProp);

	void update(float dt);
	CCSize getSize();
	void createDouble(float dt);
	void createBomb(float dt);
	void RemoveProp(CCSprite *psender);

	void PropPause();
	void PropResume();

	CCSpriteBatchNode *propBatch;
	CCArray *propArray;
};

#endif