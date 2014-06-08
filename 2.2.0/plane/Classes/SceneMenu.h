#ifndef _SCENEMENU_H_
#define _SCENEMENU_H_

#include "cocos2d.h"
USING_NS_CC;

//#include "proj.win32\LayerMenu.h"
#include "LayerMenu.h"

class SceneMenu :
	public CCScene
{
public:
	SceneMenu(void);
	~SceneMenu(void);

	bool init();
	CREATE_FUNC(SceneMenu);
	static CCScene* getMenu();

	void LoadSound();
	bool isSaveHeight();
	void getHeight();

	LayerMenu *menuLayer;
};

#endif