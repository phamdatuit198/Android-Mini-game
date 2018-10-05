//
//  ballSnowAnimation.h
//  Snow_6_cocos2dx
//
//  Created by antl on 4/18/13.
//
//

#ifndef Snow_6_cocos2dx_ballSnowAnimation_h
#import "cocos2d.h"
#define Snow_6_cocos2dx_ballSnowAnimation_h
using namespace cocos2d;
class ballSnowAnimation : public cocos2d::CCSprite
{
    CCSprite *BALL_Texture;
    char* nameB;
    CCSpriteBatchNode *spreetsheet;
    char* nameBall;
    char *plist;
    char *filePNG;
    CCPoint tempDimention;
    CCPoint tempAnchorpoint;
    public:
    ballSnowAnimation();
    ~ballSnowAnimation();
    CCSpriteBatchNode* iCreateBallAnimation(const char * iName, cocos2d::CCPoint dimensions,cocos2d::CCPoint iAnchorPoint,float scale,int type);
    
    void BALLAction();
    CCArray *ArrayShooting;
    CCArray *ArrayBeShot;
    
    // type2
    CCArray *Array_ball;
    CCArray *Array_blow;
    
    void BeShot();
    void shooting(int index);
    void hiddenBall();
    void showBall();
    void endShoting();
    void beginSnowShoot();
    /// show text
    void showText();
};

#endif
