//
//  CharacterAnimation.h
//  Snow_6_cocos2dx
//
//  Created by antl on 4/17/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Snow_6_cocos2dx_CharacterAnimation_h
#import "cocos2d.h"

#define Snow_6_cocos2dx_CharacterAnimation_h
using namespace cocos2d;

class CharacterAnimationObserver {
public:
    virtual void Notify() = 0;
};

class CharacterAnimation : public cocos2d::CCSprite
{
   

    static CharacterAnimation* instance;
    std::set<CharacterAnimationObserver*> observers;
   
    
    
    public:
    
    static CharacterAnimation* GetInstance();
    void AddObserver(CharacterAnimationObserver& o);
    void RemoveObserver(CharacterAnimationObserver& o);
    void NotifyObservers();
    void Trigger();
    
    
    
    bool beingAction;
    CharacterAnimation();
    ~CharacterAnimation();
    int iTag;
    int iFrame;
    char *plist;
    char *filePNG;
    char* nameB;
    char* nameCharactor;
    CCPoint tempDimention;
    CCPoint tempAnchorpoint;
    float cScale;
    CCSprite *charater;
    void finishAction();
    void resetCharacter();
    const char *nameAnimation;
    virtual bool init();
    virtual CCSpriteBatchNode* iCreateAnimation(const char * iName, cocos2d::CCPoint dimensions,cocos2d::CCPoint iAnchorPoint,float scale);
    virtual void setup(int iTag ,int Frame);
    virtual void ActionOneTime();
    CCArray *upArmArray;
    CCArray *downArmArray;
    CCArray *resetArray;
    CCSpriteBatchNode *spreetsheet;
    CREATE_FUNC(CharacterAnimation);
    
    // allow shoot
    void AllowShoot();
};


#endif
