//
//  KeypadLayer.cpp
//  homerun
//
//  Created by admin on 5/14/13.
//
//

#include "KeypadLayer.h"

USING_NS_CC;
using namespace extension;

bool KeypadLayer::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    
    CCSprite *keypadSprite = CCSprite::create("button_button_03.png");
    this->addChild(keypadSprite);
    //DatPV
    int CCPointX,CCPointY;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if(size.width == 720){
    	CCPointX = -130;
    	CCPointY = 126;
    }else{
    	CCPointX = -90;
    	CCPointY = 90;
    }
    
    CCPoint pointPos = CCPoint(CCPointX, CCPointY);
    
    for (int i = 0; i < 9; i++) {
        _pKeypadButton[i] = KeypadButtonSprite::create();
        _pKeypadButton[i]->setPosition(pointPos);
        _pKeypadButton[i]->setTag(i);
        _pKeypadButton[i]->delegate = delegate;
        _pKeypadButton[i]->setStarSpriteImage(CCString::createWithFormat("star_0%d.png", i)->getCString());
        this->addChild(_pKeypadButton[i]);
        // Set position for next button
        int f = (i + 1) % 3;
        if(size.width == 720){
        	if (f == 0) {
        	              pointPos.y -= 126;
        	              pointPos.x = -130;
        	        } else {
        	              pointPos.x += 130;
        	        }
        }else{
        	if (f == 0) {
        	              pointPos.y -= 90;
        	              pointPos.x = -90;
        	        } else {
        	              pointPos.x += 90;
        	        }
        }

    }
    
    return true;
}

void KeypadLayer::clickedKeypad(CCControlButton *sender) {
//    printf("clicked\n");
}

void KeypadLayer::setMarkerAt(int index)
{
    this->resetMarker();
    _pKeypadButton[index]->setMarkerVisible(true);
}

void KeypadLayer::resetMarker()
{
    for (int i = 0; i < 9; i++) {
        _pKeypadButton[i]->setMarkerVisible(false);
    }
}

/*
 *  Let keypad cannot touch in case user gets strike
 */
void KeypadLayer::setKeypadTouchEnabled(bool enable)
{
    for (int i = 0; i < 9; i++) {
        _pKeypadButton[i]->setVisible(enable);
    }
}

void KeypadLayer::setVisible(bool visible)
{
    CCSprite::setVisible(visible);
    for (int i = 0; i < 9; i++) {
        _pKeypadButton[i]->setVisible(visible);
    }
}
