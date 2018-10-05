//
//  Notice.cpp
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/22/13.
//
//

#include "Notice.h"

Notice::Notice()
{
    
}

Notice:: ~Notice()
{
    
}

Notice* Notice::create(const char *pSpriteFrame)
{
    
    Notice *pSprite = new Notice();
    if (pSprite && pSprite->initWithFile(pSpriteFrame)){
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}