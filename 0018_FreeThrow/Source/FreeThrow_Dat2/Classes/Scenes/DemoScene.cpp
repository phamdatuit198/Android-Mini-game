//
//  DemoScene.cpp
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/10/13.
//
//

#include "DemoScene.h"
#include "BarTimeGame.h"
#include "Ball.h"
#include "Notice.h"
#include "GlobalData.h"
#include "Basket.h"

#include "../NDKHelper/NDKHelper.h"
#define Z_ORDER_BALL 1
#define Z_ORDER_BASKET 2

#define POWER_NUM_NORMAL 5
#define POWER_NUM_DOWN 1
//#define POWER_TIME 2000
#define DemoSceneTag 1500

// Luan added 30/05/2013

#define kDurationShowingTopBanner 3.0f
//-------------------------------

USING_NS_CC;

using namespace cocos2d;
DemoScene::DemoScene() {
	numberOfShoot = 0;
	currentBall = BALL_LEVEL_1;
	numOfBall = GAME_NUMBER_SENCE;
	st = INIT_GAME;
	arrAction = new CCArray();
	arrBasketAction = new CCArray();
	// Luan added 29/05/2013
	arrActionExcellent = new CCArray();
	//--------------------------------
	this->setTouchEnabled(true);

//    noticeBoard = NULL;
}
DemoScene::~DemoScene() {
	delete arrAction;
	delete arrBasketAction;
	delete arrActionExcellent;
}

bool DemoScene::ccTouchBegan(CCTouch* touch, CCEvent* event) {
	switch (st) {
	case INIT_GAME:
		//
		st = START_POWER;
		goF = true;

//            if (noticeBoard != NULL) {
//                noticeBoard->setVisible(false);
//            }
		break;
	case START_POWER:
		//
		goF = false;
		st = SHOOT;
		// TODO tellTarget("/notice")gotoAndStop(2);
//            if (noticeBoard == NULL) {
//                noticeBoard = Notice::create("release2.png");
//                noticeBoard->cocos2d::CCNode::setScale(0.25);
//                noticeBoard->setPosition(ccp(320,100));
//                noticeBoard->setAnchorPoint(ccp(0.5,0.0));
//                this->addChild(noticeBoard);
//            }
//            noticeBoard->setVisible(true);
		this->showingRELEASETopBanner();
		break;
	case SHOOT: {
		numberOfShoot++;
		vecSprite->stopAllActions();
		bar->setVisible(false);
		isDown = false;
		//
		// get angle and velocity
		float angleInRads;

		float vecPositionX = vecSprite->getPositionX()
				- ((size.width / 2) - lineSprite->getContentSize().width / 2);
		float vecPositionY = vecSprite->getPositionY();
		if (vecPositionX <= lineSprite->getContentSize().width / 2) {
			float atan2f = (lineSprite->getContentSize().width / 2
					- vecPositionX) / (ball->getPositionY() - vecPositionY);
			angleInRads = CC_RADIANS_TO_DEGREES(atan2f) + 90;
			CCLOG("DATPV---angleInRads nho = %d", angleInRads);
		} else {
			float atan2f = (vecPositionX
					- lineSprite->getContentSize().width / 2)
					/ (ball->getPositionY() - vecPositionY);
			angleInRads = 90 - CC_RADIANS_TO_DEGREES(atan2f);
			CCLOG("DATPV---angleInRads lon = %d", angleInRads);
		}

		//
		float scaleY = bar->getProgressTime1()->getScaleY();
		CCLOG("%f", scaleY);
		float height = scaleY;

		power = (MAXIMUM_POWER * height / HEIGH_OF_POWER_BAR)
				+ this->getBallWeight(currentBall);

//            //[TEST]
//            power = GOAL_BONUS_POWER_MIN;
//            angleInRads = GOAL_ANGEL_BALL_MIN;
//            //[END]

		exitGameInExtraMode = true;
		//exitGameInExtraMode = false;
		isGoal = false;
		isExelentGoal = false;
		currentThrowBallScore = 0;
//		//DatPV
//		power = 100;
//		angleInRads = 90;
		//fix bug angle for 720-1280
		CCLOG("DATPV---angleInRads begin = %d", angleInRads);
		size = CCDirector::sharedDirector()->getWinSize();
		if (size.width == 720) {
			if (angleInRads >= 75 && angleInRads <= 105)
				angleInRads = 90;
		}

		if (power <= MINIMUM_POWER) {
			power = MINIMUM_POWER;
		} else if (power < MINIMUM_GOAL_POWER) {
			CCLog("OUT OF GOAL, need increase power");
		} else if (power >= MINIMUM_GOAL_POWER && power <= MAXIMUM_GOAL_POWER) {
			if (angleInRads >= GOAL_ANGEL_BALL_MIN
					&& angleInRads <= GOAL_ANGEL_BALL_MAX) {

				//
				exitGameInExtraMode = false;

				CCLog("GOAL");
				isGoal = true;
				if (power >= GOAL_BONUS_POWER_MIN
						&& power <= GOAL_BONUS_POWER_MAX) {
					CCLog("get BONUS");

					gameMode = EXTRA;

					isExelentGoal = true;
					current_Exelent = true;

					if (current_Exelent == true && previous_Exelent == true) {
						numInExelent++;
						// update score
						if (numInExelent == 1) {
//                                currentSenceScore += 2;
							currentThrowBallScore = 2;
						} else {
//                                currentSenceScore += numInExelent*numInExelent;
							currentThrowBallScore = numInExelent * numInExelent;
						}
					} else {
//                            currentSenceScore += 2;
						currentThrowBallScore = 2;
					}
				} else {
					current_Exelent = false;
					numInExelent = 0;
					currentThrowBallScore = 1;
//                        currentSenceScore +=1;
				}
				numberThrowBallGoal++;
			}
			previous_Exelent = current_Exelent;
		} else if (power >= MAXIMUM_GOAL_POWER) {
			CCLog("OUT OF GOAL, need decrease power");
			power = MAXIMUM_POWER;
		}
		//            CCLog("maxTime ------- %f", maxTime);
		CCLog("power ------- %d", power);
		CCLog("angle ------- %f", angleInRads);
		//            CCLog("---------------------");
		//            CCLog("---------------------");
		//
		st = END_GAME;

		if (isExelentGoal)
			ball->throwBall(angleInRads, power, arrActionExcellent);
		else
			ball->throwBall(angleInRads, power, arrAction);
		// tellTarget("/notice")gotoAndStop(3);
//            if (noticeBoard != NULL) {
//                noticeBoard->setVisible(false);
//            }
		break;
	}
//        default:
//            break;
	}

	return true;
}

