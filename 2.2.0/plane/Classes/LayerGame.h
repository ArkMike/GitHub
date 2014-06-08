#ifndef _LAYERGAME_H_
#define _LAYERGAME_H_

#include "cocos2d.h"
USING_NS_CC;
//#include "proj.win32\LayerBullet.h"
//#include "proj.win32\LayerEnemy.h"
//#include "proj.win32\LayerProp.h"
//#include "proj.win32\PlayerPlane.h"
#include "LayerBullet.h"
#include "LayerEnemy.h"
#include "LayerProp.h"
#include "PlayerPlane.h"

class LayerGame :
	public CCLayer
{
public:
	LayerGame(void);
	~LayerGame(void);
	static LayerGame* getLayerGame();
	bool init();
	CREATE_FUNC(LayerGame);

	CCSize getSize();
	void update(float dt);
	void onEnter();
	void onExit();

	void BulletSmall();
	void BulletMiD();
	void BulletBig();
	void PropPlayer();
	void PlayerBomb();

	void BombSkill(CCObject *psender);
	void GamePause();
	void GameOver();
	
    void keyBackClicked(void);
    void keyMenuClicked(void);
	
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void registerWithTouchDispatcher(void);

	CCPoint beginPos, endPos, offPos;

	LayerBullet *bulletLayer;
	LayerEnemy *enemyLayer;
	LayerProp *propLayer;
	PlayerPlane *plane;

	bool isGamePause;

private :
	static LayerGame *shared;
};

#endif