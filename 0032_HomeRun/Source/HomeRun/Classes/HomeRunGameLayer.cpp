#include "HomeRunGameLayer.h"

#include "GameConstants.h"
#include "HomeRunGameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
// on "init" you need to initialize your instance
bool HomeRunGameLayer::init()
{
    //////////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }
    
    //////////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    // you may modify it.
    // init variable value
//    this->setAnchorPoint(ccp(0, 0));

    this->initValue();
    size = CCDirector::sharedDirector()->getWinSize();
    CCLog("DatPV size width = %d",size.width);
    if(size.width == 720)
    	this->initLargeDesign();
    else
    	this->initMediumDesign();
    CCSprite *gameBackgroundSprite = NULL;

    gameBackgroundSprite = CCSprite::create("play_background.png");
    this->addChild(gameBackgroundSprite);
    
    // set keypad layer
    keypadSprite = KeypadLayer::create();
    keypadSprite->setPosition(ccp(keyPadX, keyPadY));
    keypadSprite->delegate = this;
    this->addChild(keypadSprite, 0);

    shadowBall2Sprite = CCSprite::create("shadow_shadow_07.png");
    shadowBall2Sprite->setVisible(false);
    this->addChild(shadowBall2Sprite, 0);

    ball2Sprite = CCSprite::create("ball.png");
    ball2Sprite->setVisible(false);
    this->addChild(ball2Sprite, 1);

    resultLabel = CCLabelTTF::create("m", "HGRPP1_0.ttf", 70);
    resultLabel->setPosition(ccp(resultLableX,resultLableY));
    resultLabel->setVisible(false);
    resultLabel->setColor(ccRED);
    this->addChild(resultLabel, 3);

    //CCSize size = CCDirector::sharedDirector()->getWinSize();

    batterCacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    ((CCSpriteFrameCache *)batterCacher)->addSpriteFramesWithFile("batter_anim.plist", "batter_anim.png");

    batterSprite = new CCSprite;

    batterSprite->initWithSpriteFrameName("batter_new_01.png");

    CCSpriteFrame *frame = ((CCSpriteFrameCache *)batterCacher)->spriteFrameByName("batter_new_01.png");

    // set batterSprite's display frame
    batterSprite->setDisplayFrame(frame);
    batterSprite->setPosition(ccp(batterX,batterY));// (-136.5, -208)

    CCSpriteBatchNode *spriteSheet = CCSpriteBatchNode::create("batter_anim.png");
    spriteSheet->addChild(batterSprite);
    this->addChild(spriteSheet, 3);

    pitcherCacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    ((CCSpriteFrameCache *)pitcherCacher)->addSpriteFramesWithFile("pitcher_anim.plist", "pitcher_anim.png");

    pitcherSprite = new CCSprite;

    pitcherSprite->initWithSpriteFrameName("pitcher_new_01.png");

    CCSpriteFrame *pitcherFrame = ((CCSpriteFrameCache *)pitcherCacher)->spriteFrameByName("pitcher_new_01.png");

    // set pitcherSprite's display frame
    pitcherSprite->setDisplayFrame(pitcherFrame);
    pitcherSprite->setPosition(ccp(-11.5f, pitcherY));//-11.5, 264

    CCSpriteBatchNode *pitcherSpriteSheet = CCSpriteBatchNode::create("pitcher_anim.png");
    pitcherSpriteSheet->addChild(pitcherSprite);
    this->addChild(pitcherSpriteSheet, 1);

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HomeRunGameLayer::touchedKeypadNotification), KEYPAD_TOUCHED_NOTIFICATION, NULL);

    // Animation for batter
    const int kNumberOfFrames = 5;
    CCArray *frames = new CCArray;
    frames->initWithCapacity(kNumberOfFrames);
    for (int i = 2; i <= kNumberOfFrames; i++) {
        CCString *fileName = CCString::createWithFormat("batter_new_0%d.png", i);
        frames->addObject(((CCSpriteFrameCache *)batterCacher)->spriteFrameByName(fileName->getCString()));
    }

    batterAnim = new CCAnimation;
    batterAnim->initWithSpriteFrames(frames, 0.1f);
    delete frames;

    // Animation for pitcher
    frames = new CCArray;
    frames->initWithCapacity(kNumberOfFrames);
    for (int i = 2; i <= kNumberOfFrames; i++) {
        CCString *fileName = CCString::createWithFormat("pitcher_new_0%d.png", i);
        frames->addObject(((CCSpriteFrameCache *)pitcherCacher)->spriteFrameByName(fileName->getCString()));
    }

    // play the animation
    pitcherAnim = new CCAnimation;
    pitcherAnim->initWithSpriteFrames(frames, 0.1f);
    delete frames;

    congratulationSprite = CCSprite::create("f_home.png");
    congratulationSprite->setPosition(ccp(congratulationSpriteX, 0.f));
    this->addChild(congratulationSprite, 4);

    // add ready sprite
    readySprite = CCSprite::create("ready.png");
    readySprite->setPosition(ccp(0, readyY)); //0, 52.5
    this->addChild(readySprite, 4);

    // add strike sprite
    strikeSprite = CCSprite::create("play_img_02.png");
    strikeSprite->setPosition(ccp(-11.f, strikeSpriteY));//-11, -2
    strikeSprite->setVisible(false);
    this->addChild(strikeSprite, 4);

    // add home run word
    homeRunWord1 = CCSprite::create("text_03.png");
    homeRunWord1->setPosition(ccp(homeRunWord1_X, -SCREEN_HEIGHT_HALF + 45.f));
    homeRunWord1->setVisible(false);
    this->addChild(homeRunWord1, 3);

    homeRunWord2 = CCSprite::create("text_02.png");
    homeRunWord2->setPosition(ccp(homeRunWord2_X, -SCREEN_HEIGHT_HALF + 45.f));
    homeRunWord2->setVisible(false);
    this->addChild(homeRunWord2, 3);

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("homerun_word_anim.plist", "homerun_word_anim.png");
    // Animation for home run word
    homeRunWord3 = new CCSprite;
    homeRunWord3->initWithSpriteFrameName("text_01.png");

    CCSpriteFrame *hrFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_01.png");
    homeRunWord3->setDisplayFrame(hrFrame);
    homeRunWord3->setPosition(ccp(homeRunWord3_X, -SCREEN_HEIGHT_HALF + 45.f));
    homeRunWord3->setVisible(false);
    CCSpriteBatchNode *hrSpriteSheet = CCSpriteBatchNode::create("homerun_word_anim.png");
    hrSpriteSheet->addChild(homeRunWord3);
    this->addChild(hrSpriteSheet, 3);

    frames = new CCArray;
    frames->initWithCapacity(2);
    frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_01.png"));
    frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_05.png"));
    homeRunWordAnim = new CCAnimation;
    homeRunWordAnim->initWithSpriteFrames(frames, 0.1f);
    delete frames;

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("foul_anim.plist", "foul_anim.png");
    // Animation for home run word
    foulSprite = new CCSprite;
    foulSprite->initWithSpriteFrameName("foul_00.png");

    CCSpriteFrame *foulFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("foul_00.png");
    foulSprite->setDisplayFrame(foulFrame);
    foulSprite->setPosition(ccp(0, foulSpriteY));
    foulSprite->setVisible(false);
    CCSpriteBatchNode *foulSpriteSheet = CCSpriteBatchNode::create("foul_anim.png");
    foulSpriteSheet->addChild(foulSprite);
    this->addChild(foulSpriteSheet, 3);

    frames = new CCArray;
    frames->initWithCapacity(2);
    frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("foul_01.png"));
    frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("foul_00.png"));
    foulAnim = new CCAnimation;
    foulAnim->initWithSpriteFrames(frames, 0.1f);
    delete frames;

    // add shadow ball sprite
    shadowBallSprite = CCSprite::create("shadow_shadow_07.png");
    shadowBallSprite->setPosition(ccp(sb_sX, sb_sY));
    shadowBallSprite->setVisible(false);
    shadowBallSprite->setScale(sb_s / 100.f);
    this->addChild(shadowBallSprite, 2);

    // add ball sprite
    ballSprite = CCSprite::create("ball.png");
    ballSprite->setPosition(ccp(b_sX, b_sY));
    ballSprite->setVisible(false);
    ballSprite->setScale(b_s / 100.f);
    this->addChild(ballSprite, 2);

    // HR ball count sprite
    CCSprite *hrCountTextSprite = CCSprite::create("play_img_03.png");
    hrCountTextSprite->setPosition(ccp(hrX,hrY));//-228, 344
    this->addChild(hrCountTextSprite, 3);

    // Remain ball count sprite
    CCSprite *remainCountTextSprite = CCSprite::create("play_img_04.png");
    remainCountTextSprite->setPosition(ccp(countX,countY));//178, 340
    this->addChild(remainCountTextSprite, 3);

    // HR ball count value
