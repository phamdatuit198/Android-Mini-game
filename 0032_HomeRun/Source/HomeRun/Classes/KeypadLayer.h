//
//  KeypadLayer.h
//  homerun
//
//  Created by admin on 5/14/13.
//
//

#ifndef __homerun__KeypadLayer__
#define __homerun__KeypadLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCControlButton.h"
#include "CCScale9Sprite.h"
#include "KeypadButtonLayer.h"

class KeypadLayer : public cocos2d::CCSprite
{
public:
    virtual bool init();
    
    CREATE_FUNC(KeypadLayer);
    
    void *delegate;
    
    void setMarkerAt(int index);
    void resetMarker();
    void setKeypadTouchEnabled(bool enable);
    
    virtual void setVisible(bool visible);
private:
    KeypadButtonSprite *_pKeypadButton[9];
    
    void clickedKeypad(cocos2d::extension::CCControlButton *sender);
};

#endif /* defined(__homerun__KeypadLayer__) */
