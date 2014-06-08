#include "LayerUI.h"
//#include "proj.win32\LayerGame.h"
#include "LayerGame.h"

LayerUI::LayerUI(void)
{
	bombNum = 0;
	totalScore = 0;
}


LayerUI::~LayerUI(void)
{
}

LayerUI* LayerUI::shared = NULL;

LayerUI* LayerUI::getLayerUIShared()
{
	shared == NULL ? shared = LayerUI::create() : shared;
	return shared;
}

bool LayerUI::init()
{
	if(!CCLayer::init())	return false;

	//// 暂停按钮
	//CCSprite *paNor = CCSprite::createWithSpriteFrameName("game_pause_nor.png");
	//CCSprite *paPre = CCSprite::createWithSpriteFrameName("game_pause_pressed.png");
	//pause = CCMenuItemImage::create();
	//pause->initWithNormalSprite(paNor, paPre, NULL, 
	//	SceneGame::getGame(), menu_selector(SceneGame::GamePause));
	//pause->setPosition(ccp(20, 820));

	//CCSprite *reNor = CCSprite::createWithSpriteFrameName("game_resume_nor.png");
	//CCSprite *rePre = CCSprite::createWithSpriteFrameName("game_resume_pressed.png");
	//resume = CCMenuItemImage::create();
	//resume->initWithNormalSprite(reNor, rePre, NULL, 
	//	SceneGame::getGame(), menu_selector(SceneGame::GamePause));
	//resume->setPosition(ccp(20, 820));

	//gamepause = CCMenuItemToggle::createWithTarget(SceneGame::getGame(),
	//	menu_selector(SceneGame::GamePause), pause, resume, NULL);
	//gamepause->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/10,
	//	CCDirector::sharedDirector()->getWinSize().height*0.95f));

	CCSprite *nor = CCSprite::createWithSpriteFrameName("bomb.png");
	bombButton = CCMenuItemImage::create();
	bombButton->initWithNormalSprite(nor, nor, NULL, LayerGame::getLayerGame(),
		menu_selector(LayerGame::BombSkill));
	bombButton->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/10,
		CCDirector::sharedDirector()->getWinSize().height/16));

	menu = CCMenu::create(/*gamepause, */bombButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	// 炸弹数字
	CCString *bombStr = CCString::createWithFormat("x%d", bombNum);
	bombLable = CCLabelBMFont::create(bombStr->m_sString.c_str(), "test1.fnt");
	bombLable->setColor(ccc3(143,146,147));
	bombLable->setAnchorPoint(ccp(0, 0.5f));
	bombLable->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/6,
		CCDirector::sharedDirector()->getWinSize().height/16));
	addChild(bombLable);

	// 分数
	CCString *scoreStr = CCString::createWithFormat("%d", totalScore);
	scoreLable = CCLabelBMFont::create(scoreStr->m_sString.c_str(), "test1.fnt");
	scoreLable->setColor(ccc3(143,146,147));
	scoreLable->setAnchorPoint(ccp(0, 0.5f));
	scoreLable->setScale(2);
	scoreLable->setPosition(ccp(80, CCDirector::sharedDirector()->getWinSize().height*0.95f));
	addChild(scoreLable);

	return true;
}

void LayerUI::AddBombCount(int count)
{
	bombNum += count;
	CCString *str = CCString::createWithFormat("x%d", bombNum); 
	bombLable->setString(str->m_sString.c_str());
}

int LayerUI::GetBombNum()
{
	return bombNum;
}

void LayerUI::AddScore(int enemyScore)
{
	totalScore += enemyScore;
	CCString *str = CCString::createWithFormat("%d", totalScore);
	scoreLable->setString(str->m_sString.c_str());
}

int LayerUI::GetTotalScore()
{
	return totalScore;
}

void LayerUI::Reset()
{
	bombNum = 0;
	totalScore = 0;
	AddScore(totalScore);
	AddBombCount(bombNum);
}