//    char value[4];
//    sprintf(value, "%d", sc);
//    hrLabel = CCLabelTTF::create(value, "HGRPP1_0.ttf", 60);
//    float x = -175.f + hrLabel->boundingBox().size.width / 2.f;
    hrLabel->setPosition(ccp(hrLableX, (SCREEN_HEIGHT_HALF - 136.f)));//x, 344
    hrLabel->setColor(ccRED);
    this->addChild(hrLabel, 3);

//    sprintf(value, "%d", b_zan);
//    remainLabel = CCLabelTTF::create(value, "HGRPP1_0.ttf", 60);
//    x = 235.f + remainLabel->boundingBox().size.width / 2.f;
    remainLabel->setPosition(ccp(remainLableX, (SCREEN_HEIGHT_HALF - 140.f)));//x, 340
    remainLabel->setColor(ccRED);
    this->addChild(remainLabel, 3);


    //add ht hint and stike msg
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ani_hr_hint.plist", "ani_hr_hint.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("strike_msg.plist", "strike_msg.png");
	// Animation for home run word
	hintHRSprite = new CCSprite;
	hintMessageSprite = new CCSprite;
	hintMessageSprite->initWithSpriteFrameName("early_message.png");
	hintMessageSprite->setVisible(false);
//	hintMessageSprite->setAnchorPoint(ccp(0,0));
	hintMessageSprite->setPosition(ccp(strikeMessageSpriteX,strikeMessageSpriteY));
//	hintMessageSprite->setPosition(ccp(size.width - hintMessageSprite->getContentSize().width,strikeMessageSpriteY));

	hintHRSprite->initWithSpriteFrameName("ani_HR_hint1.png");

	CCSpriteFrame *hintFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ani_HR_hint1.png");
	hintHRSprite->setDisplayFrame(hintFrame);
	hintHRSprite->setPosition(ccp(0, foulSpriteY));
	hintHRSprite->setVisible(false);
	CCSpriteBatchNode *hintSpriteSheet = CCSpriteBatchNode::create("ani_hr_hint.png");
	hintSpriteSheet->addChild(hintHRSprite);
	this->addChild(hintSpriteSheet, 3);
	this->addChild(hintMessageSprite,3);
	frames = new CCArray;
	frames->initWithCapacity(2);
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ani_HR_hint1.png"));
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ani_HR_hint2.png"));
	hintAnim = new CCAnimation;
	hintAnim->initWithSpriteFrames(frames, 0.1f);
	delete frames;

    this->playReadySound();

    this->scheduleOnce(schedule_selector(HomeRunGameLayer::startThrowingBall), 3.f);
    this->scheduleUpdate();
    
    return true;
}

void HomeRunGameLayer::initMediumDesign(){
		batterX = -110.5f;
		batterY = -SCREEN_HEIGHT_HALF + 200.f;
		pitcherY= -SCREEN_HEIGHT_HALF + 600.f;
		readyY =  -SCREEN_HEIGHT_HALF + 452.5;
		congratulationSpriteX = 730;
		strikeSpriteY = -SCREEN_HEIGHT_HALF + 370.f;
		resultLableY = -SCREEN_HEIGHT_HALF + 400.f;
		resultLableX = 150.f;
		keyPadX = 0;
		keyPadY = -SCREEN_HEIGHT_HALF + 205;
		hrX = -160.f;
		hrY = SCREEN_HEIGHT_HALF - 136.f;
		countX = 120.f;
		countY = SCREEN_HEIGHT_HALF - 140.f;

		char value[4];
		sprintf(value, "%d", b_zan);
		remainLabel = CCLabelTTF::create(value, "HGRPP1_0.ttf", 40);
		remainLableX = 170 + remainLabel->boundingBox().size.width / 2;
		sprintf(value, "%d", sc);
		hrLabel = CCLabelTTF::create(value, "HGRPP1_0.ttf", 40);
		hrLableX =  -110 + hrLabel->boundingBox().size.width / 2;
		homeRunWord1_X = -190;
		homeRunWord2_X = -50;
		homeRunWord3_X = -5;

		foulSpriteY = -SCREEN_HEIGHT_HALF + 452.5f;
		strikeMessageSpriteY = -SCREEN_HEIGHT_HALF + 200.5f;
		strikeMessageSpriteX = 170.f;
}

void HomeRunGameLayer::initLargeDesign(){
	batterX = -170.5f;
	batterY = -SCREEN_HEIGHT_HALF + 300.f;
	pitcherY= -SCREEN_HEIGHT_HALF + 920.f;
	readyY =  -SCREEN_HEIGHT_HALF + 692.5;
	congratulationSpriteX = 730;
	strikeSpriteY = -SCREEN_HEIGHT_HALF + 490.f;
	resultLableY = -SCREEN_HEIGHT_HALF + 490.f;
	resultLableX = 250.f;
	keyPadX = 0;
	keyPadY = -SCREEN_HEIGHT_HALF + 260;
	hrX = -228.f;
	hrY = SCREEN_HEIGHT_HALF - 136.f;
	countX = 178.f;
	countY = SCREEN_HEIGHT_HALF - 140.f;

	char value[4];
	sprintf(value, "%d", b_zan);
	remainLabel = CCLabelTTF::create(value, "HGRPP1_0.ttf", 60);
	remainLableX = 265.f + remainLabel->boundingBox().size.width / 2.f;
	sprintf(value, "%d", sc);
	hrLabel = CCLabelTTF::create(value, "HGRPP1_0.ttf", 60);
	hrLableX = -150.f + hrLabel->boundingBox().size.width / 2.f;

	homeRunWord1_X = -236.5;
	homeRunWord2_X = -80;
	homeRunWord3_X = -3;

	foulSpriteY = -SCREEN_HEIGHT_HALF + 532.5f;
	strikeMessageSpriteY = -SCREEN_HEIGHT_HALF + 250.5f;
	strikeMessageSpriteX = 270.f;

}
void HomeRunGameLayer::initValue()
{
    t_t_n = 3;
    b_spH = 60.f;
    b_spSC = 120.f;
    b_spSLR = 100.f;
    sc = 0;
    totalKM = 0;
    b_ch = 9;
    b_zan = b_ch;
    ex = false;
#if TESTING
//    b_zan = 0;
//    sc = 997;
#endif
    this->resetValue();
}

