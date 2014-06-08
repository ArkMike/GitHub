#include "SceneOver.h"
#include "SceneGame.h"

SceneOver::SceneOver(void)
{
}


SceneOver::~SceneOver(void)
{
}

int SceneOver::hightest_current = 0;

bool SceneOver::init()
{
	if(!CCScene::init())	return false;

	CCSprite *temp = CCSprite::create("icon.png");
	temp->setPosition(ccp(getSize().width/2, getSize().height/2));
	addChild(temp);

	// back ground
	CCSprite *background = CCSprite::createWithSpriteFrameName("gameover.png");
	background->setAnchorPoint(CCPointZero);
	background->setPosition(CCPointZero);
	addChild(background);

	// current score
	currentScore = CCLabelBMFont::create("0", "test1.fnt");
	currentScore->setColor(ccc3(143,146,147));
	currentScore->setScale(2);
	currentScore->setPosition(ccp(getSize().width/2, getSize().height/2));
	addChild(currentScore);

	// highest score
	CCString *str = CCString::createWithFormat("%d", hightest_current);
	highestScore = CCLabelBMFont::create(str->m_sString.c_str(), "test1.fnt");
	highestScore->setColor(ccc3(143,146,147));
	highestScore->setAnchorPoint(ccp(0, 0.5f));
	highestScore->setScale(2);
	highestScore->setPosition(ccp(150, getSize().height*0.94f));
	addChild(highestScore);

	//if(current > hightest_current)
	//{
	//	CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore", current);
	//	hightest_current = current;
	//	SetNewHighest(hightest_current);
	//}

	// back menu
	CCSprite *nor = CCSprite::createWithSpriteFrameName("btn_finish.png");
	CCSprite *pres = CCSprite::createWithSpriteFrameName("btn_finish.png");
	CCMenuItemImage *back = CCMenuItemImage::create();
	back->initWithNormalSprite(nor, pres, NULL, this, menu_selector(SceneOver::BackToGame));
	back->setPosition(getSize().width/5, getSize().height/16);
	
	CCMenu *main = CCMenu::create(back, NULL);
	main->setPosition(CCPointZero);
	addChild(main);

	return true;
}

CCSize SceneOver::getSize()
{
	return CCDirector::sharedDirector()->getWinSize();
}

CCScene* SceneOver::getOver()
{
	CCScene *scene = CCScene::create();
	SceneOver *over = SceneOver::create();
	scene->addChild(over);
	return scene;
}

void SceneOver::BackToGame(CCObject *obj)
{
	//CCLog("back to game");
	//CCTransitionMoveInL *nextScene = CCTransitionMoveInL::create(0.8f, SceneGame::getGame());
	//CCDirector::sharedDirector()->replaceScene(nextScene);
	CCDirector::sharedDirector()->popScene();
	//CCDirector::sharedDirector()->end();
}

void SceneOver::SetCurrentScore(int _score)
{
	current = _score;
	CCString *str = CCString::createWithFormat("%d", _score);
	currentScore->setString(str->m_sString.c_str());

	if(current > hightest_current)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighScore", current);
		hightest_current = current;
		SetNewHighest(hightest_current);
	}
}

void SceneOver::SetNewHighest(int _high)
{
	CCString *str = CCString::createWithFormat("%d", _high); 
	highestScore->setString(str->m_sString.c_str());
}