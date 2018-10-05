//
//  CharaterAnimation.cpp
//  Snow_6_cocos2dx
//
//  Created by antl on 4/17/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CharacterAnimation.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Scenes/GameBoard.h"
#pragma mark - OBSERVERS DESIGN PATTERN -BEGIN
CharacterAnimation* CharacterAnimation::instance = NULL;


CharacterAnimation* CharacterAnimation::GetInstance()
{
    if ( instance == NULL ) {
        instance = new CharacterAnimation();
    }
    
    return instance;
}
void CharacterAnimation::AddObserver(CharacterAnimationObserver& o)
{
    observers.insert(&o);
}

void CharacterAnimation::RemoveObserver(CharacterAnimationObserver& o)
{
    observers.erase(&o);
}

void CharacterAnimation::NotifyObservers()
{
    std::set<CharacterAnimationObserver*>::iterator itr;
    for ( itr = observers.begin();
         itr != observers.end(); itr++ )
        (*itr)->Notify();
}
void CharacterAnimation::Trigger()
{
    NotifyObservers();
}
#pragma mark - OBSERVERS DESIGN PATTERN -END
bool CharacterAnimation::init()
{
       
    return true;

}
void CharacterAnimation::setup(int iTag ,int Frame)
{
    iTag=iTag;
    iFrame=Frame;
}
///CCString *plist=CCString::createWithFormat("%@.plist", iName);
CCSpriteBatchNode* CharacterAnimation::iCreateAnimation(const char * iName, cocos2d::CCPoint dimensions,cocos2d::CCPoint iAnchorPoint,float scale)
{
    cScale=scale;
    tempDimention=dimensions;
    tempAnchorpoint=iAnchorPoint;
    sprintf(nameCharactor, "%s", iName);/// saving name
    sprintf(plist, "%s.plist", iName);      
    sprintf(filePNG, "%s.png", iName);
    CCLog("plist :%s",plist);
     CCLog("filePNG :%s",filePNG);
     CCLog("iName : %s",iName);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist);
    spreetsheet = CCSpriteBatchNode::create(filePNG);
    sprintf(nameB,"%s3.png",nameCharactor);
    charater = CCSprite::createWithSpriteFrameName(nameB);
    charater->setAnchorPoint(tempAnchorpoint);
    charater->setPosition(tempDimention);
    charater->setScale(cScale);
    spreetsheet->addChild(charater);
   
    for(int i = 1; i <= 3; i++)
    {
        char name[32] = {0};
        sprintf(name, "%s%d.png",iName,i);
        
        
        
        if(i>=2)
        {
            downArmArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
        }

       if(i==1)
       {
           upArmArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
        }
        else if(i==3)
        {
            resetArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
        }
    }
   
    return spreetsheet;
}
void CharacterAnimation::ActionOneTime()
{
    beingAction=true;
    CCArray* actions = CCArray::create();
    CCAnimation *upAnim = CCAnimation::createWithSpriteFrames(upArmArray, 0.2f);   
    actions->addObject(CCAnimate::create(upAnim));
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(CharacterAnimation::AllowShoot)));
    //CCAction *walkAction =CCAnimate::create(walkAnim);//CCRepeatForever::create(CCAnimate::create(walkAnim));//CCDelayTime *delayAction = CCDelayTime::create(1.0f);    
    actions->addObject(CCDelayTime::create(1.0f));
    CCAnimation *downAnim = CCAnimation::createWithSpriteFrames(downArmArray, 0.2f);
    actions->addObject(CCAnimate::create(downAnim));    
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(CharacterAnimation::finishAction)));
    
    CCFiniteTimeAction* actionSchedule = CCSequence::create(actions);
    charater->runAction(actionSchedule);
    
    
    delete actions;
       
}
void CharacterAnimation::AllowShoot()
{
    GameBoard *gb=GameBoard::GetGameBoardInstance();
    gb->AllowSnowShooting();
    gb=NULL;
}
void CharacterAnimation::resetCharacter()
{
    CCAnimation *iResetArray = CCAnimation::createWithSpriteFrames(resetArray, 0.1f);
    CCAction *resetAction =CCAnimate::create(iResetArray);
    charater->runAction(resetAction);
    
    CCLog("reset");
}
void CharacterAnimation::finishAction()
{
    CCLog("Character finish action");
    //beingAction=false;
    //GameBoard->sw
    GameBoard *gb=GameBoard::GetGameBoardInstance();
    gb->SnowManBeginShootInstance();
    gb=NULL;
    
}
CharacterAnimation::CharacterAnimation()
{
    beingAction=false;
    plist =new char;
    filePNG =new char;
    nameB=new char;
    nameCharactor=new char;
    upArmArray = new CCArray();
    resetArray= new CCArray();
    downArmArray=new CCArray();
}
CharacterAnimation::~CharacterAnimation()
{
    delete resetArray;
    beingAction=false;
    delete upArmArray;
    delete plist;
    delete filePNG;
    delete nameB;
    delete nameCharactor;
    delete downArmArray;
}