void HomeRunGameLayer::resetValue()
{
    t_state = ThrowingStateNone;
    th = -0.5;
    htg_flg = false;
    wr = 50;
    b_c = 0;
    hit_rlt = HitResultNone;
}

//static int i = 0;


void HomeRunGameLayer::startThrowingBall()
{
    readySprite->setVisible(false);
    hintMessageSprite->setVisible(false);
    int randomValue = arc4random() % t_t_n;
    t_typ = (ThrowingType)randomValue;
    int rnd_p = arc4random() % p_n;
    //t_typ = (ThrowingType)4;
#if TESTING
    t_typ = (ThrowingType)3;
    rnd_p = i++ % 9;
#endif
#if TESTING_1
    t_typ = (ThrowingType)2;
#endif
    mkn = rnd_p;
    keypadSprite->setMarkerAt(rnd_p);
    int tmp = rnd_p % p_y_n;
    if (t_typ < ThrowingTypeLoose) {
        // Straight Ball
        b_sp = b_spH;
    } else if (t_typ >= ThrowingTypeTurningRound) {
        // Strange Ball
        b_sp = b_spSC;
    } else {
        // Slow and loose curve ball
        if (tmp == 1) {
            b_sp = b_spSC;
        } else {
            b_sp = b_spSLR;
        }
    }
    // X position of shadow ball
    if (tmp == 0) {
        // Case 1, 4, 7
        sb_HX = sb_lHX;
    } else if (tmp == 1) {
        // There is no movement in case 2, 5, 8
        sb_HX = sb_sX;
    } else if (tmp == 2) {
        // Case 3, 6, 9
        sb_HX = sb_rHX;
    }
    int random1 = arc4random() % 4;
    int random2 = arc4random() % 3 - 1;
    sb_HX += random1 * random2;
    // Y position of ball
    tmp = floor(rnd_p / p_y_n);
    if (tmp == 0) {
        // Case 1, 2, 3
        if (t_typ <= 0 || t_typ >= 2) {
            b_HY = b_uHYS;
        } else if (t_typ <= 1) {
            // 速球
            b_HY = b_uHY;
        }
    } else if (tmp == 1) {
        // Case 4, 5, 6
        b_HY = b_mHY;
    } else if (tmp == 2) {
        // Case 7, 8, 9
        b_HY = b_dHY;
    }
    // Strange ball settings
    if (t_typ >= 3) {
        r = arc4random() % 4;
#if TESTING
        r = 2;
#endif
//        printf("r %d\n", r);
        if (r <= 1) {
            mth = mth_1;    // Quay 3 vong (6 cai nua vong tron)
        } else {
            mth = mth_2;    // Quay 2 vong (4 cai nua vong tron)
        }
        if (r % 2) {
            r = -1; // Quay nguoc chieu kim dong ho
        } else {
            r = 1;  // Quay chieu kiem dong ho
        }
    }
    b_dy = (b_HY - b_sY) / (float)b_sp;
    sb_dx = (sb_HX - sb_sX) / (float)b_sp;
    sb_dy = (sb_HY - sb_sY) / (float)b_sp;
//    	b_dy = (b_HY - B_SY) / (float)b_sp;
//        sb_dx = (sb_HX - sb_sX) / (float)b_sp;
//        sb_dy = (SB_HY - SB_SY) / (float)b_sp;
    pitcherSprite->runAction(CCSequence::create(CCAnimate::create(pitcherAnim), CCCallFuncN::create(this, callfuncN_selector(HomeRunGameLayer::throwBall)), NULL));

}

void HomeRunGameLayer::update(float dt)
{
	float _y = shadowBallSprite->getPosition().y;
	//CCLOG("toa do ball: %f / HR_Y_1 %f : HR_Y_2 %f MISS_Y_1 %f MISS_Y_2 %f",_y,HR_Y_1,HR_Y_2,MISS_Y_1,MISS_Y_2);
	bool showHint = (MAX_BALL_COUNT - b_zan <= 2) ? true : false;
	if(showHint){
		if(_y <= HR_Y_1 && _y >= HR_Y_2)
		{
			showHomeRunHint();
		}else{
			hideHomeRunHint();
		}
	}
    if (t_state == ThrowingStateStarted) {
        // set ball sprite position and scale
        this->updateBallSpritePositionAndScale();
        // Set shadow sprite position and scale
        this->updateShadowBallSpritePositionAndScale();
    } else if (t_state == ThrowingStateFlying) {
        this->updateBallSpriteFlyingPositionAndScale();
        this->updateShadowBallSpriteFlyingPositionAndScale();
    } else if (t_state == ThrowingStateMissBall) {
        this->updateBallSpriteMissBallPositionAndScale();
        this->updateShadowBallSpriteMissBallPositionAndScale();
    } else if (t_state == ThrowingStateHR) {
        this->updateBallSpriteHomeRunPositionAndScale();
        this->updateShadowBallSpriteHomeRunPositionAndScale();
    } else if (t_state == ThrowingStateFoul) {
        this->updateBallSpriteFoulPositionAndScale();
        this->updateShadowBallSpriteFoulPositionAndScale();
    }
}

void HomeRunGameLayer::updateBallSpritePositionAndScale()
{
    float _x = ballSprite->getPosition().x;
    float _y = ballSprite->getPosition().y;
    float _xscale = ballSprite->getScale() * 100;
    float _yscale = ballSprite->getScale() * 100;

    if (t_typ <= 2) {
        //直球・ゆるい球・ゆるいカーブ
        //ボールの_x
        _x = shadowBallSprite->getPosition().x;
        //ボールの_y
        _y += b_dy;
        //ボールの大きさ
        _xscale += (100 - b_s) / (float)b_sp;
        _yscale = _xscale;
    } else if (t_typ == 3) {
        //ぐるぐる
        if (mth <= th) {
            _x = b_sX + wr * cos(th * M_PI) * r;
            _y = b_sY + wr * sin(th * M_PI);
            //ボールの大きさ
            _xscale += 0.125;
            _yscale = _xscale;
            if (mth == th) {
                b_tx = _x;
                b_ty = _y;
                b_dx = (sb_HX - b_tx) / b_sp;
                b_dy = (b_HY - b_ty) / b_sp;
            }
            if (mth == mth_1) {
            	if(size.width == 480)
            		wr +=0.1f;
            	else
            		wr += 0.5f;//3
                th -= 0.03125f;//0.05f;//0.125
            } else {
            	if(size.width == 480)
            	    wr +=0.5f;
            	else
            		wr += 1.f;
                th -= 0.03125f;
            }
        } else {
            _x = shadowBallSprite->getPosition().x;
            _y += b_dy;
            _xscale += 0.5;
            _yscale = _xscale;
        }
    } else if (t_typ == 4) {
        //クセ球
        if (b_c < max_b_c_4) {
            if (b_c <= max_b_c_4 / 2) {
                _x += r * 10;
                _y += 30;
            } else {
                _x -= r * 15;
                _y -= 33;
            }
        } else {
            _x = shadowBallSprite->getPosition().x;
            _y += b_dy * (b_c - max_b_c_4 - 1) / (float)b_sp;
            _xscale += (100 - b_s) / (float)b_sp;
            _yscale = _xscale;
        }
        b_c++;
    } else if (t_typ == 5) {
        //ブーメラン
        if (b_c <= 10) {
            _x += r * 2 + 5;
            _y += 25;
            _xscale -= 3.5f;
            _yscale = _xscale;
            if (b_c == 8) {
                b_ts = _xscale;
                b_dy = (b_HY - _y) / b_sp;
            }
        } else if (15 + r < b_c) {
            _x = shadowBallSprite->getPosition().x;
            _y += b_dy;
            _xscale += (100 - b_ts) / (float)b_sp;
            _yscale = _xscale;
        }
    }
    ballSprite->setPosition(ccp(_x, _y));
    float scale = _xscale / 100.f;
    ballSprite->setScale(scale);


}

