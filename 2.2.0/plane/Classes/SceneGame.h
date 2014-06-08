#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
USING_NS_CC;

//#include "proj.win32\LayerGround.h"
//#include "proj.win32\LayerGame.h"
//#include "proj.win32\LayerUI.h"
#include "LayerGround.h"
#include "LayerGame.h"
#include "LayerUI.h"

class SceneGame :
	public CCScene
{
public:
	SceneGame(void);
	~SceneGame(void);

	bool init();
	CREATE_FUNC(SceneGame);
	static CCScene* getGame();
	CCSize getSize();

	void onEnter();
	void onExit();

	void GamePause(CCObject *obj);
	void GameResume(CCObject *obj);
	void GameControl(CCObject *obj);

private :
	LayerGround *groundLayer;
	LayerGame *gameLayer;
	LayerUI *uiLayer;

	CCMenuItemImage *pause, *resume;
};

#endif