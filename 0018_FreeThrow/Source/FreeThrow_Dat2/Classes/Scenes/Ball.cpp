//
//  Ball.cpp
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/16/13.
//
//

#include "Ball.h"
#include "ProjectileAction.h"
#include "DemoScene.h"
#include "BarTimeGame.h"

#define ACTION_TAG 150

const float GRAVITY = 20.0f;
using namespace cocos2d;
Ball::Ball()
{
//    dx=0;
//    px=0;
//    py=80;
//    pz=0;
//    fl=200;
//    bectx=120;
    status = NONE;
}

Ball::~Ball()
{
    
}

//void Ball::play()
//{
//    //上がる処理
//    // processing up ball
//    if(_root->jumpf==1){
//        py-=_root->dy*2;
//        //kage._y+=_root.dy*2
//        _root->dy=_root->dy-_root->cg;
//        if(_root->dy<=0){
//            _root->jumpf=2;
//            _root->dy=3;//落ちる初速// initial velocity falling
//        }
////        //エクセレントゴール用キラキラ生成// excellent ball
////        if(_root.EXgF){
////            tellTarget("/kira"){
////                duplicateMovieClip("kira_m","kira_m"add k,1000-k)
////                eval("kira_m"add k)._x=_root.ball._x-10+random(20)
////                eval("kira_m"add k)._y=_root.ball._y
////                eval("kira_m"add k)._xscale=eval("kira_m"add k)._yscale=_root.ball._xscale
////                tellTarget("/kira/kira_m"add k)gotoAndPlay(2)
////                k++;
////            }}
//    }
//    
//    //落ちる処理// ball falling
//    if(_root->jumpf==2){
//        py+=_root->dy;
//        //kage._y-=_root.dy
//        _root->dy=_root->dy+_root->cg;
//        /*if(py>=80){//着地
//         py=80
//         kage._y=0
//         _root.dy=10
//         }*/
//    }
//    
//    if(_root->missF!=1){// and (_x<_root.goal1._x+_root.goal1._width/2 and _x>_root.goal1._x-_root.goal1._width/2)){
//        if(pz<=200)pz+=_root->bp;//10
//    }else{
//        pz+=_root->bp;//10
//    }
//    //TODO call("move")
//    this->move();
//    
//    this->reachGoal();
//}
//
//void Ball::reachGoal()
//{
//    if(_root->jumpf==2 and py>=240){//if(pz>=400){
//        _root->jumpf=0;
////        if(_root.thcnt<=5){//通常モード
////            if(_root.EXgF){//エクセレントゴールで投球回数やそこまでのミスに関係なくエクストラモード突入
////                if(_root.combo<_root.combolm)_root.combo++;
////                _root.score=5;
////                _root.thcnt=5;
////                for(i=1;i<=5;i++){
////                    eval("/:scoreF" add i)=1
////                }
////                _root.exF=false;;
////            }else if(_root.missF==0){
////                _root.score++;
////                eval("/:scoreF" add _root.thcnt)=1
////            }else{
////                _root.exF=true;
////                eval("/:scoreF" add _root.thcnt)=2
////            }
////        }else{//延長モード
////            if(_root.missF==0){
////                if(_root.EXgF){//エクセレントゴールでスコア倍増
////                    if(_root.combo<_root.combolm){
////                        _root.combo++;//コンボは100回まで
////                        _root.bonuscF=true;
////                    }
////                    if(_root.score<99999999){
////                        if(_root.combo==1){
////                            _root.score+=2
////                        }else{
////                            _root.score+=_root.combo*_root.combo;
////                        }
////                    }else{
////                        _root.score=99999999
////                    }
////                    _root.thcnt++;//投球回数インクリメント
////                }else{
////                    if(_root.combo>0){
////                        _root.combo--;
////                        _root.bonuscF=true;
////                    }
////                    if(_root.score<99999999)_root.score++;
////                }
////                //eval("/:scoreF" add _root.thcnt)=1
////            }else{
////                _root.exF=true;
////                //eval("/:scoreF" add _root.thcnt)=2
////            }
////        }
////        _root.thcnt++;//投球回数インクリメント
////        tellTarget("/scoreh")gotoAndPlay(1)
////        if(_root.thcnt>5 and _root.exF){//ゲームオーバー判定
////            //tellTarget("/scoreh")gotoAndPlay("over")
////            tellTarget("/")gotoAndPlay("over")
////            stop();
////        }else{
////            tellTarget("/pow_mc")gotoAndPlay(1)
////            tellTarget("/sw")gotoAndPlay(1)
////            tellTarget("/")gotoAndPlay("set")
////            gotoAndStop(1)
////            //removeMovieClip("")
////        }
//    }else{
//        this->play();
//    }
//}