cocos2d::CCScene* DemoScene::scene() {
	CCScene *scene = CCScene::create();
	DemoScene *layer = DemoScene::create();
	scene->addChild(layer, DemoSceneTag);
	return scene;
}

bool DemoScene::init() {
	//////////////////////////////
	// 1. super init first

	if (!CCLayer::init()) {
		return false;
	}
	// init global data
	currentThrowBallScore = 0;    // game score
	gameScore = 0;
	numberOfShoot = 0;    // number of throw ball
	currentBall = BALL_LEVEL_1;    // current ball index

	previous_Exelent = true;
	current_Exelent = false;
	//
	gameMode = NORMAL;
	exitGameInExtraMode = false;
	ballReset = true;

	numberThrowNormalMode = 0;
	//
	this->registerWithTouchDispatcher();
	// backgroud for iphone 5
	int dy = 0;
//    if (CCDirector::sharedDirector()->getWinSize().height == 1136) {
//        this->drawImageWithLayer("IP5.png", ccp(0,0), ccp(0,0));
//        dy = 176;
//    } else {
	size = CCDirector::sharedDirector()->getWinSize();
	if (size.width == 720)
		this->initPositionLarge(size);
	else
		this->initPositionMedium(size);

	this->drawImageWithLayer("play_background.png", ccp(0, 0), ccp(0, 0));
	// board 605x338pixels
	boardSprite = this->drawImageWithLayer("board_board_03.png",
			ccp(boardX, boardY), ccp(0.5, 0.5)); // board include 1/2 basket

	// init power
	powerSprite = this->drawImageWithLayer("power.png", ccp(PowerX, PowerY),
			ccp(0.5, 0.5));
	lineSprite = this->drawImageWithLayer("vec_line.png",
			ccp(VecLineX, VecLineY), ccp(0.5, 0.5));
	vecSprite = this->drawImageWithLayer("vec.png", ccp(VecX, VecY),
			ccp(0.5, 0.5)); // ---------------------------------------------------------------
	// init basket
	// ---------------------------------------------------------------
	basket = Basket::create("basket/bk1.png");
	basket->setPosition(ccp(BasketX, BasketY));
	basket->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(basket);
	// ---------------------------------------------------------------
	// init ball
	// ---------------------------------------------------------------
	char name[32] = { 0 };

	sprintf(name, "ball/%d/ball%d1.png", currentBall, currentBall); //   ball/1/ball11

	ball = Ball::create(name);
	ball->setPosition(ccp(BeginBallX, BeginBallY));
	ball->setAnchorPoint(ccp(0.5, 0.5));
	if (size.width == 720) {
		ball->setScale(1.5f);
	}
	ball->_root = this;
	this->addChild(ball);

	// ---------------------------------------------------------------
	// init animation for ball and basket
	// ---------------------------------------------------------------
	char pngFileName[32] = { 0 };
	char plistFileName[32] = { 0 };
	sprintf(pngFileName, "ball/%d/ball%d.png", currentBall, currentBall);
	sprintf(plistFileName, "ball/%d/ball%d.plist", currentBall, currentBall);
	this->iCreateAnimation(plistFileName, pngFileName);
	this->iCreateBasketAnimation("basket/bk.plist", "basket/bk.png");

	//
	// ---------------------------------------------------------------
	// animation for vector
	// ---------------------------------------------------------------
	//
	char pngExcellentFileName[32] = { 0 };
	char plistExcellentFileName[32] = { 0 };
	sprintf(pngExcellentFileName, "ballEx/%d/ballE%d.png", currentBall,
			currentBall);
	sprintf(plistExcellentFileName, "ballEx/%d/ballE%d.plist", currentBall,
			currentBall);
	this->iCreateExcellentAnimation(plistExcellentFileName,
			pngExcellentFileName);
	//----------------------------------------------------------------------------

//    vecSprite->setPositionX(xleft);

	setVecSprite();

	// init progress bar
	CCLog("DatPV bar");
	bar = BarTimeGameLayer::create();
	bar->setTag(10);
	bar->setPosition(ccp(barX, barY));
	bar->setContentSize(CCSizeMake(22, HEIGH_OF_POWER_BAR));
	this->addChild(bar);
	this->schedule(schedule_selector(DemoScene::updateProgressBar), 0.05);

	// score lable
	senseLbl = CCLabelTTF::create("0/5", "HGRPP1_0.ttf", sizeText);
	senseLbl->setColor(ccBLACK);
	senseLbl->setPosition(ccp(scoreLableX, scoreLableY));
	senseLbl->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(senseLbl);

	// sense lable
	scoreLbl = CCLabelTTF::create("0", "HGRPP1_0.ttf", sizeText);
	scoreLbl->setColor(ccBLACK);
	scoreLbl->setPosition(ccp(50, scoreLableY));
	this->addChild(scoreLbl);

//    this->scheduleUpdate();
	this->schedule(schedule_selector(DemoScene::updateGame));
	//

	return true;
}

