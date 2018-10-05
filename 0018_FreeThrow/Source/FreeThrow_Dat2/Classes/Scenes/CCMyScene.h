//
//  CCMyScene.h
//  Snow_6_cocos2dx
//
//  Created by antl on 4/16/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Snow_6_cocos2dx_Header_h
#define Snow_6_cocos2dx_Header_h
#include "cocos2d.h"
#include "../Support/Define.h"
class CCMyScene : public cocos2d::CCLayer
{
    public :
    virtual cocos2d::CCSprite* drawImageWithLayer(const char* image ,cocos2d::CCPoint dimensions ,cocos2d::CCPoint iAnchorPoint );
    virtual cocos2d::CCLabelTTF* drawLable(const char* letter ,const char* fontName ,cocos2d::CCPoint dimensions ,cocos2d::CCPoint iAnchorPoint, float size);
};

#endif
