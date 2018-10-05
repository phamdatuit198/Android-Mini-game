//
//  BarTimeGame.h
//  Yougashi
//
//  Created by dattd on 5/16/13.
//
//

#ifndef Yougashi_BarTimeGame_h
#define Yougashi_BarTimeGame_h


#include "cocos2d.h"
USING_NS_CC;
class BarTimeGameLayer:public cocos2d::CCLayer{
    
public:
    int timeGame;
    CCSize sizeBg;
    CREATE_FUNC(BarTimeGameLayer);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCLayerColor *, _progressTime, ProgressTime);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite *, _progressTime1, ProgressTime1);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF *, _lblTime, LblTime);
    
    virtual ~BarTimeGameLayer();
    virtual bool init();
    void executeUpdateProgressTime(int value);
    void animationTimeRemaining();
    void stopAnimationTimeRemaining();
    void changeProgressTime(int value);
};

#endif