// SET POSITION
void DemoScene::initPositionMedium(CCSize size) {
	BeginBallX = size.width / 2;
	BeginBallY = size.height / 8 + 120;

	BasketX = size.width / 2;
	BasketY = size.height / 2 + 52;

	PowerX = size.width - 40;
	PowerY = size.height / 4;

	VecLineX = size.width / 2;
	VecLineY = size.height / 8 - 40;

	VecX = VecLineX;
	VecY = VecLineY - 10;

	scoreLableX = size.width - 60;
	scoreLableY = size.height / 2 + size.height / 3 + 20;

	boardX = size.width / 2;
	boardY = size.height / 2 + (size.height / 2) / 3 - 23;

	sizeText = 38;

	kInSpriteX = 520;
	kInSpriteY = 685;

	barX = PowerX + 2;
	barY = 99;

	widthBar = 23;

//	HEIGH_OF_POWER_BAR = 200;
//
//
//	MINIMUM_GOAL_POWER = 87.0f;
//	MAXIMUM_GOAL_POWER = 110.0f;
//
//	GOAL_BONUS_POWER_MAX = 105.0f;
//	GOAL_BONUS_POWER_MIN = 97.0f;

}

void DemoScene::initPositionLarge(CCSize size) {
	BeginBallX = size.width / 2;
	BeginBallY = size.height / 8 + 120;

	BasketX = size.width / 2;
	BasketY = size.height / 2 + 75;

	PowerX = size.width - 60;
	PowerY = size.height / 4;

	VecLineX = size.width / 2;
	VecLineY = size.height / 8 - 50;

	VecX = VecLineX;
	VecY = VecLineY - 12;

	scoreLableX = size.width - 60;
	scoreLableY = size.height / 2 + size.height / 3 + 40;

	boardX = size.width / 2;
	boardY = size.height / 2 + (size.height / 2) / 3 - 33;

	sizeText = 50;

	kInSpriteX = 520;
	kInSpriteY = 1116;

	barX = PowerX + 4;
	barY = 166;

	widthBar = 23;
	HEIGH_OF_POWER_BAR = 300;

	MINIMUM_GOAL_POWER = 110.0f;
	MAXIMUM_GOAL_POWER = 130.0f;

	GOAL_BONUS_POWER_MAX = 125.0f;
	GOAL_BONUS_POWER_MIN = 117.0f;

}

