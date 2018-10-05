//
//  CCMyScene.cpp
//  Snow_6_cocos2dx
//
//  Created by antl on 4/16/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
#include "CCMyScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

using namespace cocos2d;
using namespace CocosDenshion;
cocos2d::CCSprite* CCMyScene::drawImageWithLayer(const char* image ,cocos2d::CCPoint dimensions ,cocos2d::CCPoint iAnchorPoint)
{
    CCSprite* pSprite = CCSprite::create(image);
    pSprite->setPosition(ccp(dimensions.x, dimensions.y) );
    if(iAnchorPoint.x!=-1&&iAnchorPoint.y!=-1)
    {
        pSprite->setAnchorPoint(iAnchorPoint);
    }

   
    this->addChild(pSprite, 0);
    return pSprite;

}

cocos2d::CCLabelTTF* CCMyScene::drawLable(const char* letter ,const char* fontName ,cocos2d::CCPoint dimensions ,cocos2d::CCPoint iAnchorPoint, float size)
{
    CCLabelTTF* pLabel = CCLabelTTF::create(letter, fontName, size);
    pLabel->setPosition( ccp(dimensions.x, dimensions.y) );
     pLabel->setAnchorPoint(iAnchorPoint);
    this->addChild(pLabel, 1);
    return pLabel;
}