void HomeRunGameLayer::updateShadowBallSpritePositionAndScale()
{
    float _x = shadowBallSprite->getPosition().x;
    float _y = shadowBallSprite->getPosition().y;
    float _xscale = shadowBallSprite->getScale() * 100;
    float _yscale = shadowBallSprite->getScale() * 100;
    if (t_typ >= 3) {
#if TESTING
        shadowBallSprite->setVisible(true);
#else
        shadowBallSprite->setVisible(false);
#endif
    } else {
        shadowBallSprite->setVisible(true);
        _xscale += (100 - sb_s) / (float)b_sp;
        _yscale = _xscale;
    }
    if (_y >= sb_MaxY) {
        b_c++;
        //ボールの大きさ
        if (t_typ <= 1) {
            //直球とゆるい球
            _x += sb_dx;
            _y += sb_dy;
        } else if (t_typ == 2) {
            //ゆるいカーブ
            _x += sb_dx;
            _y += sb_dy;
            if (b_c >= b_sp - 20) {
                if (sb_dx <= 0) {
                    sb_dx -= 0.075;
                } else {
                    sb_dx += 0.075;
                }
            }
        } else if (t_typ == 3) {
            //ぐるぐる
            if (mth == th) {
                _x = ballSprite->getPosition().x;
               //DatPV test
                //mth = mth_1 + 2;
                if (mth == mth_1) {
                    _y = THROW_TYPE_3_1; //160
                } else {
                    _y = THROW_TYPE_3_2;    //150
                }
                if (mth == mth_1) {                    
                    sb_dx = (sb_HX - _x) / b_sp;
                } else {
                    sb_dx = (sb_HX - _x) / b_sp;
                }
                sb_dy = (sb_HY - -40) / b_sp;   // 320-10 la vi tri shadow banh trc khi ra khoi man hinh, 320-142*8/3=-59
            } else if (mth > th) {
                _x += sb_dx;
                _y += sb_dy;
            }
            _xscale = _yscale = ballSprite->getScale() * 100;
        } else if (t_typ == 4) {
            //DatPV test
        	//b_c = max_b_c_4 +2;
            if (b_c == max_b_c_4 + 1) {
                _x = ballSprite->getPosition().x;
                sb_dx = (sb_HX - _x) / (float)b_sp;
                _y = sb_sY;
            } else if (max_b_c_4 < b_c) {
                _x += sb_dx;
                if(size.width == 480)
                	_y += sb_dy * (b_c - max_b_c_4 - 1) / (float)b_sp;
                else
                	_y += sb_dy * (b_c - max_b_c_4 - 1) / (float)b_sp + 1;
            }
            _xscale = _yscale = ballSprite->getScale() * 100;
        } else if (t_typ == 5) {
            //ブーメラン
            if (b_c == 10) {
                sb_ts = ballSprite->getScale() * 100;
                _x = ballSprite->getPosition().x;
                sb_dx = (sb_HX - _x) / (float)b_sp;
                sb_dy = (sb_MaxY - -133 - _y) / (float)b_sp;   // tang -133 phai nho tang xet if (b_c == 3) ben updateBall
                _xscale = _yscale = sb_ts;
            } else if (15 + r < b_c) {
                _x += sb_dx;
                _y += sb_dy;
                _xscale += (100 - sb_ts) / (float)b_sp;
                _yscale = _xscale;
            }
        }
        shadowBallSprite->setPosition(ccp(_x, _y));
        shadowBallSprite->setScale(_xscale / 100.f);
    } else {
        t_state = ThrowingStateNone;
        this->resetBallPosition();
        this->showStrike();
    }
}

void HomeRunGameLayer::updateBallSpriteFlyingPositionAndScale()
{
    b2_x = shadowBall2Sprite->getPosition().x;
    if (b2_bm > bm - 70) {
        float tmp = (float)b2_bdy / (bm - 20) / (bm - 20) * (b2_bm - bm) * (b2_bm - bm + 70);
        b2_y = shadowBall2Sprite->getPosition().y - tmp;
    } else {
        float tmp = (float)7 * b2_bdy / (bm - 50) / (bm - 50) * (b2_bm + 30) * (b2_bm - bm + 70);
        float prev_b2_y = b2_y;
        b2_y = shadowBall2Sprite->getPosition().y - tmp;
        if (b2_y > prev_b2_y || bm == 210) {
            this->reorderChild(ball2Sprite, 2);
        } else {
            this->reorderChild(ball2Sprite, 0);
        }
    }
    b2_bm++;
    ball2Sprite->setPosition(ccp(b2_x, b2_y));
    ball2Sprite->setScale(shadowBall2Sprite->getScale());
}

void HomeRunGameLayer::updateShadowBallSpriteFlyingPositionAndScale()
{
    float _xscale = shadowBall2Sprite->getScale() * 100, _yscale;
    if (sb2_bm < bm) {
        sb2_x += sb2_dx * (bm - sb2_bm);
        sb2_y += sb2_dy * (bm - sb2_bm);
        if (sb2_bm <= 10) {
            _xscale -= (hsc - 80) / 5;
            _yscale = _xscale;
            ls = _xscale;
        } else if (sb2_bm < (bm - 70)/2) {
            ts = hsc - (hsc - 20)/155 * (-231 - sb2_y) * 3/8;
            if (ts < ls) {
                _xscale = _yscale = ts;
            } else {
                _xscale = _yscale = ls;
            }
        } else if (sb2_bm < bm - 70) {
            ts = hsc - (hsc - 20)/155 * abs(-231 - sb2_y) * 3/8;
            float tmp = (float)3 * (bm - 70 - sb2_bm) * (ts - ls) / (bm - 70);  // so lan nhan cang lon, shadow se cang lon
            _xscale = _yscale = ts - tmp;
        } else if (sb2_bm <= bm - 30) {
            _xscale -= 0.2f; // khi nay len, cho nho hon luc rot xuong
            _yscale = _xscale;
        } else {
            _xscale += 0.2f;   // khi dung yen hoan toan, xet scale lon hon ti
            _yscale = _xscale;
        }
        sb2_bm++;
        shadowBall2Sprite->setPosition(ccp(sb2_x, sb2_y));
        float scale = _xscale / 100.f;
        shadowBall2Sprite->setScale(scale);
    } else {
        // Tell b2 stop
        t_state = ThrowingStateNone;
        resultLabel->setVisible(true);
        this->unschedule(schedule_selector(HomeRunGameLayer::resetGame));
        this->scheduleOnce(schedule_selector(HomeRunGameLayer::resetGame), 1.5f);
    }
}

void HomeRunGameLayer::updateBallSpriteMissBallPositionAndScale()
{
    float _xscale = ball2Sprite->getScale();
    if (b2_bm < bm) {
        b2_x += b2_dx;
        b2_y += b2_dy;
        _xscale -= b2_ts;
        if (b2_bm == 41) {
            b2_dx = (r * 15) / 30.f;
            b2_dy = 15 / 30.f;
            b2_ts = 0.05 / 30.f;
        } else if (b2_bm == 71) {
            b2_dx = (r * 10) / 30.f;
            b2_dy = -5 / 30.f;
            b2_ts = 0.05 / 30.f;
        } else if (b2_bm == 101) {
            b2_dx = 0.f;
            b2_dy = 0.f;
            b2_ts = 0.f;
        }
        ball2Sprite->setPosition(ccp(b2_x, b2_y));
        ball2Sprite->setScale(_xscale);
        b2_bm++;
    }
}