void DemoScene::updateGame(int dt) {
//    CCLOG("log = %f, %f",ball->getPositionX(), ball->getPositionY());
	float topBoardY = boardSprite->getPositionY()
			+ boardSprite->getContentSize().height;
	topBoardY += (ball->getContentSize().height / 2);
	if (ballReset && ball->getPositionY() > topBoardY) {
		ball->stopMoveball();
		ballReset = false;

	}
}
/**
 * update progressbar
 */
void DemoScene::updateProgressBar() {
	if (goF) {
		if (!isDown) {
			BarTimeGameLayer *bar = (BarTimeGameLayer *) this->getChildByTag(
					10);
			bar->changeProgressTime(POWER_NUM_NORMAL);
			if (bar->getProgressTime1()->getScaleY() >= HEIGH_OF_POWER_BAR) {
				isDown = true;
			}
		} else {
			BarTimeGameLayer *bar = (BarTimeGameLayer *) this->getChildByTag(
					10);
			bar->changeProgressTime(-POWER_NUM_NORMAL);
			if (bar->getProgressTime1()->getScaleY() <= 1) {
				isDown = false;
			}
		}
	} else {
		// decrease progress bar to 0
		BarTimeGameLayer *bar = (BarTimeGameLayer *) this->getChildByTag(10);
		if (bar->getProgressTime1()->getScaleY() <= 1.0f) {
			return;
		}
		bar->changeProgressTime(-POWER_NUM_DOWN);
	}
	//update color for power
	float scaleY = bar->getProgressTime1()->getScaleY();
	// change image
	int temp = (scaleY * MAXIMUM_POWER) / HEIGH_OF_POWER_BAR
			+ this->getBallWeight(currentBall);

	if (temp > MAXIMUM_GOAL_POWER || temp < MINIMUM_GOAL_POWER) {
		bar->getProgressTime1()->setTexture(
				CCTextureCache::sharedTextureCache()->addImage(
						"power/red_pixel.png"));
	} else {
		if (temp <= GOAL_BONUS_POWER_MAX && temp >= GOAL_BONUS_POWER_MIN) {
			bar->getProgressTime1()->setTexture(
					CCTextureCache::sharedTextureCache()->addImage(
							"power/green_pixel.png"));
		} else {
			bar->getProgressTime1()->setTexture(
					CCTextureCache::sharedTextureCache()->addImage(
							"power/blue_pixel.png"));
		}
	}
}

void DemoScene::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
			this, 0, true);
}

cocos2d::CCSpriteBatchNode* DemoScene::iCreateAnimation(const char *plistFile,
		const char *pngFile) {
//    cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFile);
//    CCSpriteBatchNode* spreetsheet = CCSpriteBatchNode::create(pngFile);
//    
//    char initFileName[32] = {0};
//    sprintf(initFileName, "ball%d1.png",currentBall);
//    Ball *ballObj = (Ball *)cocos2d::CCSprite::createWithSpriteFrameName(initFileName);
//    
//    ballObj->setPosition(ccp(320,220));
//    ballObj->setAnchorPoint(ccp(0.5,0.5));
//    
//    spreetsheet->addChild(ballObj);

	if (arrAction != NULL) {
		arrAction->removeAllObjects();
	}

	for (int i = 1; i <= 9; i++) {
		char name[32] = { 0 };
		sprintf(name, "ball/%d/ball%d%d.png", currentBall, currentBall, i);

		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(
				name);
		CCRect rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTexture,
				rect);
		arrAction->addObject(pFrame);

	}
	return NULL;
