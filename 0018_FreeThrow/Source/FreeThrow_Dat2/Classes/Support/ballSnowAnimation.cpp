//
//  ballSnowAnimation.cpp
//  Snow_6_cocos2dx
//
//  Created by antl on 4/18/13.
//
//

#include "ballSnowAnimation.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Scenes/GameBoard.h"

ballSnowAnimation::ballSnowAnimation()
{
    
    
   // nameBall=new char;
    
    ArrayShooting = new CCArray();
    ArrayBeShot = new CCArray();
    /// new ball
    Array_blow=new  CCArray();
    Array_ball=new CCArray();
}
ballSnowAnimation::~ballSnowAnimation()
{
   
   
    delete ArrayShooting;
    delete ArrayBeShot;
    
    //// new ball
    delete Array_ball;
    delete Array_blow;
    
}

CCSpriteBatchNode* ballSnowAnimation::iCreateBallAnimation(const char * iName, cocos2d::CCPoint dimensions,cocos2d::CCPoint iAnchorPoint,float scale ,int type)
{

    tempDimention=dimensions;
    tempAnchorpoint=iAnchorPoint;
    CCLog("++++++++++++++++++++++++++++++ :%s",iName);
    nameB= new char;
    nameBall=new char;
    plist =new char;
    filePNG =new char;
    sprintf(nameBall, "%s", iName);/// saving name ball
    sprintf(plist, "%s.plist", nameBall);
    sprintf(filePNG, "%s.png", nameBall);
    
    
    CCLog("plist :         %s",plist);
    CCLog("filePNG :      %s",filePNG);
    CCLog("iName :         %s",nameBall);
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist);
    spreetsheet = CCSpriteBatchNode::create(filePNG);
    sprintf(nameB,"%s1.png",nameBall);
    BALL_Texture = CCSprite::createWithSpriteFrameName(nameB);
     BALL_Texture->setPosition(tempDimention);
    BALL_Texture->setScale(scale);
    spreetsheet->addChild(BALL_Texture);
    

        for(int i = 0; i <= 6; i++)
        {
            char name[32] = {0};
            sprintf(name, "%s%d.png",iName,i);
            
            if(i==1)
            {
                Array_ball->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
            }
            else if(i==0)
            {
                Array_blow->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
            }
            
            if(i!=0)
            {
                ArrayBeShot->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
            }
            
        }
        
    BALL_Texture->setScale(1.3f);
    BALL_Texture->setVisible(false);
    
    
    
    delete filePNG;
    delete nameBall;
    delete plist;
    delete nameB;    
    
    return spreetsheet;
    
}

void ballSnowAnimation::shooting(int index)
{
    CCLog("Shoot . ........ ....%d",index);
    CCPoint P;
    if(index==0)
    {
        P=CCPoint(50+60,730+50);
    }
    else if(index==1)
    {
         P=CCPoint(250+60, 700+30+50);
    }
    else if(index==2)
    {
         P=CCPoint(400+60, 700+30+50);
    }
    else if(index==3)
    {
         P=CCPoint(55+70, 520+30+50);
    }
    else if(index==4)
    {
         P=CCPoint(225+70, 520+30+50);
    }
    else if(index==5)
    {
         P=CCPoint(430+70, 520+30+50);
    }
    else if(index==6)
    {
         P=CCPoint(20+80, 320+30+70);
    }
    else if(index==7)
    {
         P=CCPoint(240+80, 320+30+70);
    }
    else if(index==8)
    {
         P=CCPoint(420+80, 320+30+70);
    }
  
  
    CCArray* actions = CCArray::create();
     actions->addObject(CCCallFuncN::create( this,callfuncN_selector(ballSnowAnimation::showBall)));
    CCAnimation *ballAnim_1 = CCAnimation::createWithSpriteFrames(Array_ball, 0.1f);
    
   
    actions->addObject(CCAnimate::create(ballAnim_1));
    actions->addObject(CCMoveTo::create(0.3, P));
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(ballSnowAnimation::showText)));
    CCAnimation *ballAnim_2 = CCAnimation::createWithSpriteFrames(Array_blow, 1.0f);
    actions->addObject(CCAnimate::create(ballAnim_2));
    actions->addObject(CCDelayTime::create(1.0f));
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(ballSnowAnimation::endShoting)));
    CCFiniteTimeAction* actionSchedule = CCSequence::create(actions);
    BALL_Texture->runAction(actionSchedule);
    delete actions;

}


void ballSnowAnimation::showText()
{
    
    GameBoard *gb=GameBoard::GetGameBoardInstance();
    gb->ShowText();
    gb=NULL;

}

void ballSnowAnimation::BeShot()
{
    BALL_Texture->setVisible(true);
    CCAnimation *ballAnim = CCAnimation::createWithSpriteFrames(ArrayBeShot, 0.1f);
    CCArray* actions = CCArray::create();
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(ballSnowAnimation::beginSnowShoot)));    
    actions->addObject(CCAnimate::create(ballAnim));
    actions->addObject(CCDelayTime::create(1.0f));
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(ballSnowAnimation::hiddenBall)));
    CCFiniteTimeAction* actionSchedule = CCSequence::create(actions);
    BALL_Texture->runAction(actionSchedule);
    
    
    delete actions;

    
}
#pragma mark - ME SHOOT SNOW BEGIN
void ballSnowAnimation::showBall()
{
    // CCLog("hidden ball");
    GameBoard *gb=GameBoard::GetGameBoardInstance();
    gb->ManShotedSnowManBeginInstance();
    gb=NULL;
    
    
    BALL_Texture->setVisible(true);
    BALL_Texture->setPosition(ccp(300, 150));
}
void ballSnowAnimation::endShoting()
{
    BALL_Texture->setVisible(false);
    GameBoard *gb=GameBoard::GetGameBoardInstance();
    gb->ManShotedSnowManEndInstance();
    gb=NULL;
}

#pragma mark - ME SHOOT SNOW BEGIN END
#pragma mark -SNOW MAN SHOT BEGIN
void ballSnowAnimation::beginSnowShoot()
{
    BALL_Texture->setVisible(true);
    BALL_Texture->setPosition(ccp(300+20, 650-160));
   
}

void ballSnowAnimation::hiddenBall()
{
   // CCLog("hidden ball");
   BALL_Texture->setVisible(false);
    
    GameBoard *gb=GameBoard::GetGameBoardInstance();
    gb->SnowManShotedEndInstance();
    gb=NULL;
}
#pragma mark -SNOW MAN SHOT BEGIN END

