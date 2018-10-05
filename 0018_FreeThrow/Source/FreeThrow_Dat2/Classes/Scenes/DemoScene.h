//
//  DemoScene.h
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/10/13.
//
//

#ifndef __Snow_6_cocos2dx__DemoScene__
#define __Snow_6_cocos2dx__DemoScene__
#include "CCMyScene.h"
#include <iostream>
using namespace cocos2d;

enum GAME_STATE {
    INIT_GAME = 0,
    START_POWER = 1,
    SHOOT = 2,
    END_GAME = 3
};

class Ball;
class Notice;
class BarTimeGameLayer;
class Basket;
class DemoScene :public CCMyScene
{
    bool ballReset;
    bool previous_Exelent;
    bool current_Exelent;
    int numberThrowNormalMode;//bien dem so lan nem trong NORMAL MODE
    
    static DemoScene* instance;

    int vec;
    
    int power;
    int power_num;
    
    int pin;
    Ball *ball;
    CCSprite* boardSprite;
//    Notice *noticeBoard;
    CCSprite* powerSprite;
    CCSprite* vecSprite;
    CCSprite* lineSprite;
    bool countdowned;
    
    cocos2d::CCArray *arrAction;
    cocos2d::CCArray *arrBasketAction;
    cocos2d::CCArray *arrActionExcellent;
    
private:
    int getBallWeight(int ballIndex);
    bool nextSence();
    void endGame();
    void updateGame(int dt);
public:
    

    static DemoScene* getInstance();
    CCLabelTTF *scoreLbl;
    CCLabelTTF *senseLbl;
    
    BarTimeGameLayer *bar;
    Basket *basket;
    
    bool isGoal;
    bool isExelentGoal;
    bool goF;
    int st;
    int cg;
    int dy;
    int jumpf;
    int missF;
    int bp;
    bool EXgF;
    int thcnt;
    //
    bool isDown;
    
    DemoScene();
    ~DemoScene();
    static cocos2d::CCScene* scene();
    virtual bool init();    
    CREATE_FUNC(DemoScene);
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
//    virtual void update(float dt);
//    float getTimeTick();
//    float beginTimeTick;
//    float maxTime;
//    float minTime;
    void updateProgressBar();
    void SampleSelector(CCNode *sender, void *data);
    cocos2d::CCSpriteBatchNode* iCreateAnimation(const char *plistFile, const char *pngFile);
    cocos2d::CCSpriteBatchNode* iCreateBasketAnimation(const char *plistFile, const char *pngFile);
    
    // Luan added 29/05/2013
    cocos2d::CCSpriteBatchNode* iCreateExcellentAnimation(const char *plistFile, const char *pngFile);
    // Luan added 30/05/2013
    void showingINTopBanner();
    void showingOUTTopBanner();
    void showingRELEASETopBanner();
    void showingEXCELLENTTopBanner();
    void finishedShowingTopBanner(cocos2d::CCNode *sender);

//    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    //void CCLayer::ccTouchBegan(CCTouch *touch, CCEvent *event);
    
    void ballInGoal();
    void ballBeginFallDownToGoal();
    void resetZorder();

    CCSize size;
      void initPositionMedium(cocos2d::CCSize);
      void initPositionLarge(cocos2d::CCSize);
      void setVecSprite();
      float sizeText;
      int BeginBallX,BeginBallY;
      int BasketX,BasketY;
      int PowerX,PowerY;
      int VecLineX,VecLineY;
      int VecX,VecY;
      int scoreLableX,scoreLableY;
      int boardX,boardY;
      int kInSpriteX;
      int kInSpriteY;
      int barX,barY;
      int widthBar;
      CCSprite *showEX;
      CCSprite *showRelease;
      CCSprite *showOut;
      CCSprite *showIn;
};

#endif /* defined(__Snow_6_cocos2dx__DemoScene__) */