//    return spreetsheet;
}

// Luan added 29/05/2013
cocos2d::CCSpriteBatchNode* DemoScene::iCreateExcellentAnimation(
		const char *plistFile, const char *pngFile) {
//    cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFile);
//    CCSpriteBatchNode* spreetsheet = CCSpriteBatchNode::create(pngFile);
//    
//    char initFileName[32] = {0};
//    sprintf(initFileName, "ballE%d1.png",currentBall);
//    Ball *ballObj = (Ball *)cocos2d::CCSprite::createWithSpriteFrameName(initFileName);
//    
//    //    ballObj->setPosition(ccp(320,190));
//    spreetsheet->addChild(ballObj);

	if (arrActionExcellent != NULL) {
		arrActionExcellent->removeAllObjects();
	}

	for (int i = 1; i <= 9; i++) {
		char name[32] = { 0 };
		sprintf(name, "ballEx/%d/ballE%d%d.png", currentBall, currentBall, i);

		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(
				name);
		CCRect rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTexture,
				rect);
		arrActionExcellent->addObject(pFrame);
//        arrActionExcellent->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
	}
	return NULL;
//    return spreetsheet;
}
//-------------------------------------------------------------------------------------

cocos2d::CCSpriteBatchNode* DemoScene::iCreateBasketAnimation(
		const char *plistFile, const char *pngFile) {
//    cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFile);
//    CCSpriteBatchNode* spreetsheet = CCSpriteBatchNode::create(pngFile);
//    
//    Basket *ballObj = (Basket *)cocos2d::CCSprite::createWithSpriteFrameName("bk1.png");

//    ballObj->setPosition(ccp(160,60));
//    spreetsheet->addChild(ballObj);

	for (int i = 1; i <= 5; i++) {
		char name[32] = { 0 };
		sprintf(name, "basket/bk%d.png", i);

		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(
				name);
		CCRect rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTexture,
				rect);
		arrBasketAction->addObject(pFrame);
//        arrBasketAction->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
	}
	return NULL;
//    return spreetsheet;
}

/**
 * get ball's weight
 */

int DemoScene::getBallWeight(int ballIndex) {

	switch (ballIndex) {
	case BALL_LEVEL_1:
		return BALL_WEIGHT_1;
	case BALL_LEVEL_2:
		return BALL_WEIGHT_2;
	case BALL_LEVEL_3:
		return BALL_WEIGHT_3;
	case BALL_LEVEL_4:
		return BALL_WEIGHT_4;
	case BALL_LEVEL_5:
		return BALL_WEIGHT_5;
	case BALL_LEVEL_6:
		return BALL_WEIGHT_6;
	case BALL_LEVEL_7:
		return BALL_WEIGHT_7;
	case BALL_LEVEL_8:
		return BALL_WEIGHT_8;
	case BALL_LEVEL_9:
		return BALL_WEIGHT_9;
	}
	return 0;
}
/**
 * move to next sence
 */
bool DemoScene::nextSence() {
	if (currentBall == numOfBall) {
		// show result
		CCLog("--------------------RANKING");

		//this->endGame();
		this->scheduleOnce(schedule_selector(DemoScene::endGame), 1.5);
	} else {
		currentBall++;
		CCLOG("move to sence---%d", currentBall);
		numberOfShoot = 0;
		numberThrowBallGoal = 0;
//        currentSenceScore = 0;
		// set ball image for current ball which has index is currentBall
		char name[32] = { 0 };
		sprintf(name, "ball/%d/ball%d1.png", currentBall, currentBall);
		if (ball != NULL) {
			this->removeChild(ball, true);
		}
		ball = Ball::create(name);
//        CCLOG("Sanh Creat 1");
		ball->setPosition(ccp(BeginBallX, BeginBallY));
		ball->setAnchorPoint(ccp(0.5, 0.5));
		if (size.width == 720) {
			ball->setScale(1.5f);
		}
		ball->_root = this;
		this->addChild(ball);
		ball->setZOrder(Z_ORDER_BASKET);
		basket->setZOrder(Z_ORDER_BALL);
		// update animation for current ball
		char pngFileName[32] = { 0 };
		char plistFileName[32] = { 0 };
		sprintf(pngFileName, "ball/%d/ball%d.png", currentBall, currentBall);
		sprintf(plistFileName, "ball/%d/ball%d.plist", currentBall,
				currentBall);
		this->iCreateAnimation(plistFileName, pngFileName);

		// Luan 29/05/2013
		char pngExcellentFileName[32] = { 0 };
		char plistExcellentFileName[32] = { 0 };
		sprintf(pngExcellentFileName, "ballEx/%d/ballE%d.png", currentBall,
				currentBall);
		sprintf(plistExcellentFileName, "ballEx/%d/ballE%d.plist", currentBall,
				currentBall);
		this->iCreateExcellentAnimation(plistExcellentFileName,
				pngExcellentFileName);
		//----------------------------------------------------------------------------

	}
	return true;
}

