//
//  KeypadButtonLayer.h
//  homerun
//
//  Created by admin on 5/14/13.
//
//

#ifndef __homerun__KeypadButtonLayer__
#define __homerun__KeypadButtonLayer__

#include "cocos2d.h"
#include "CCScale9Sprite.h"
#include "cocos-ext.h"
#include "CCControlButton.h"

#define MAX_BUTTON_COLOR    3

class KeypadButtonSprite : public cocos2d::CCSprite
{
public:
    virtual bool init();
    
    CREATE_FUNC(KeypadButtonSprite);
    
    void setTag(int tag);
    int getTag();
    
    void *delegate;
    
    void setMarkerVisible(bool visible);
    void setStarSpriteImage(const char *fileName);
private:
    static int keypadColor;
    int _tag;
    
    cocos2d::extension::CCScale9Sprite *_pButtonNormal;
    cocos2d::extension::CCScale9Sprite *_pButtonHighlighted[MAX_BUTTON_COLOR];
    
    cocos2d::extension::CCControlButton *_pButton;
    void clickedButton(cocos2d::extension::CCControlButton *sender);
    void touchedDownButton(cocos2d::extension::CCControlButton *sender);
    void touchedDragOutside(cocos2d::extension::CCControlButton *sender);
    cocos2d::CCSprite *marker;
    cocos2d::CCSprite *starSprite;
    
    ~KeypadButtonSprite();
};

#endif /* defined(__homerun__KeypadButtonLayer__) */