void HomeRunGameLayer::updateShadowBallSpriteMissBallPositionAndScale()
{
    float _xscale = ball2Sprite->getScale();
    if (sb2_bm < bm) {
        sb2_x += sb2_dx;
        sb2_y += sb2_dy;
        _xscale -= sb2_ts;
        if (sb2_bm == 41) {
            sb2_dx = (r * 15) / 30.f;
            sb2_dy = 5 / 30.f;
            sb2_ts = 0.05 / 30.f;
        } else if (sb2_bm == 71) {
            sb2_dx = (r * 10) / 30.f;
            sb2_dy = 5 / 30.f;
            sb2_ts = 0.05 / 30.f;
        } else if (sb2_bm == 101) {
            sb2_dx = 0.f;
            sb2_dy = 0.f;
            sb2_ts = 0.f;
        }
        shadowBall2Sprite->setPosition(ccp(sb2_x, sb2_y));
        shadowBall2Sprite->setScale(_xscale);
        sb2_bm++;
    } else {
        t_state = ThrowingStateNone;
        resultLabel->setVisible(true);
        this->unschedule(schedule_selector(HomeRunGameLayer::resetGame));
        this->scheduleOnce(schedule_selector(HomeRunGameLayer::resetGame), 1.5f);
    }
}

void HomeRunGameLayer::updateBallSpriteHomeRunPositionAndScale()
{
    if (b2_bm < bm) {
        float xscale = ball2Sprite->getScale();
        b2_x += b2_dx;
        b2_y += b2_dy;
        xscale -= b2_ts;
        switch (hrType) {
            case HomeRunTypeStraight:
                if (b2_bm == 17) {
                    b2_dx = 0;
                    b2_dy = 0;
                    b2_ts = 0;
                } else if (b2_bm == 60) {
                    homeRunWord1->setVisible(false);
                    homeRunWord2->setVisible(true);                    
                } else if (b2_bm == 131) {
                    b2_y = (SCREEN_HEIGHT_HALF * 3 / 2.f);
                    xscale = 0.33f;
                    b2_dy = (HR_BALL_FALL - b2_y) / 90.f;
                    b2_ts = 0.167 / 90.f;
                } else if (b2_bm == 221) {
                    ball2Sprite->setVisible(false);
                }
                break;
            case HomeRunTypeLeft1:
            case HomeRunTypeRight1:
                if (b2_bm == 17) {
                    homeRunWord1->setVisible(false);
                    homeRunWord2->setVisible(true);
                    b2_dx = 0;
                    b2_dy = 0;
                    b2_ts = 0;
                } else if (b2_bm == 131) {
                    b2_x = ball2Sprite->getPosition().x + (r * 45.f);
                    b2_y = (SCREEN_HEIGHT_HALF * 3 / 2.f);
                    xscale = 0.283f;
                    b2_dx = (r * 100) / 90.f;
                    b2_dy = (HR_BALL_FALL - b2_y) / 90.f;
                    b2_ts = 0.0167 / 90.f;
                } else if (b2_bm == 221) {
                    ball2Sprite->setVisible(false);
                }
                break;
            case HomeRunTypeLeft2:
            case HomeRunTypeRight2:
                if (b2_bm == 17) {
                    homeRunWord1->setVisible(false);
                    homeRunWord2->setVisible(true);
                    b2_dx = 0;
                    b2_dy = 0;
                    b2_ts = 0;
                } else if (b2_bm == 131) {
                    b2_x = ball2Sprite->getPosition().x + (r * 70.f);
                    b2_y = (SCREEN_HEIGHT_HALF * 3 / 2.f);
                    xscale = 0.283f;
                    b2_dx = (r * 20) / 90.f;
                    b2_dy = (HR_BALL_FALL - b2_y) / 90.f;
                    b2_ts = 0.0167 / 90.f;
                } else if (b2_bm == 221) {
                    ball2Sprite->setVisible(false);
                }
                break;
            default:
                break;
        }        b2_bm++;
        ball2Sprite->setPosition(ccp(b2_x, b2_y));
        ball2Sprite->setScale(xscale);
    }
}

void HomeRunGameLayer::updateShadowBallSpriteHomeRunPositionAndScale()
{
    if (sb2_bm < bm) {
        float xscale = shadowBall2Sprite->getScale();
        sb2_x += sb2_dx;
        sb2_y += sb2_dy;
        xscale -= sb2_ts;
        switch (hrType) {
            case HomeRunTypeStraight:                
                if (sb2_bm == 29) {
                    sb2_ts = 0.125 / 90.f;
                } else if (sb2_bm == 119) {
                    sb2_dx = 0;
                    sb2_dy = 0;
                    sb2_ts = 0;
                    shadowBall2Sprite->setVisible(false);
                }
                break;
            case HomeRunTypeLeft1:
            case HomeRunTypeRight1:
                if (sb2_bm == 23) {
                    sb2_ts = 0.13 / 60.f;
                } else if (sb2_bm == 83) {
                    sb2_dx = 0;
                    sb2_dy = 0;
                    sb2_ts = 0;
                    shadowBall2Sprite->setVisible(false);
                }
                break;
            case HomeRunTypeLeft2:
            case HomeRunTypeRight2:
                if (sb2_bm == 23) {
                    sb2_ts = 0.13 / 60.f;
                } else if (sb2_bm == 83) {
                    sb2_dx = 0;
                    sb2_dy = 0;
                    sb2_ts = 0;
                    shadowBall2Sprite->setVisible(false);
                }
                break;
            default:
                break;
        }
        sb2_bm++;
        shadowBall2Sprite->setPosition(ccp(sb2_x, sb2_y));
        shadowBall2Sprite->setScale(xscale);
    } else {
        t_state = ThrowingStateNone;
        resultLabel->setVisible(true);
        this->showCongratulation();
    }
}

void HomeRunGameLayer::updateBallSpriteFoulPositionAndScale()
{
    float xscale = ball2Sprite->getScale();
    if (b2_bm < bm) {
        b2_x += b2_dx;
        b2_y += b2_dy;
        xscale -= b2_ts;
        if (b2_bm == 89) {
            b2_dx = 0;
            b2_dy = 0;
            b2_ts = 0;
        }
        b2_bm++;
        ball2Sprite->setPosition(ccp(b2_x, b2_y));
        ball2Sprite->setScale(xscale);
    }
}

void HomeRunGameLayer::updateShadowBallSpriteFoulPositionAndScale()
{
    float xscale = shadowBall2Sprite->getScale();
    if (sb2_bm < bm) {
        sb2_x += sb2_dx;
        sb2_y += sb2_dy;
        xscale -= sb2_ts;
        if (sb2_bm == 89) {
            sb2_dx = 0;
            sb2_dy = 0;
            sb2_ts = 0;
        }
        sb2_bm++;
        shadowBall2Sprite->setPosition(ccp(sb2_x, sb2_y));
    } else {
        t_state = ThrowingStateNone;
        this->showFoul();
    }
}

void HomeRunGameLayer::throwBall()
{
    t_state = ThrowingStateStarted;
    ballSprite->setVisible(true);
    shadowBallSprite->setVisible(true);
}