void DemoScene::ballInGoal() {
	if (isGoal) {
		basket->goalAnimation(arrBasketAction);

	}
}

void DemoScene::ballBeginFallDownToGoal() {
	if (isGoal) {
		ball->setZOrder(Z_ORDER_BALL);
		basket->setZOrder(Z_ORDER_BASKET);
	}
}
/*
 *
 */
void DemoScene::setVecSprite() {
	int half = lineSprite->getContentSize().width / 2;
	int xleft = (size.width / 2) - half;
	int xright = (size.width / 2) + half;

	CCMoveTo *move2RightAction = CCMoveTo::create(2.0f,
			ccp(xright, vecSprite->getPositionY()));
	CCMoveTo *move2LeftAction = CCMoveTo::create(2.0f,
			ccp(xleft, vecSprite->getPositionY()));
	CCArray *_arrayLoopMove = new CCArray();

	_arrayLoopMove->addObject(move2RightAction);
	_arrayLoopMove->addObject(move2LeftAction);

	CCSequence *sequenceAction = CCSequence::create(_arrayLoopMove);
	CCRepeatForever *_repeatForeverAction = CCRepeatForever::create(
			sequenceAction);
	vecSprite->runAction(_repeatForeverAction);
}
/**
 * khi bong dc nem xong thi` vao method nay
 */
void DemoScene::resetZorder() {
	// notice game state

	setVecSprite();
	//reset bar
	if (bar != NULL) {
		this->removeChild(bar, true);
	}
	bar = BarTimeGameLayer::create();
	bar->setTag(10);
	bar->setPosition(ccp(barX, barY));
	bar->setContentSize(CCSizeMake(22, HEIGH_OF_POWER_BAR));
	this->addChild(bar);
	this->schedule(schedule_selector(DemoScene::updateProgressBar), 0.05);


	if (isExelentGoal) {

		this->showingEXCELLENTTopBanner();
	} else if (isGoal) {

		this->showingINTopBanner();
	} else {

		this->showingOUTTopBanner();
	}

	ballReset = true;
	if (isGoal) {
		ball->setZOrder(Z_ORDER_BASKET);
		basket->setZOrder(Z_ORDER_BALL);
	}
	if (isExelentGoal) {
		char name[32] = { 0 };
		sprintf(name, "ball/%d/ball%d1.png", currentBall, currentBall);
		if (ball != NULL) {
			this->removeChild(ball, true);
		}
		ball = Ball::create(name);

//        CCLOG("Sanh Creat 2");

		ball->setPosition(ccp(BeginBallX, BeginBallY));
		ball->setAnchorPoint(ccp(0.5, 0.5));
		ball->_root = this;
		if (size.width == 720) {
			ball->setScale(1.5f);
		}
		this->addChild(ball);
		ball->setZOrder(Z_ORDER_BASKET);
		basket->setZOrder(Z_ORDER_BALL);
		// update animation for current ball
		char pngFileName[32] = { 0 };
		char plistFileName[32] = { 0 };
		sprintf(pngFileName, "ball/%d/ball%d.png", currentBall, currentBall);
		sprintf(plistFileName, "ball/%d/ball%d.plist", currentBall,
				currentBall);
		this->iCreateAnimation(plistFileName, pngFileName);
	}
	isGoal = false;
	isExelentGoal = false;

	//
	gameScore += currentThrowBallScore;

	if (gameMode == NORMAL) {

		if (numberOfShoot == SCORE_TO_MOVE_NEXT_SENCE_IN_NORMAL) {

			if (numberThrowBallGoal == SCORE_TO_MOVE_NEXT_SENCE_IN_NORMAL) {

				gameMode = EXTRA;
				this->nextSence();
			} else {

				//fail
				//this->endGame();
				this->scheduleOnce(schedule_selector(DemoScene::endGame), 1.5);
			}
		} else {
			// continue current mode
			// do nothing
		}
	} else {

		//EXTRA MODE
		if (exitGameInExtraMode) {

			//this->endGame();
			this->scheduleOnce(schedule_selector(DemoScene::endGame), 1.5);
		} else {

			// continue in extra mode
			if (numberOfShoot >= SCORE_TO_MOVE_NEXT_SENCE_IN_EXTRA) {

				this->nextSence();
			}
		}
	}

	//update score UI
	char name[32] = { 0 };
	sprintf(name, "%d", gameScore);
	scoreLbl->setString(name);

	if (gameMode == NORMAL) {

		numberThrowNormalMode++;
		//update sence UI
		char sence[32] = { 0 };
		sprintf(sence, "%d/5", numberThrowNormalMode);
		senseLbl->setString(sence);
	} else {
		senseLbl->setVisible(false);
	}

}
void DemoScene::SampleSelector(CCNode *sender, void *data) {

}

