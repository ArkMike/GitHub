#ifndef _LAYERUI_H_
#define _LAYERUI_H_

#include "cocos2d.h"
USING_NS_CC;
//#include "proj.win32\LayerGame.h"
#include "LayerGame.h"

class LayerUI :
	public CCLayer
{
public:
	LayerUI(void);
	~LayerUI(void);

	static LayerUI* getLayerUIShared();
	bool init();
	CREATE_FUNC(LayerUI);

	void AddBombCount(int count);
	int GetBombNum();

	void AddScore(int enmeyScore);
	int GetTotalScore();

	void Reset();

private :
	static LayerUI *shared;
	int bombNum, totalScore;

	//CCMenuItemImage *pause, *resume;
	//CCMenuItemToggle *gamepause;

	CCMenuItemImage *bombButton;
	CCMenu *menu;
	CCLabelBMFont *bombLable, *scoreLable;
};

#endif