void HomeRunGameLayer::touchedKeypadNotification(CCObject* notificationObj)
{
    if (!htg_flg) {        
        this->runBatterAnimation();
    }
    float _y = shadowBallSprite->getPosition().y;
    CCSpriteFrame *msgFrame;
    CCSpriteFrameCache *Cacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCLOG("toa do ball: %f / HR_Y_1 %f : HR_Y_2 %f MISS_Y_1 %f MISS_Y_2 %f",_y,HR_Y_1,HR_Y_2,MISS_Y_1,MISS_Y_2);
    if (_y > HR_Y_1)
	{
    	CCLog("strike_early");
		msgFrame = Cacher->spriteFrameByName("early_message.png");
		hintMessageSprite->setDisplayFrame(msgFrame);
		hintMessageSprite->setVisible(true);
	}else if (_y < HR_Y_2)
	{
		CCLog("strike_late");
		msgFrame = Cacher->spriteFrameByName("late_message.png");
		hintMessageSprite->setDisplayFrame(msgFrame);
		hintMessageSprite->setVisible(true);
	}


    //タイミング
    if (b_c) {
        bool f = false;
        hit_rlt = HitResultHit;
        float blHY = shadowBallSprite->getPosition().y;
        KeypadButtonSprite *keypadBtn = (KeypadButtonSprite *)notificationObj;
        //blHY = MISS_Y_1;
        //720 homrun
        //blHY = -550;
        //blHY = -350;
        //mkn = keypadBtn->getTag();
#if TESTING
//        blHY = -250.f;
        blHY = MISS_Y_1;
        mkn = keypadBtn->getTag();
#endif
#if TESTING_1
        blHY = MISS_Y_1;
        mkn = keypadBtn->getTag();
#endif
        if (keypadBtn->getTag() == mkn) {
            int grndN;
            int km;
            // 240 - 285
//            CCLOG("unschedule");
            this->unschedule(schedule_selector(HomeRunGameLayer::resetGame));
#if TESTING
//            blHY = HR_Y_1 - 1;
#endif
//            if (blHY <= -234.5 && blHY >= -282.5) {
            if (blHY < HR_Y_1 && blHY > HR_Y_2) {
                //ホームラン
//                printf("HR\n");
#if TESTING
                hrType = (HomeRunType)0;
#else
                int randomType = (arc4random() % 12) % 7;
                hrType = (HomeRunType)randomType;
                float b_hit_X = ballSprite->getPosition().x;
                if (hrType > HomeRunTypeRight2) {
                    hit_rlt = HitResultFoul;
                    t_state = ThrowingStateFoul;
                    if (hrType % 2) {
                        r = 1;
                    } else {
                        r = -1;
                    }
                    this->runFoulAnimation(b_hit_X, hrType);
                    keypadSprite->setVisible(false);
                    this->playBatSound();
                } else {
                    hit_rlt = HitResultHR;
                    //飛距離表示
                    km = 120 + arc4random() % 30;
                    // Show result
                    t_state = ThrowingStateHR;
                    if (hrType == 0) {
                        r = 0;
                    } else if (hrType % 2) {
                        r = 1;
                    } else {
                        r = -1;
                    }
                    char value[6];
                    sprintf(value, "%dm", km);
                    resultLabel->setString(value);
                    homeRunWord1->setVisible(true);
                    this->runHomeRunAnimation(b_hit_X, hrType);
                    keypadSprite->setVisible(false);
                    totalKM += km;
                    this->playBatSound();
                    this->playHomeRunSound();
                }
#endif
            }else if ((blHY <= MISS_Y_1 && blHY > HR_Y_1) || (blHY < HR_Y_2 && blHY >= MISS_Y_2)) {
                this->playBatSound();
                grndN = arc4random() % 5;
                //grndN = 2;
#if TESTING
                grndN = 2 + arc4random() % 3;
                //grndN = 2;
#endif
                float bhiX = ballSprite->getPosition().x;
                hit_rlt = HitResultMiss;
                if (grndN <= 1) {
                    //ゴロ
                    km = 8 + arc4random() % 7;
                    // Run miss ball animation
                    if (grndN == 0) {
                        r = -1;
                    } else {
                        r = 1;
                    }
                    bm = 144;
                    b2_bm = 0;
                    b2_x = bhiX;
                    b2_y = b_uHYS;
                    b2_dx = (r * 160) / 42.f;
                    b2_dy = 40.f / 42.f;
                    b2_ts = 0.2 / 42.f;
                    ball2Sprite->setPosition(ccp(b2_x, b2_y));
                    ball2Sprite->setScale(1.f);
                    sb2_bm = 0;
                    sb2_x = bhiX;
                    sb2_y = b2_y - 90;
                    sb2_dx = b2_dx;
                    sb2_dy = (40.f + 90.f) / 42.f;
                    sb2_ts = 0.2 / 42.f;
                    shadowBall2Sprite->setPosition(ccp(sb2_x, sb2_y));
                    shadowBall2Sprite->setScale(1.f);
                    t_state = ThrowingStateMissBall;
                    ball2Sprite->setVisible(true);
                    shadowBall2Sprite->setVisible(true);
                    keypadSprite->setVisible(false);
                } else {
                    //フライ
                	float posPitcher;
                	int r1;//Khoang cach dao dong cua kmy
                	int kmy;
                	int keyPadToPit;
				    if(size.width == 480){
						posPitcher = -SCREEN_HEIGHT_HALF + 540;
						r1 = arc4random() % 230;
						kmy = (-SCREEN_HEIGHT_HALF + 334) + r1;
						keyPadToPit = 208;
				    }else{
						posPitcher = -SCREEN_HEIGHT_HALF + 840;
						r1 = arc4random() % 400;
						kmy = (-SCREEN_HEIGHT_HALF + 456) + r1;
						keyPadToPit = 380;
				    }
                    //int r1 = arc4random() % 300;
#if TESTING
                    r1 = arc4random() % 300;
                    r1 = 273;
#endif
                    int ra = arc4random() % 2;
                    if (ra == 0) {
                        ra = -1;    // Quyet dinh chieu cua x
                    }
                    //ボールが落ちきったときのx方向座標
                    int kmx = 0 + ra * (arc4random() % 265);// x dao dong trong khoang (-265, 265)
                    //ボールが落ちきったときのy方向座標
                    //int kmy = (-SCREEN_HEIGHT_HALF + 450) + r1;//56 + r;  // y dao dong trong khoang [-27, 173)
                    if (kmy < (-SCREEN_HEIGHT_HALF + 650) && abs(kmx) <= 85) {// neu kmy < 80 thi gioi han x dao dong trong khoang [-85, 85]
                        if (ra > 0) {
                            kmx = 85;//145;
                        } else {
                            kmx = -85;//95;
                        }
                    }
                    long bmS = 0;

                    if (kmy < posPitcher) { //200 la vi tri tai chan cua pitcher
                        km = 22 + floorf((kmy + 30) / 10);
                        bm = 210;//210 tuong ung 3.5s
                    } else {
                        if ((abs(kmx) <= 180) || r1 <= keyPadToPit) {//if ((abs(kmx - 120) <= 45 && r >= 8) || r >= 13) {
                            km = floor(r1 / 8) + 20;// km dao dong trong khoang [48, 54];
                        } else {
                            km = floor(r1 / 2) - 70;//km dao dong trong khoang [67, 80];
                        }
                        bm = 240;//240 tuong ung 4s
                    }
                    for (int j = bm; j > 0; j--) {
                        bmS += j;
                    }
                    //１フレームあたりの移動距離
                    sb2_dx = (kmx - bhiX) / (float)bmS;
                    sb2_dy = (kmy - MISS_Y_1) / (float)bmS;
                    b2_bm = 0;
                    b2_x = bhiX;
                    b2_y = b_uHY;
                    ball2Sprite->setPosition(ccp(b2_x, b2_y));
                    b2_bdy = 320 + arc4random() % 200;
                    sb2_bm = 0;
                    sb2_x = bhiX;
                    sb2_y = MISS_Y_1;
                    shadowBall2Sprite->setPosition((ccp(sb2_x, sb2_y)));
                    hsc = shadowBallSprite->getScale() * 100;
                    shadowBall2Sprite->setScale(hsc / 100.f);
                    t_state = ThrowingStateFlying;
                    ball2Sprite->setVisible(true);
                    shadowBall2Sprite->setVisible(true);
                    keypadSprite->setVisible(false);
                }                
                //飛距離表示
                char value[6];
                sprintf(value, "%dm", km);
                totalKM += km;
                resultLabel->setString(value);
            } else if (blHY < -SCREEN_HEIGHT_HALF) {
                f = true;
            } else {
                t_state = ThrowingStateNone;
                this->showStrike();
                this->resetBallPosition();
            }
        } else {
            t_state = ThrowingStateNone;
            this->resetBallPosition();
            this->showStrike();
        }
        if (f) {
            f = false;
        } else {
            this->resetBallPosition();
        }
    }
}