void DemoScene::endGame() {
	CCLog("========restart===DATPV==");

	NDKHelper::AddSelector("YogashiSelectors", "endGame",
			callfuncND_selector(DemoScene::SampleSelector), this);
	CCDictionary* prms = CCDictionary::create();
	std::ostringstream ostr; //output string stream
	ostr << gameScore;
	std::string theNumberString = ostr.str();
	prms->setObject(CCString::create(theNumberString), "score");
	SendMessageWithParams(string("endGame"), prms);

	// RESET GAME
	//reset banner
	if(showOut != NULL){
		CCLOG("DatPV----showOut");
		this->removeChild(showOut, true);
	}
	if(showEX != NULL)
		this->removeChild(showEX, true);
	if(showRelease != NULL)
			this->removeChild(showRelease, true);
	if(showIn != NULL)
			this->removeChild(showIn, true);

	currentThrowBallScore = 0; // game score
	numberThrowBallGoal = 0;
	numInExelent = 0;
	gameScore = 0;
	currentBall = BALL_LEVEL_1; // current ball index
	numberThrowNormalMode = 0;
	senseLbl->setString("0/5");
	senseLbl->setVisible(true);

	previous_Exelent = true;
	current_Exelent = false;
	//
	gameMode = NORMAL;
	exitGameInExtraMode = false;

	numberOfShoot = 0;
	numberThrowBallGoal = 0;
	// set ball image for current ball which has index is currentBall
	char name[32] = { 0 };
	sprintf(name, "ball/%d/ball%d1.png", currentBall, currentBall);
	if (ball != NULL) {
		this->removeChild(ball, true);
	}

	ball = Ball::create(name);
	ball->setPosition(ccp(BeginBallX, BeginBallY));
	ball->setAnchorPoint(ccp(0.5, 0.5));
	if (size.width == 720) {
		ball->setScale(1.5f);
	}
	ball->_root = this;
	this->addChild(ball);
	ball->setZOrder(Z_ORDER_BASKET);
	basket->setZOrder(Z_ORDER_BALL);
	// update animation for current ball
	char pngFileName[32] = { 0 };
	char plistFileName[32] = { 0 };
	sprintf(pngFileName, "ball/%d/ball%d.png", currentBall, currentBall);
	sprintf(plistFileName, "ball/%d/ball%d.plist", currentBall, currentBall);
	this->iCreateAnimation(plistFileName, pngFileName);
	char pngExcellentFileName[32] = { 0 };
	char plistExcellentFileName[32] = { 0 };
	sprintf(pngExcellentFileName, "ballEx/%d/ballE%d.png", currentBall,
			currentBall);
	sprintf(plistExcellentFileName, "ballEx/%d/ballE%d.plist", currentBall,
			currentBall);
	this->iCreateExcellentAnimation(plistExcellentFileName,
			pngExcellentFileName);

}

// Luan added 30/05/2013
void DemoScene::finishedShowingTopBanner(cocos2d::CCNode *sender) {
	sender->removeFromParentAndCleanup(true);
}

