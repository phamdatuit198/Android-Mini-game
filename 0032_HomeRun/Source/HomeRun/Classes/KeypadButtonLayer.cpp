//
//  KeypadButtonLayer.cpp
//  homerun
//
//  Created by admin on 5/14/13.
//
//

#include "KeypadButtonLayer.h"
#include "GameConstants.h"

using namespace cocos2d;
using namespace extension;

int KeypadButtonSprite::keypadColor = 0;

bool KeypadButtonSprite::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    
    _pButtonNormal = new CCScale9Sprite();
    _pButtonNormal->initWithFile("keypad_button_bg.png");
    
    for (int i = 0; i < MAX_BUTTON_COLOR; i++) {
        _pButtonHighlighted[i] = new CCScale9Sprite();
        CCString *fileName = CCString::createWithFormat("keypad_%d.png", i);
        _pButtonHighlighted[i]->initWithFile(fileName->getCString());
    }
    
    _pButton = new CCControlButton();
    _pButton->initWithBackgroundSprite(_pButtonNormal);
    _pButton->setAdjustBackgroundImage(false);
    _pButton->setPosition(ccp(0, 0));
    _pButton->addTargetWithActionForControlEvents(this, cccontrol_selector(KeypadButtonSprite::touchedDownButton), CCControlEventTouchDown);
    _pButton->addTargetWithActionForControlEvents(this, cccontrol_selector(KeypadButtonSprite::clickedButton), CCControlEventTouchUpInside);
    _pButton->addTargetWithActionForControlEvents(this, cccontrol_selector(KeypadButtonSprite::touchedDragOutside), CCControlEventTouchDragOutside);
    this->addChild(_pButton);
    
    marker = CCSprite::create("aim_aim_03.png");
    marker->setPosition(ccp(0.f, 0.f));
    marker->setVisible(false);
    this->addChild(marker, 1);
    
    return true;
}

void KeypadButtonSprite::touchedDownButton(CCControlButton *sender)
{
    _pButton->setBackgroundSpriteForState(_pButtonHighlighted[keypadColor], CCControlStateHighlighted);
    starSprite->setVisible(true);
}

void KeypadButtonSprite::touchedDragOutside(cocos2d::extension::CCControlButton *sender)
{
    starSprite->setVisible(false);
}

void KeypadButtonSprite::clickedButton(CCControlButton *sender)
{
    keypadColor++;
    keypadColor = keypadColor % MAX_BUTTON_COLOR;
    marker->setVisible(false);
    starSprite->setVisible(false);
    if (this->isVisible()) {        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(KEYPAD_TOUCHED_NOTIFICATION, this);
    }
}

KeypadButtonSprite::~KeypadButtonSprite()
{
    delete _pButtonNormal;
    delete _pButton;
    for (int i = 0; i < MAX_BUTTON_COLOR; i++) {
        delete _pButtonHighlighted[i];
    }
}

void KeypadButtonSprite::setTag(int tag)
{
    _tag = tag;
}

int KeypadButtonSprite::getTag()
{
    return _tag;
}

void KeypadButtonSprite::setMarkerVisible(bool visible)
{
    marker->setVisible(visible);
    if (!visible) {
        starSprite->setVisible(visible);
    }
}

void KeypadButtonSprite::setStarSpriteImage(const char *fileName)
{
    starSprite = CCSprite::create(fileName);
    starSprite->setPosition(ccp(0.f, 0.f));
    starSprite->setVisible(false);
    this->addChild(starSprite);
}