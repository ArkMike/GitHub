#ifndef _LAYERMENU_H_
#define _LAYERMENU_H_

#include "cocos2d.h"
USING_NS_CC;

//#include "proj.win32\SceneGame.h"
#include "SceneGame.h"

class LayerMenu :
	public CCLayer
{
public:
	LayerMenu(void);
	~LayerMenu(void);

	bool init();
	CREATE_FUNC(LayerMenu);

	CCSize getSize();
	void nextScene(CCNode *node);

private :
	CCSprite *background ;
	CCSprite *title;
	CCSprite *loading;
};

#endif