void DemoScene::showingINTopBanner() {
	// Luan added 30/05/2013
	showIn = CCSprite::create("text/IN1.png");
	showIn->setPosition(ccp(kInSpriteX, kInSpriteY));
	CCAnimation *changeSpriteAnimation = CCAnimation::create();
	changeSpriteAnimation->addSpriteFrameWithFileName("text/IN1.png");
	changeSpriteAnimation->addSpriteFrameWithFileName("text/IN2.png");
	changeSpriteAnimation->setDelayPerUnit(.1);
	changeSpriteAnimation->setLoops(-1);
	showIn->runAction(CCAnimate::create(changeSpriteAnimation));

	CCFiniteTimeAction *movementSprite = CCMoveTo::create(
			kDurationShowingTopBanner,
			ccp(showIn->getPositionX() - 500, showIn->getPositionY()));
	;
	CCFiniteTimeAction *movementCallBack = CCCallFuncN::create(this,
			callfuncN_selector(DemoScene::finishedShowingTopBanner));

	showIn->runAction(
			CCSequence::create(movementSprite, movementCallBack, NULL));

	this->addChild(showIn, 100, 100);
	//------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------

void DemoScene::showingOUTTopBanner() {
	// Luan added 30/05/2013

	showOut = CCSprite::create("text/out1.png");
	showOut->setPosition(ccp(kInSpriteX, kInSpriteY));
	CCAnimation *changeSpriteAnimation = CCAnimation::create();
	changeSpriteAnimation->addSpriteFrameWithFileName("text/out1.png");
	changeSpriteAnimation->addSpriteFrameWithFileName("text/out2.png");
	changeSpriteAnimation->setDelayPerUnit(.1);
	changeSpriteAnimation->setLoops(-1);
	showOut->runAction(CCAnimate::create(changeSpriteAnimation));

	CCFiniteTimeAction *movementSprite = CCMoveTo::create(
			kDurationShowingTopBanner,
			ccp(showOut->getPositionX() - 500, showOut->getPositionY()));
	;
	CCFiniteTimeAction *movementCallBack = CCCallFuncN::create(this,
			callfuncN_selector(DemoScene::finishedShowingTopBanner));

	showOut->runAction(
			CCSequence::create(movementSprite, movementCallBack, NULL));

	this->addChild(showOut, 100, 100);

	//------------------------------------------------------------------------------
}

void DemoScene::showingRELEASETopBanner() {
	// Luan added 30/05/2013
	showRelease = CCSprite::create("text/release1.png");
	showRelease->setPosition(ccp(kInSpriteX, kInSpriteY));
	CCAnimation *changeSpriteAnimation = CCAnimation::create();
	changeSpriteAnimation->addSpriteFrameWithFileName("text/release1.png");
	changeSpriteAnimation->addSpriteFrameWithFileName("text/release2.png");
	changeSpriteAnimation->setDelayPerUnit(.1);
	changeSpriteAnimation->setLoops(-1);
	showRelease->runAction(CCAnimate::create(changeSpriteAnimation));

	CCFiniteTimeAction *movementSprite = CCMoveTo::create(
			kDurationShowingTopBanner,
			ccp(showRelease->getPositionX() - 420, showRelease->getPositionY()));
	;
	CCFiniteTimeAction *movementCallBack = CCCallFuncN::create(this,
			callfuncN_selector(DemoScene::finishedShowingTopBanner));

	showRelease->runAction(
			CCSequence::create(movementSprite, movementCallBack, NULL));

	this->addChild(showRelease, 100, 100);
	//------------------------------------------------------------------------------

}

void DemoScene::showingEXCELLENTTopBanner() {
	// Luan added 30/05/2013
	showEX = CCSprite::create("text/EXELLENT1.png");
	showEX->setPosition(ccp(kInSpriteX, kInSpriteY));
	CCAnimation *changeSpriteAnimation = CCAnimation::create();
	changeSpriteAnimation->addSpriteFrameWithFileName("text/EXELLENT1.png");
	changeSpriteAnimation->addSpriteFrameWithFileName("text/EXELLENT2.png");
	changeSpriteAnimation->setDelayPerUnit(.1);
	changeSpriteAnimation->setLoops(-1);
	showEX->runAction(CCAnimate::create(changeSpriteAnimation));

	CCFiniteTimeAction *movementSprite = CCMoveTo::create(
			kDurationShowingTopBanner,
			ccp(showEX->getPositionX() - 420, showEX->getPositionY()));
	;
	CCFiniteTimeAction *movementCallBack = CCCallFuncN::create(this,
			callfuncN_selector(DemoScene::finishedShowingTopBanner));

	showEX->runAction(
			CCSequence::create(movementSprite, movementCallBack, NULL));

	this->addChild(showEX, 100, 100);
	//------------------------------------------------------------------------------
}
