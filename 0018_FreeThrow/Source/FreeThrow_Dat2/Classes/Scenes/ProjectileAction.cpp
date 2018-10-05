//
//  ProjectileAction.cpp
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/20/13.
//
//

#include "ProjectileAction.h"
#include "Ball.h"

// set target position first

using namespace cocos2d;

ProjectileAction::ProjectileAction() {
	y0 = 0;
	isReachGoal = false;
	isfalldown = false;
}
ProjectileAction::~ProjectileAction() {

}

void ProjectileAction::startWithTarget(cocos2d::CCNode *pTarget) {

	this->elapse = 0;
	this->initialPosition = pTarget->getPosition();
	this->target = pTarget;
}

void ProjectileAction::update(float tt) {
	this->elapse = this->elapse + tt;

	float t = this->elapse;
	float theta = CC_DEGREES_TO_RADIANS(angle);
	float v0 = this->v;
	float g = this->gravitationalAcceleration;
	double x = v0 * cos(theta) * t;
	double y = v0 * sin(theta) * t - 0.5 * g * t * t;
	if (y > 10 && y < y0) {
		isfalldown = true;
		((Ball*) this->target)->beginFallIntoBasket();
	}
	y0 = y;
//    CCLOG("DISTANCE X --- %f", x);
//    CCLOG("DISTANCE Y --- %f", y);
	this->target->setPosition(
			ccp(this->initialPosition.x + (float) x,
					this->initialPosition.y + (float) y));

	// let check if ball reach goal
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (size.width == 720) {
		if (!isReachGoal && isfalldown && y <= DISTANCE + 100) {
			isReachGoal = true;
			((Ball*) this->target)->reachBasket();
		}
	} else {
		if (!isReachGoal && isfalldown && y <= DISTANCE) {
			isReachGoal = true;
			((Ball*) this->target)->reachBasket();
		}
	}
	// out of board
	if (y < 0) {
//        cocos2d::CCLog("out of board");
		this->target->stopAllActions();
		((Ball*) this->target)->stopMoveball();

		y0 = 0;
		y = 0;
		isReachGoal = false;
		isfalldown = false;
	}
}

bool ProjectileAction::initWithDuration(float duration, float angle,
		float theVelocity, float g) {
	if (!CCActionInterval::initWithDuration(duration)) {
		return false;
	}

	this->v = theVelocity;
	if (angle >= 80 && angle <= 100) {
		this->angle = 90;
	} else {
		this->angle = angle;
	}
	this->gravitationalAcceleration = g;
	return true;
}

//void ProjectileAction::updateBall()
//{
////    this->elapse=this->elapse+tt;
//    
////    float t = this->getelapse;
//    float t = this->getElapsed();
//    float theta = CC_DEGREES_TO_RADIANS(angle);
//    float v0 = this->v;
//    float g = this->gravitationalAcceleration;
//    double x = v0 * cos(theta) * t;
//    double y = v0 * sin(theta) * t - 0.5 * g * t * t ;
//    this->target->setPosition(ccp(this->initialPosition.x + (float)x, this->initialPosition.y + (float)y));
//    
//}
//
//cocos2d::CCActionInterval* ProjectileAction::initParapol(float distance,float angle,float theVelocity,float g)
//{
//    this->v=theVelocity;
//    this->angle=angle;
//    this->gravitationalAcceleration=g;
//    this->distance = distance;
//    
//    cocos2d::CCRepeatForever *repeatForeverAction = cocos2d::CCRepeatForever::create(cocos2d::CCCallFuncN::create( this,callfuncN_selector(ProjectileAction::update)));
//    return repeatForeverAction;
//
//}
