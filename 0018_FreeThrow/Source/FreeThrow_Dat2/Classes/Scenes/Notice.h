//
//  Notice.h
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/22/13.
//
//

#ifndef __Snow_6_cocos2dx__Notice__
#define __Snow_6_cocos2dx__Notice__

#include <iostream>
#include "cocos2d.h"

class Notice:public cocos2d::CCSprite
{
public:
    Notice();
    virtual ~Notice();
    static Notice* create(const char *pSpriteFrame);
};

#endif /* defined(__Snow_6_cocos2dx__Notice__) */