Ball* Ball::create(const char *pSpriteFrame){
    Ball *pSprite = new Ball();
    if (pSprite && pSprite->initWithFile(pSpriteFrame)){
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
     return NULL;
}

//cocos2d::CCSequence * Ball::scale()
//{
//    return NULL;
//}

//cocos2d::CCSequence * Ball::changeAnimation(float angle, float theVelocity, cocos2d::CCArray *arrAction)
//{   
//    //
//}

//cocos2d::CCSequence * Ball::move(cocos2d::CCPoint point)
//{
//    
//}

void Ball::stopMoveball()
{
    this->stopAllActions();
    this->setVisible(false);
    cocos2d::CCDelayTime *delayTime = cocos2d::CCDelayTime::create(0.5f);
    
    CCArray* actions = CCArray::create();
    actions->addObject(delayTime);
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(Ball::reset)));
    CCSequence *sequenceMoveAction = CCSequence::create(actions);
    delete actions;
    
    cocos2d::CCRepeat *repeatAction = cocos2d::CCRepeat::create(sequenceMoveAction, 1);
    this->runAction(repeatAction);
}

void Ball::reset()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setVisible(true);
    this->setTexture(this->getTexture());
    if(size.width == 720)
    	this->setScale(1.5f);
    else
    	this->setScale(1.0f);
    this->setPosition(originalPoint);
    _root->st = INIT_GAME;
    _root->isDown = false;
    _root->bar->setVisible(true);
    _root->resetZorder();
    
}
float Ball::getTimeTick(){
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec/1000);
    return (float) millisecs;
}

void Ball::moveBall()
{
    this->elapse += 0.1;
    
    float t = this->elapse;
    float theta = CC_DEGREES_TO_RADIANS(angle);
    float v0 = this->v;
    float g = this->gravitationalAcceleration;
    double x = v0 * cos(theta) * t;
    double y = v0 * sin(theta) * t - 0.5 * g * t * t ;
    this->setPosition(ccp(this->originalPoint.x + (float)x, this->originalPoint.y + (float)y));
    
    // out of board
//    if (x < -160 || x > 160) {
//        CCLog("out of board");
//        this->stopAllActions();
//        this->reset();
//    }
}

void Ball::throwBall(float angle,float theVelocity, cocos2d::CCArray *arrAction)
{
    //
    status = NONE;
    if (_root->isGoal) {
        status = GOAL;
    }
    if (_root->isExelentGoal) {
        status = EXGOAL;
    }
    //
    originalScale = this->getScale();
    originalPoint = this->getPosition();
    
    this->angle = angle;
    this->v = theVelocity;
    //move
    ProjectileAction *projectTileAction = new ProjectileAction();
    projectTileAction->startWithTarget(this);
    float t = DISTANCE/theVelocity + 0.18f*theVelocity;
    projectTileAction->initWithDuration(t, angle, theVelocity, 9.8f);
    CCArray* actions = CCArray::create();
    actions->addObject(projectTileAction);
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(Ball::stopMoveball)));
    CCSequence *sequenceMoveAction = CCSequence::create(actions);
    delete actions;
//    CCArray* actions = CCArray::create();
//    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(Ball::moveBall)));
//    CCSequence *sequenceMoveAction = CCSequence::create(actions);
//    CCRepeatForever *repeatMoveAction = CCRepeatForever::create(sequenceMoveAction);
//    delete actions;
    //scale
    cocos2d::CCScaleBy *scaleAction = cocos2d::CCScaleBy::create(10.f, 0.05f);
    //rotate
    cocos2d::CCAnimation *ballAnim = cocos2d::CCAnimation::createWithSpriteFrames(arrAction, 0.03f);
    CCArray* rotateAction = CCArray::create();
    rotateAction->addObject(CCAnimate::create(ballAnim));
//    CCFiniteTimeAction* actionSchedule = CCSequence::create(rotateAction);
    CCSequence *sequenceAction = CCSequence::create(rotateAction);
    CCRepeatForever *repeatForeverAction = CCRepeatForever::create(sequenceAction);
    repeatForeverAction->setTag(ACTION_TAG);
    
    //run action
//    beginActionTime=this->getTimeTick();
//    CCLog("%f", beginActionTime);
    this->runAction(sequenceMoveAction);
    this->runAction(scaleAction);
    this->runAction(repeatForeverAction);
    
    delete rotateAction;
//    //
//    CCArray* actions = CCArray::create();
//    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(ballSnowAnimation::showBall)));
//    CCAnimation *ballAnim_1 = CCAnimation::createWithSpriteFrames(Array_ball, 0.1f);
//    
//    
//    actions->addObject(CCAnimate::create(ballAnim_1));
//    actions->addObject(CCMoveTo::create(0.3, P));
//    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(ballSnowAnimation::showText)));
//    CCAnimation *ballAnim_2 = CCAnimation::createWithSpriteFrames(Array_blow, 1.0f);
//    actions->addObject(CCAnimate::create(ballAnim_2));
//    actions->addObject(CCDelayTime::create(1.0f));
//    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(ballSnowAnimation::endShoting)));
//    CCFiniteTimeAction* actionSchedule = CCSequence::create(actions);
//    BALL_Texture->runAction(actionSchedule);
//    delete actions;
}

void Ball::reachBasket()
{
    _root->ballInGoal();
}

void Ball::beginFallIntoBasket()
{
    _root->ballBeginFallDownToGoal();
}
