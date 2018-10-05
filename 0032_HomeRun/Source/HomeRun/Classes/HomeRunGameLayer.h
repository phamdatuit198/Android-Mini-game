//
//  HomeRunGameLayer.h
//  homerun
//
//  Created by admin on 5/14/13.
//
//

#ifndef __homerun__HomeRunGameLayer__
#define __homerun__HomeRunGameLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCControlButton.h"
#include "kmResultSprite.h"
#include "ScoreSprite.h"
#include "KeypadLayer.h"

typedef enum {
    ThrowingTypeStraight,
    ThrowingTypeLoose,
    ThrowingTypeLooseCurve,
    ThrowingTypeTurningRound,
    ThrowingTypeHabit,
    ThrowingTypeBoomerang,
} ThrowingType;

typedef enum {
    ThrowingStateNone,
    ThrowingStateStarted,
    ThrowingStateFlying,
    ThrowingStateMissBall,
    ThrowingStateHR,
    ThrowingStateFoul,
} ThrowingState;

typedef enum {
    HitResultNone,
    HitResultHit,
    HitResultHR,
    HitResultMiss,
    HitResultFoul,
} HitResult;

typedef enum {
    HomeRunTypeStraight,
    HomeRunTypeLeft1,
    HomeRunTypeRight1,
    HomeRunTypeLeft2,
    HomeRunTypeRight2,
    HomeRunTypeFoul1,
    HomeRunTypeFoul2,
} HomeRunType;

class HomeRunGameLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HomeRunGameLayer);
    
    void *mainGameScene;
    
    void newGame();
    void pauseGame();
    void resumeGame();
    //DatPV
    void initMediumDesign();
    void initLargeDesign();
    int batterX,batterY;
    int pitcherX,pitcherY;
    int readyY;
    int congratulationSpriteX;
    int strikeSpriteY;
    int resultLableY;
    int resultLableX;
    int keyPadX, keyPadY;
    int hrX,hrY;
    int countX,countY;
    float hrLableX,hrLableY;
    float remainLableX,remainLableY;
    float homeRunWord1_X;
    float homeRunWord2_X;
    float homeRunWord3_X;

    float B_UHY ;
    float B_UHYS;
    float B_MHY;
	float B_DHY;

	float B_SY; // diem bat dau cua trai banh
	float SB_SY;  // diem bat dau cua bong trai banh
	float SB_HY;  // diem dich cua bong trai banh

	float foulSpriteY;
	float strikeMessageSpriteY;
	float strikeMessageSpriteX;
	cocos2d::CCSize size;

//#define sb_HY       (-SCREEN_HEIGHT_HALF + 80)//111//215
private:
    KeypadLayer *keypadSprite;
    cocos2d::CCSprite *batterSprite;
    cocos2d::CCSprite *pitcherSprite;
    cocos2d::CCSprite *ballSprite;
    cocos2d::CCSprite *shadowBallSprite;
    cocos2d::CCSprite *readySprite;
    cocos2d::CCSprite *strikeSprite;
    cocos2d::CCSprite *congratulationSprite;
    cocos2d::CCSprite *ball2Sprite;
    cocos2d::CCSprite *shadowBall2Sprite;
    cocos2d::CCSprite *homeRunWord1;
    cocos2d::CCSprite *homeRunWord2;
    cocos2d::CCSprite *homeRunWord3;
    cocos2d::CCSprite *foulSprite;
    
    cocos2d::CCSprite *hintHRSprite;
    cocos2d::CCSprite *hintMessageSprite;

    cocos2d::CCLabelTTF *resultLabel;
    cocos2d::CCLabelTTF *hrLabel;
    cocos2d::CCLabelTTF *remainLabel;
    
    void *batterCacher;
    void *pitcherCacher;
    
    cocos2d::CCAnimation *batterAnim;
    cocos2d::CCAnimation *pitcherAnim;
    cocos2d::CCAnimation *homeRunWordAnim;
    cocos2d::CCAnimation *foulAnim;
    cocos2d::CCAction *homeRunWordAnimateAction;
    
    cocos2d::CCAnimation *hintAnim;

    void initValue();
    void resetValue();
    void touchedKeypadNotification(CCObject* notificationObj);
    void startThrowingBall();
    void throwBall();
    void update(float dt);
    
    void homeRun();
    
    void updateBallSpritePositionAndScale();
    void updateShadowBallSpritePositionAndScale();
    
    void updateBallSpriteFlyingPositionAndScale();
    void updateShadowBallSpriteFlyingPositionAndScale();
    
    void updateBallSpriteMissBallPositionAndScale();
    void updateShadowBallSpriteMissBallPositionAndScale();
    
    void updateBallSpriteHomeRunPositionAndScale();
    void updateShadowBallSpriteHomeRunPositionAndScale();
    
    void updateBallSpriteFoulPositionAndScale();
    void updateShadowBallSpriteFoulPositionAndScale();
    
    void runBatterAnimation();
    void runHomeRunAnimation(float b_hit_X, HomeRunType type);
    void runFoulAnimation(float b_hit_X, HomeRunType type);
    
    void showStrike();
    void showCongratulation();
    void showFoul();
    void resetGame();
    void resetBallPosition();
    void setState();
    void setValue();
    void showHomeRunHint();
    void hideHomeRunHint();
    
    void resetBatter();
    void resetPitcher();
    
    void unscheduleAll();
    void endGame();
    
    void runMissBallAnimation(int type, float b_x);
    void setBatterAndBallPosition(float sb_dx);
    
    void playReadySound();
    void playDisappointedSound();
    void playHomeRunSound();
    void playBatSound();
    void playFoulSound();
    
    virtual ~HomeRunGameLayer();
    
    ThrowingState t_state;
    ThrowingType t_typ;
    int t_t_n;  // Normal: 3, EX: 6
    int b_sp;
    int r;
    float wr;
    float mth, th;
    
    float sb_HX, b_HY;
    
    float b_dx, b_dy, b_tx, b_ty, b_ts;
    float sb_dx, sb_dy, sb_ts;
    
    int b_c;
    
    bool htg_flg;
    int mkn;
    HitResult hit_rlt;
    
    int bm, b2_bm, sb2_bm;
    float b2_x, b2_y, sb2_x, sb2_y, b2_ts, sb2_ts;
    int b2_bdy;
    float b2_dx, b2_dy, sb2_dx, sb2_dy;
    
    int b_zan, b_ch, sc;
    long totalKM;
    bool ex;
    
    float b_spH, b_spSLR, b_spSC;
    
    float ts, ls;
    
    float hsc;
    
    HomeRunType hrType;

};

#endif /* defined(__homerun__HomeRunGameLayer__) */
