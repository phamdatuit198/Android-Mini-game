//
//  ProjectileAction.h
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/20/13.
//
//

#ifndef __Snow_6_cocos2dx__ProjectileAction__
#define __Snow_6_cocos2dx__ProjectileAction__

#include <iostream>
#include "cocos2d.h"

class Ball;
class ProjectileAction : public cocos2d::CCRepeatForever
{
public:
    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    virtual void update(float t);
    float elapse;
    cocos2d::CCPoint initialPosition;
    cocos2d::CCNode *target;
    float v;
    float angle;
    float distance;
    float gravitationalAcceleration;
    
    float y0;
    bool isfalldown;
    bool isReachGoal;
    
    ProjectileAction();
    ~ProjectileAction();
    
    bool initWithDuration(float,float,float,float);
    
    void updateBall();
    CCActionInterval* initParapol(float,float,float,float);
};

#endif /* defined(__Snow_6_cocos2dx__ProjectileAction__) */
