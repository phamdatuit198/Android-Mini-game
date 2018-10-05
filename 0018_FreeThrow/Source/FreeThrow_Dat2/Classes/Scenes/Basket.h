//
//  Basket.h
//  r_bomb
//
//  Created by Soa Nguyen on 5/28/13.
//
//

#ifndef __r_bomb__Basket__
#define __r_bomb__Basket__

#include <iostream>
#include "cocos2d.h"

class Basket:public cocos2d::CCSprite
{
private:
//    cocos2d::CCArray *arrAction;
public:
    Basket();
    virtual ~Basket();
    static Basket* create(const char *pSpriteFrame);
    
    void goalAnimation(cocos2d::CCArray *arrAction);
};

#endif /* defined(__r_bomb__Basket__) */
