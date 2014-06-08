#ifndef _LAYERGROUND_H_
#define _LAYERGROUND_H_

#include "cocos2d.h"
USING_NS_CC;

class LayerGround :
	public CCLayer
{
public:
	LayerGround(void);
	~LayerGround(void);

	bool init();
	CREATE_FUNC(LayerGround);

	void update(float dt);

private :
	CCSprite *back1, *back2;
};

#endif