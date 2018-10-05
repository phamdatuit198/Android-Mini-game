//
//  Basket.cpp
//  r_bomb
//
//  Created by Soa Nguyen on 5/28/13.
//
//

#include "Basket.h"
using namespace cocos2d;
using namespace std;

Basket::Basket()
{
    
}

Basket:: ~Basket()
{
    
}

Basket* Basket::create(const char *pSpriteFrame)
{
    
    Basket *pSprite = new Basket();
    if (pSprite && pSprite->initWithFile(pSpriteFrame)){
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Basket::goalAnimation(cocos2d::CCArray *arrAction)
{
    // change image for basket NORMAL_IMAGE - GOAL_IMAGE - NORMAL_IMAGE
    cocos2d::CCAnimation *ballAnim = cocos2d::CCAnimation::createWithSpriteFrames(arrAction, 0.05f);
    CCArray* rotateAction = CCArray::create();
    rotateAction->addObject(CCAnimate::create(ballAnim));
    CCSequence *sequenceAction = CCSequence::create(rotateAction);
    CCRepeat *repeatAction = CCRepeat::create(sequenceAction, 1);
    this->runAction(repeatAction);
}