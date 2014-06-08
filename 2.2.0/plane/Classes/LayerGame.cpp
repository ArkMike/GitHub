#include "LayerGame.h"
//#include "proj.win32\LayerUI.h"
#include "LayerUI.h"
#include "SceneOver.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

LayerGame::LayerGame(void)
{
	//CCLog("LayerGame::LayerGame()");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist", "shoot.png");
	isGamePause = false;
}

LayerGame::~LayerGame(void)
{
	//CCLog("LayerGame::~LayerGame()");
}

LayerGame* LayerGame::shared = NULL;

LayerGame* LayerGame::getLayerGame()
{
	shared == NULL ? shared = LayerGame::create() : shared ;
	return shared;
}

bool LayerGame::init()
{
	//CCLog("LayerGame::init()");
	if(!CCLayer::init())	return false;

	bulletLayer = LayerBullet::create();
	addChild(bulletLayer);

	enemyLayer = LayerEnemy::create();
	addChild(enemyLayer);

	propLayer = LayerProp::create();
	addChild(propLayer);

	plane = PlayerPlane::createPlaneWithName("hero1.png");
	plane->setPosition(ccp(getSize().width/2, 100));
	addChild(plane);

	setKeypadEnabled(true);
	scheduleUpdate();
	setTouchEnabled(true);
	return true;
}

CCSize LayerGame::getSize()
{
	return CCDirector::sharedDirector()->getWinSize();
}

void LayerGame::update(float dt)
{
	if(plane->getPositionX() <= plane->getContentSize().width/2)
		plane->setPositionX(plane->getContentSize().width/2);
	if(plane->getPositionX() >= getSize().width-plane->getContentSize().width/2)
		plane->setPositionX(getSize().width-plane->getContentSize().width/2);
	if(plane->getPositionY() <= plane->getContentSize().height/2)
		plane->setPositionY(plane->getContentSize().height/2);
	if(plane->getPositionY() >= getSize().height-plane->getContentSize().height/2)
		plane->setPositionY(getSize().height-plane->getContentSize().height/2);
	
	//if(plane->getPositionX() <= plane->getPlane().size.width/2)
	//	plane->setPositionX(plane->getPlane().size.width/2);
	//if(plane->getPositionX() >= getSize().width - plane->getPlane().size.width/2)
	//	plane->setPositionX(getSize().width - plane->getPlane().size.width/2);
	//if(plane->getPositionY() <= plane->getPlane().size.height/2)
	//	plane->setPositionY(plane->getPlane().size.height/2);
	//if(plane->getPositionY() >= getSize().height - plane->getPlane().size.height/2)
	//	plane->setPositionY(getSize().height - plane->getPlane().size.height/2);

	BulletSmall();
	BulletMiD();
	BulletBig();
	PropPlayer();
	PlayerBomb();
}

void LayerGame::onEnter()
{
	CCLayer::onEnter();
	plane->Reset();
	LayerUI::getLayerUIShared()->Reset();
}

void LayerGame::onExit()
{
	CCLayer::onExit();
	enemyLayer->CleanAllEnemies();
	bulletLayer->RemoveAll();
}

void LayerGame::BulletSmall()
{
	// all bullets
	for(int i=0; i < bulletLayer->bulletArray->count(); i++)
	{
		CCSprite *bullet = (CCSprite*)bulletLayer->bulletArray->objectAtIndex(i);
		if(bullet != NULL)
		{
			// small enemies
			for(int j=0; j < enemyLayer->smallArray->count(); j++)
			{
				EnemySmall *enemy = (EnemySmall*)enemyLayer->smallArray->objectAtIndex(j);
				if(enemy != NULL)
				{
					if(bullet->boundingBox().intersectsRect(enemy->boundingBox())
						&& enemy->GetHP() > 0)
					{
						enemy->LoseHP();
						bulletLayer->RemoveBullet(bullet);
						if(enemy->GetHP() <= 0)
						{
							// update score, then destroy the enemy
							LayerUI::getLayerUIShared()->AddScore(enemy->GetScore());
							enemyLayer->SmallBomb(enemy);
							SimpleAudioEngine::sharedEngine()->playEffect("enemy1_down.mp3");
						break;
						}
					}
				}// check enemy
			}// small enemies
		}// check bullet
	}// all bullets
}

void LayerGame::BulletMiD()
{
	// all bullets
	for(int i=0; i<bulletLayer->bulletArray->count(); i++)
	{
		CCSprite *bullet = (CCSprite*)bulletLayer->bulletArray->objectAtIndex(i);
		if(bullet != NULL)
		{
			// mid enemies
			for(int j=0; j<enemyLayer->midArray->count(); j++)
			{
				EnemyMid *enemy = (EnemyMid*)enemyLayer->midArray->objectAtIndex(j);
				if(enemy != NULL)
				{
					if(bullet->boundingBox().intersectsRect(enemy->boundingBox())
						&& enemy->GetHP() > 0)
					{
						enemy->LoseHP();
						bulletLayer->RemoveBullet(bullet);
						if(enemy->GetHP() <= 0)
						{
							// update score, then destroy the enemy
							LayerUI::getLayerUIShared()->AddScore(enemy->GetScore());
							enemyLayer->MidBomb(enemy);
							SimpleAudioEngine::sharedEngine()->playEffect("enemy2_down.mp3");
						break;
						}
					}
				}// check enemy
			}// mid enemies
		}// check bullet
	}// all bullets
}