/*

CharacterAnimation::CharacterAnimation()
:m_pfnSelectorDelegate(0)
,m_pTarget(0)
,m_isPlistLoaded(false)
//,m_ElaspeTime(0)
,m_IncrementValue(0)
,m_isAnimationRunning(false)
{
    
}

CharacterAnimation::~CharacterAnimation()
{
    if(m_isPlistLoaded)
        CC_SAFE_DELETE(m_AnimationFrames);
}

void CharacterAnimation::addFrames(const char *pList)
{
    m_isPlistLoaded = true;
    m_AnimationFrames = new CCArray;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pList);
    const char *pszPath = CCFileUtils::fullPathForFilename(pList);
	CCDictionary<std::string, CCObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);
    CCDictionary<std::string, CCObject*> *framesDict = (CCDictionary<std::string, CCObject*>*)dict->objectForKey(std::string("frames"));
    
    framesDict->begin();
	std::string key = "";
	while((CCDictionary<std::string, CCObject*>*)framesDict->next(&key))
	{
        m_AnimationFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key.c_str()));
    }
    setDisplayFrame(m_AnimationFrames->objectAtIndex(0));
}

void CharacterAnimation::addFrames(CCArray* frames)
{
    m_AnimationFrames = frames;
    setDisplayFrame(m_AnimationFrames->objectAtIndex(0);
}

void CharacterAnimation::addFrames(CCArray *frames, int displayTextureIndex)
{
    m_AnimationFrames = frames;
    setDisplayFrame(m_AnimationFrames->getObjectAtIndex(displayTextureIndex));
}

void CharacterAnimation::increaseCurrentIndex()
{
    if(m_AnimationMode && (m_EndingIndex - m_CurrentIndex) != 0)
        m_IncrementValue += (m_EndingIndex - m_CurrentIndex) / abs(m_EndingIndex - m_CurrentIndex);
    else if((m_StartingIndex - m_CurrentIndex) != 0)
        m_IncrementValue += (m_StartingIndex - m_CurrentIndex) / abs(m_StartingIndex - m_CurrentIndex);
}

void CharacterAnimation::update(CCTime dt)
{
    m_ElaspeTime += dt;
    while (m_ElaspeTime >= m_FrameRate) 
    {
        m_ElaspeTime -= m_FrameRate;
        
        m_CurrentIndex += m_IncrementValue;
        setDisplayFrame(m_AnimationFrames->objectAtIndex(m_CurrentIndex);
        
        //Forward Animation....
        if (m_CurrentIndex == m_EndingIndex) 
        {
            if(m_NeedToRunReverseAnimation)
            {
                m_AnimationMode = false;
                increaseCurrentIndex();
                return;
            }
            
            m_RunningLoop++;
            if(m_RunningLoop == m_NumberOfLoop)
            {
                stopAnimaiton();
                //Raising Callback.
                if(m_pTarget != 0 && m_pfnSelectorDelegate != 0)
                    (m_pTarget->*m_pfnSelectorDelegate)();
                
                //Remove Object by Itself.
                if(m_NeedToDeleteItself)
                    removeObjectItself();
                return;
            }
            else
            {
                m_CurrentIndex = m_StartingIndex;
            }
        }
        
        //Reverse Animation...
        else if(m_CurrentIndex == m_StartingIndex)
        {
            m_RunningLoop++;
            if(m_RunningLoop == m_NumberOfLoop)
            {
                stopAnimaiton();
                //Raising Callback.
                if(m_pTarget != 0 && m_pfnSelectorDelegate != 0)
                    (m_pTarget->*m_pfnSelectorDelegate)();
                
                //Remove Object by Itself.
                if(m_NeedToDeleteItself)
                    removeObjectItself();
                return;
            }
            else
            {
                m_AnimationMode = true;
                increaseCurrentIndex();
            }
        }
    }
}

void CharacterAnimation::startAnimation(int startInd, int endInd, int number_Loop, SEL_CallFunc pfnSelectorDelegate, CCObject *pTarget, int NumberOfFramesPerSecond, bool NeedToRunReverseAnimation, bool NeedToDeleteItself)
{
    if(m_isAnimationRunning)
    {
        stopAnimaiton();
        
        //Reset pointer.
        m_pfnSelectorDelegate = 0;
        m_pTarget = 0;
        m_ElaspeTime = 0.0f;
    }
    
    //Assign values.
    m_isAnimationRunning = true;
    
    m_StartingIndex = startInd - 1;
    m_EndingIndex = endInd - 1;
    
    m_NumberOfLoop = number_Loop;
    
    m_pfnSelectorDelegate = pfnSelectorDelegate;
    m_pTarget = pTarget;
    if(NumberOfFramesPerSecond != -1)
        m_FrameRate = calculateFrameRate(NumberOfFramesPerSecond);
    
    //Initilize values....
    m_NeedToRunReverseAnimation = NeedToRunReverseAnimation;
    m_AnimationMode = true;
    m_CurrentIndex = m_StartingIndex;
    m_RunningLoop = 0;
    m_IncrementValue = 0;
    m_NeedToDeleteItself = NeedToDeleteItself;
    increaseCurrentIndex();
    this->scheduleUpdateWithPriority(-1);
    resumeAnimation();
}

void CharacterAnimation::stopAnimaiton()
{
    m_isAnimationRunning = false;
    this->unscheduleUpdate();
}

void CharacterAnimation::removeObjectItself()
{
    this->removeFromParentAndCleanup(true);
    delete (this);
}*/
