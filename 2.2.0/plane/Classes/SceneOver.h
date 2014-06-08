#ifndef _SCENEOVER_H_
#define _SCENEOVER_H_

#include "cocos2d.h"
USING_NS_CC;

class SceneOver :
	public CCScene
{
public:
	SceneOver(void);
	~SceneOver(void);

	bool init();
	CREATE_FUNC(SceneOver);
	CCSize getSize();
	static CCScene* getOver();

	void BackToGame(CCObject *obj);

	void SetCurrentScore(int _score);
	void SetNewHighest(int _high);

	CCLabelBMFont *currentScore, *highestScore;
	int current;

	static int hightest_current;
};

#endif