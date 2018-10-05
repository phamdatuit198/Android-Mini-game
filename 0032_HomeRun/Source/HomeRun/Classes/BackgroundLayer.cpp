//
//  BackgroundLayer.cpp
//  homerun
//
//  Created by admin on 5/13/13.
//
//

#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

// on "init" you need to initialize your instance
bool BackgroundLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }
    
    //////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    // you may modify it.
    CCSprite *backgroundSprite = CCSprite::create("bg.png");
    this->addChild(backgroundSprite);
    
    return true;
}