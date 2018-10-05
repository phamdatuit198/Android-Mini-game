//
//  Ball.h
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/16/13.
//
//

#ifndef __Snow_6_cocos2dx__Ball__
#define __Snow_6_cocos2dx__Ball__

#include <iostream>
#include "cocos2d.h"

#define DISTANCE 300.0f

enum BALL_STATE {
    NONE = 0,
    GOAL = 1,
    EXGOAL = 2
    };

class DemoScene;
class Ball : public cocos2d::CCSprite
{
//    float dx;
//    int fl;
//    int bectx;
//    //
//    float scale;
//    float px;
//    float py;
//    float pz;
//    float _xscale;
//    float _yscale;
    
    int status;
    //
    float velocity_y;
    float velocity_x;
    
    float beginActionTime;
    float elapse;
    float v;
    float angle;
    float gravitationalAcceleration;
    float getTimeTick();
    
    float originalScale;
    cocos2d::CCPoint originalPoint;
private:
    cocos2d::CCSequence * move(cocos2d::CCPoint point);
    cocos2d::CCSequence * scale();
    cocos2d::CCSequence * changeAnimation(float angle, float theVelocity, cocos2d::CCArray *arrAction);
    //
    void updatePosition(float dt);
    
//    void reachGoal();
public:
   
    Ball();
    virtual ~Ball();
    static Ball* create(const char *pSpriteFrame);
//
    void stopMoveball();
    void reset();
    void throwBall(float angle,float theVelocity, cocos2d::CCArray *arrAction);
    cocos2d::CCSprite *image;
    
    void reachBasket();
    void beginFallIntoBasket();
    
    void moveBall();
//    void play();
//    
    DemoScene *_root;
};

#endif /* defined(__Snow_6_cocos2dx__Ball__) */
