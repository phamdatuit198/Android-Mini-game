//
//  ScoreSprite.h
//  homerun
//
//  Created by admin on 5/21/13.
//
//

#ifndef __homerun__ScoreSprite__
#define __homerun__ScoreSprite__

#include "cocos2d.h"

class ScoreSprite : public cocos2d::CCSprite
{
public:
    virtual bool init();
    
    CREATE_FUNC(ScoreSprite);
    
    void setScore(int score);
    void setEx();
private:
    cocos2d::CCSprite *sc_10;
    cocos2d::CCSprite *sc_1;
    cocos2d::CCSprite *sc_ex;
};

#endif /* defined(__homerun__ScoreSprite__) */