void LayerGame::BulletBig()
{
	// all bullets
	for(int i=0; i<bulletLayer->bulletArray->count(); i++)
	{
		CCSprite *bullet = (CCSprite*)bulletLayer->bulletArray->objectAtIndex(i);
		if(bullet != NULL)
		{
			// big enemies
			for(int j=0; j<enemyLayer->bigArray->count(); j++)
			{
				EnemyBig *enemy = (EnemyBig*)enemyLayer->bigArray->objectAtIndex(j);
				if(enemy != NULL)
				{
					if(bullet->boundingBox().intersectsRect(enemy->boundingBox())
						&& enemy->GetHP() > 0)
					{
						enemy->LoseHP();
						bulletLayer->RemoveBullet(bullet);
						if(enemy->GetHP() <= 0)
						{
							// update score, then destroy the enemy
							LayerUI::getLayerUIShared()->AddScore(enemy->GetScore());
							enemyLayer->BigBomb(enemy);
							SimpleAudioEngine::sharedEngine()->playEffect("enemy3_down.mp3");
						break;
						}
					}
				}// check enemy
			}// big enemies
		}// check bullet
	}// all bullets
}

void LayerGame::PropPlayer()
{
	for(int i=0; i<propLayer->propArray->count(); i++)
	{
		CCSprite *prop = (CCSprite*)propLayer->propArray->objectAtIndex(i);
		if(prop->boundingBox().intersectsRect(plane->boundingBox())
			&& plane->isLive)
		{
			if(prop->getTag() == 11)
			{
				bulletLayer->DoubleStart();
				bulletLayer->SingleStop();
				bulletLayer->SingleStart(3);
				SimpleAudioEngine::sharedEngine()->playEffect("get_double_laser.mp3");
			}
			else if(prop->getTag() == 12)
			{
				LayerUI::getLayerUIShared()->AddBombCount(1);
				SimpleAudioEngine::sharedEngine()->playEffect("get_bomb.mp3");
			}
			propLayer->RemoveProp(prop);
		}
	}
}

void LayerGame::PlayerBomb()
{
	// small enemies
	for(int i=0; i<enemyLayer->smallArray->count(); i++)
	{
		EnemySmall *enemy = (EnemySmall*)enemyLayer->smallArray->objectAtIndex(i);
		if(enemy->boundingBox().intersectsRect(plane->boundingBox())
			&& plane->isLive)
		{
			// Íæ¼ÒËÀÁË
			//CCLog("player is dead with small");
			plane->PlaneFall();
				SimpleAudioEngine::sharedEngine()->playEffect("game_over.mp3");
			//removeChild(plane);
			break;
		}
	}

	// mid enemies
	for(int i=0; i<enemyLayer->midArray->count(); i++)
	{
		EnemyMid *enemy = (EnemyMid*)enemyLayer->midArray->objectAtIndex(i);
		if(enemy->boundingBox().intersectsRect(plane->boundingBox())
			&& plane->isLive)
		{
			//CCLog("player is dead with mid");
			plane->PlaneFall();
				SimpleAudioEngine::sharedEngine()->playEffect("game_over.mp3");
			//removeChild(plane);
			break;
		}
	}

	// big enemies 
	for(int i=0; i<enemyLayer->bigArray->count(); i++)
	{
		EnemyBig *enemy = (EnemyBig*)enemyLayer->bigArray->objectAtIndex(i);
		if(enemy->boundingBox().intersectsRect(plane->boundingBox())
			&& plane->isLive)
		{
			//CCLog("player is dead with big");
			plane->PlaneFall();
				SimpleAudioEngine::sharedEngine()->playEffect("game_over.mp3");
			//removeChild(plane);
			break;
		}
	}

}

void LayerGame::BombSkill(CCObject *psender)
{
	//CCLog("all enemies clear.");
	if(LayerUI::getLayerUIShared()->GetBombNum() >= 1)
	{
		LayerUI::getLayerUIShared()->AddBombCount(-1);
		enemyLayer->CleanAllEnemies();
				SimpleAudioEngine::sharedEngine()->playEffect("use_bomb.mp3");
	}
}

void LayerGame::GamePause()
{
	isGamePause = !isGamePause;
}

void LayerGame::GameOver()
{
	SceneOver *over = SceneOver::create();
	CCTransitionMoveInT *nextScene = CCTransitionMoveInT::create(0.8f, over);
	CCDirector::sharedDirector()->pushScene(nextScene);
	over->SetCurrentScore(LayerUI::getLayerUIShared()->GetTotalScore());
}

void LayerGame::keyBackClicked()
{
	//CCLog("key back clicked in game layer");
	onExit();
	CCDirector::sharedDirector()->end();
}

void LayerGame::keyMenuClicked()
{
	//CCLog("key menu clicked in game layer");
}

bool LayerGame::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//CCLog("LayerGame::ccTouchBegan()");
	beginPos = pTouch->getLocationInView();
	beginPos = CCDirector::sharedDirector()->convertToUI(beginPos);

	if(plane->boundingBox().containsPoint(beginPos) && !isGamePause)
	{
		plane->isMove = true;
		offPos.x = beginPos.x - plane->getPositionX();
		offPos.y = beginPos.y - plane->getPositionY();
		//return true;
	}
	 //return false;
	return true;
}

void LayerGame::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touch = pTouch->getLocationInView();
	touch = CCDirector::sharedDirector()->convertToUI(touch);
	if(plane->isMove)
	{
		plane->setPosition(ccp(touch.x - offPos.x, touch.y - offPos.y));
	}
}

void LayerGame::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	//CCLog("LayerGame::ccTouchEnded()");
	plane->isMove = !plane->isMove;
	offPos.setPoint(0, 0);
}

void LayerGame::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}