void HomeRunGameLayer::runBatterAnimation()
{
    htg_flg = true;
    batterSprite->runAction(CCSequence::create(CCAnimate::create(batterAnim), CCCallFuncN::create(this, callfuncN_selector(HomeRunGameLayer::setState)), NULL));
}

void HomeRunGameLayer::setState()
{
    if (hit_rlt == HitResultNone) {
        this->resetBatter();
        htg_flg = false;
    }
}

void HomeRunGameLayer::showStrike()
{
    this->playDisappointedSound();
    strikeSprite->setVisible(true);
    keypadSprite->resetMarker();
    b_c = 0;
    keypadSprite->setKeypadTouchEnabled(false);
    this->unschedule(schedule_selector(HomeRunGameLayer::resetGame));
    this->scheduleOnce(schedule_selector(HomeRunGameLayer::resetGame), 1.5f);
}

void HomeRunGameLayer::showCongratulation()
{
    resultLabel->setVisible(true);
    homeRunWord2->setVisible(false);
    homeRunWord3->setVisible(true);
    homeRunWord3->runAction(CCRepeatForever::create(CCAnimate::create(homeRunWordAnim)));
    CCMoveBy *moveBy = CCMoveBy::create(1.5f, ccp(-1280.f, 0.f));
    congratulationSprite->runAction(CCSequence::create(moveBy, CCCallFuncN::create(this, callfuncN_selector(HomeRunGameLayer::homeRun)), NULL));
}

void HomeRunGameLayer::showFoul()
{
    this->playFoulSound();
    foulSprite->setVisible(true);
    foulSprite->runAction(CCSequence::create(CCRepeat::create(CCAnimate::create(foulAnim), 5), CCCallFuncN::create(this, callfuncN_selector(HomeRunGameLayer::resetGame)), NULL));
}

void HomeRunGameLayer::homeRun()
{
    congratulationSprite->setPosition(ccp(congratulationSpriteX, 0.f));
    homeRunWord3->setVisible(false);
    homeRunWord3->stopAllActions();
    sc++;
    char value[4];
    sprintf(value, "%d", sc);
    hrLabel->setString(value);
    float x = -170.f + hrLabel->boundingBox().size.width / 2.f;
    hrLabel->setPosition(ccp(hrLableX, (SCREEN_HEIGHT_HALF - 136.f)));
    this->resetGame();
}

void HomeRunGameLayer::resetGame()
{
    this->setValue();
    keypadSprite->setKeypadTouchEnabled(true);
    keypadSprite->setVisible(true);
    ball2Sprite->setVisible(false);
    ball2Sprite->setScale(1);
    shadowBall2Sprite->setVisible(false);
    shadowBall2Sprite->setScale(1);
    resultLabel->setVisible(false);
    strikeSprite->setVisible(false);
    foulSprite->setVisible(false);
    this->resetValue();
    this->resetPitcher();
    this->resetBatter();
}

void HomeRunGameLayer::resetBallPosition()
{    
    ballSprite->setPosition(ccp(b_sX, b_sY));
    ballSprite->setScale(b_s / 100.f);
    ballSprite->setVisible(false);
    shadowBallSprite->setPosition(ccp(sb_sX, sb_sY));
    shadowBallSprite->setScale(sb_s / 100.f);
    shadowBallSprite->setVisible(false);
    this->reorderChild(shadowBallSprite, 1);
    this->reorderChild(ballSprite, 1);
}

void HomeRunGameLayer::setValue()
{
    //2球目以降のセット用フレーム
    if (b_zan >= 0) {
        b_zan--;
    }
    if (b_zan < 0 && b_ch + 1 == sc) {
        ex = true;
        t_t_n = 6;
    }
#if TESTING
//    ex = true;
//    t_t_n = 6;
#endif
    //スピードをだんだん早く
    if (b_spH > 41) {
        b_spH -= 0.25;
        b_spSC -= 0.25;
        b_spSLR -= 0.25;
    }
    //プレイ続行？ゲームオーバー？
    if ((ex && hit_rlt != HitResultHR) || sc >= 999) {
        // end game
        CCLOG("************* YOU GOT %d HRs %d KM", sc, totalKM);
        this->endGame();
        ((HomeRunGame *)mainGameScene)->finishGame(totalKM);
    } else if ((ex && hit_rlt == HitResultHR) || b_zan >= 0) {
        // continue game
#if TESTING
#else
        this->unschedule(schedule_selector(HomeRunGameLayer::startThrowingBall));
        this->scheduleOnce(schedule_selector(HomeRunGameLayer::startThrowingBall), 1.5f);
#endif
    } else {
        // end game
        CCLOG("************* YOU GOT %d HRs %d KM", sc, totalKM);
        this->endGame();
        ((HomeRunGame *)mainGameScene)->finishGame(totalKM);
    }
//    CCLOG("start throwing ball 2");
#if TESTING
    this->unschedule(schedule_selector(HomeRunGameLayer::startThrowingBall));
    this->scheduleOnce(schedule_selector(HomeRunGameLayer::startThrowingBall), 1.5f);
#endif
    if (ex) {
        remainLabel->setString("EX");
        float x = 235.f + remainLabel->boundingBox().size.width / 2.f;
        remainLabel->setPosition(ccp(remainLableX, (SCREEN_HEIGHT_HALF - 140.f)));
    } else if (b_zan >= 0) {        
        char value[4];
        sprintf(value, "%d", b_zan);
        remainLabel->setString(value);
        float x = 235.f + remainLabel->boundingBox().size.width / 2.f;
        remainLabel->setPosition(ccp(remainLableX, (SCREEN_HEIGHT_HALF - 140.f)));
    }
}

void HomeRunGameLayer::resetBatter()
{    
    CCSpriteFrame *batterFrame = ((CCSpriteFrameCache *)batterCacher)->spriteFrameByName("batter_new_01.png");
    batterSprite->setDisplayFrame(batterFrame);
}

void HomeRunGameLayer::resetPitcher()
{    
    CCSpriteFrame *pitcherFrame = ((CCSpriteFrameCache *)pitcherCacher)->spriteFrameByName("pitcher_new_01.png");
    pitcherSprite->setDisplayFrame(pitcherFrame);
}

void HomeRunGameLayer::runMissBallAnimation(int type, float b_x)
{
    resultLabel->setVisible(true);
    this->unschedule(schedule_selector(HomeRunGameLayer::resetGame));
    this->scheduleOnce(schedule_selector(HomeRunGameLayer::resetGame), 1.f);
}

