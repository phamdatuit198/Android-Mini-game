//
//  BackgroundLayer.h
//  homerun
//
//  Created by admin on 5/13/13.
//
//

#ifndef __homerun__BackgroundLayer__
#define __homerun__BackgroundLayer__

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(BackgroundLayer);
};

#endif /* defined(__homerun__BackgroundLayer__) */
