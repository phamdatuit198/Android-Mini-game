//
//  kmResultSprite.h
//  homerun
//
//  Created by admin on 5/20/13.
//
//

#ifndef __homerun__kmResultSprite__
#define __homerun__kmResultSprite__

#include "cocos2d.h"

class kmResultSprite : public cocos2d::CCSprite
{
public:
    virtual bool init();
    
    CREATE_FUNC(kmResultSprite);
    
    void setValue(int km, bool isHR);
private:
    CCSprite *hr_100, *hr_10, *hr_1;
};

#endif /* defined(__homerun__kmResultSprite__) */