void HomeRunGameLayer::setBatterAndBallPosition(float sb_dx)
{
    if (sb_dx > 0) {
        // Neu ball di tu trai qua phai, batter o tren ball va shadow
        this->reorderChild(shadowBallSprite, 0);
        this->reorderChild(ballSprite, 0);
    } else {
        // Neu ball di tu phai qua trai, ball va shadow o tren batter
        this->reorderChild(shadowBallSprite, 1);
        this->reorderChild(ballSprite, 1);
    }
}

void HomeRunGameLayer::newGame()
{
    this->initValue();
    this->resetBallPosition();
    char value[4];
    sprintf(value, "%d", sc);
    hrLabel->setString(value);
    hintMessageSprite->setVisible(false);
    float x = -170.f + hrLabel->boundingBox().size.width / 2.f;
    hrLabel->setPosition(ccp(hrLableX, (SCREEN_HEIGHT_HALF - 136.f)));
    sprintf(value, "%d", b_zan);
    remainLabel->setString(value);
    x = 235.f + remainLabel->boundingBox().size.width / 2.f;
    remainLabel->setPosition(ccp(remainLableX, (SCREEN_HEIGHT_HALF - 140.f)));
    readySprite->setVisible(true);
    this->playReadySound();
    this->scheduleOnce(schedule_selector(HomeRunGameLayer::startThrowingBall), 3.f);
    this->scheduleUpdate();
}

void HomeRunGameLayer::pauseGame()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    this->unscheduleAll();
    this->resetValue();
    ball2Sprite->setVisible(false);
    shadowBall2Sprite->setVisible(false);
    this->resetBallPosition();
    keypadSprite->resetMarker();
    this->resetBatter();
    this->resetPitcher();
    strikeSprite->setVisible(false);
    resultLabel->setVisible(false);
    congratulationSprite->setPosition(ccp(congratulationSpriteX, 0.f));
}

void HomeRunGameLayer::resumeGame()
{
	CCLog("DatPV resumeGame");
    readySprite->setVisible(true);
    CCLOG("keypadSprite true resume");
    keypadSprite->setVisible(true);
    keypadSprite->setKeypadTouchEnabled(true);
    this->scheduleOnce(schedule_selector(HomeRunGameLayer::startThrowingBall), 3.f);
    this->scheduleUpdate();
}

void HomeRunGameLayer::endGame()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    this->unscheduleAll();
}

void HomeRunGameLayer::unscheduleAll()
{
    this->unscheduleAllSelectors();
    this->unscheduleUpdate();    
}

void HomeRunGameLayer::runHomeRunAnimation(float b_hit_X, HomeRunType type)
{
    bm = 222;
    b2_bm = 0;
    sb2_bm = 0;
    switch (type) {
        case HomeRunTypeStraight:
            b2_x = b_hit_X;
            b2_y = ballSprite->getPosition().y;
            b2_dx = 0.f;//(r * 100) / 18.f;
            b2_dy = ((SCREEN_HEIGHT_HALF * 3 / 2.f) - b2_y) / 18.f;
            b2_ts = 0.67 / 18.f;
            sb2_x = b_hit_X;
            sb2_y = b2_y - 90;
            sb2_dx = 0.f;//(r * 100) / 30.f;
            sb2_ts = 0.27 / 30.f;
            sb2_dy = (sb_maxY_HR - sb2_y) / 120.f;//cho di chuyen toi het duong danh
            break;
        case HomeRunTypeLeft1:
        case HomeRunTypeRight1:
            b2_x = b_hit_X;
            b2_y = ballSprite->getPosition().y;
            b2_dx = (r * 50) / 18.f;
            b2_dy = ((SCREEN_HEIGHT_HALF * 3 / 2.f) - b2_y) / 18.f;
            b2_ts = 0.53 / 18.f;
            sb2_x = b_hit_X;
            sb2_y = b2_y - 90;
            sb2_ts = 0.27 / 24.f;
            sb2_dx = (r * 90) / 84.f;
            sb2_dy = (sb_maxY_HR - sb2_y) / 84.f;// cho di chuyen toi het duong banh
            break;
        case HomeRunTypeLeft2:
        case HomeRunTypeRight2:
            b2_x = b_hit_X;
            b2_y = ballSprite->getPosition().y;
            b2_dx = (r * 50) / 18.f;
            b2_dy = ((SCREEN_HEIGHT_HALF * 3 / 2.f) - b2_y) / 18.f;
            b2_ts = 0.53 / 18.f;
            sb2_x = b_hit_X;
            sb2_y = b2_y - 90;
            sb2_ts = 0.27 / 24.f;
            sb2_dx = (r * 90) / 84.f;
            sb2_dy = (sb_maxY_HR - sb2_y) / 84.f;// cho di chuyen het duong banh
            break;
        default:
            break;
    }
    ball2Sprite->setPosition(ccp(b2_x, b2_y));
    ball2Sprite->setScale(0.6f);
    ball2Sprite->setVisible(true);
    shadowBall2Sprite->setPosition(ccp(sb2_x, sb2_y));
    shadowBall2Sprite->setScale(0.6f);
    shadowBall2Sprite->setVisible(true);

}

void HomeRunGameLayer::runFoulAnimation(float b_hit_X, HomeRunType type)
{
    bm = 150;
    b2_bm = 0;
    sb2_bm = 0;
    switch (type) {
        case HomeRunTypeFoul1:
        case HomeRunTypeFoul2:
            b2_x = b_hit_X;
            b2_y = ballSprite->getPosition().y;
            b2_dx = (1.5 * r * SCREEN_HEIGHT_HALF) / 90.f;
            b2_dy = ((SCREEN_HEIGHT_HALF * 15 / 2.f) - b2_y) / 90.f;//(sb_maxY_HR - b2_y) / 90.f
            b2_ts = 0.2 / 90.f;//0.4
            sb2_x = b_hit_X;
            sb2_y = b2_y - 90;
            sb2_dx = (1.5 * r * SCREEN_HEIGHT_HALF) / 90.f;
            sb2_dy = (sb_maxY_HR / 2.f - sb2_y) / 90.f;
            sb2_ts = 0.2 / 90.f;//0.4
            break;
        default:
            break;
    }
    ball2Sprite->setPosition(ccp(b2_x, b2_y));
    ball2Sprite->setScale(0.6f);
    ball2Sprite->setVisible(true);
    shadowBall2Sprite->setPosition(ccp(sb2_x, sb2_y));
    shadowBall2Sprite->setScale(0.6f);
    shadowBall2Sprite->setVisible(true);

}

void HomeRunGameLayer::playReadySound()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.mp3");
}

void HomeRunGameLayer::playDisappointedSound()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("disappoint.mp3");
}

void HomeRunGameLayer::playHomeRunSound()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("homerun.mp3");
}

void HomeRunGameLayer::playBatSound()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bat.mp3");
}

void HomeRunGameLayer::playFoulSound()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("foul_whistle.mp3");

}

HomeRunGameLayer::~HomeRunGameLayer()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, KEYPAD_TOUCHED_NOTIFICATION);
    delete batterSprite;
    delete pitcherSprite;
    delete foulSprite;
    delete hintHRSprite;
    delete batterAnim;
    delete pitcherAnim;
    delete homeRunWordAnim;
    delete foulAnim;
    delete hintAnim;
}
void HomeRunGameLayer::showHomeRunHint()
{
	hintHRSprite->setVisible(true);
    hintHRSprite->runAction(CCSequence::create(CCRepeat::create(CCAnimate::create(hintAnim), 5), NULL, NULL));

}
void HomeRunGameLayer::hideHomeRunHint()
{
	hintHRSprite->stopAllActions();
	hintHRSprite->setVisible(false);
}
