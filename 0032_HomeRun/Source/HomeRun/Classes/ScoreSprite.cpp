//
//  ScoreSprite.cpp
//  homerun
//
//  Created by admin on 5/21/13.
//
//

#include "ScoreSprite.h"

USING_NS_CC;

bool ScoreSprite::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    
    sc_10 = CCSprite::create("f_n0.png");
    sc_10->setPosition(ccp(-18.5f, 0.f));
    this->addChild(sc_10);
    
    sc_1 = CCSprite::create("f_n0.png");
    sc_1->setPosition(ccp(18.5f, 0.f));
    this->addChild(sc_1);
    
    sc_ex = CCSprite::create("f_ex.png");
    sc_ex->setPosition(ccp(0.f, 0.f));
    this->addChild(sc_ex);
    sc_ex->setVisible(false);
    
    return true;
}

void ScoreSprite::setScore(int score)
{
    int score_10 = floor(score/10);
    if (score_10 > 9) {
        score_10 = score_10 % 10;
    }
    int score_1 = score % 10;
    //    hr_10->release();
    CCString *fileName = CCString::createWithFormat("f_n%d.png", score_10);
    this->removeChild(sc_10, true);
    sc_10 = CCSprite::create(fileName->getCString());
    if (sc_10) {
        sc_10->setPosition(ccp(-18.5f, 0.f));
        this->addChild(sc_10);
        sc_10->setVisible(score_10 > 0);
    }
    fileName = CCString::createWithFormat("f_n%d.png", score_1);
    this->removeChild(sc_1, true);
    sc_1 = CCSprite::create(fileName->getCString());
    if (sc_1) {
        sc_1->setPosition(ccp(18.5f, 0.f));
        this->addChild(sc_1);
        sc_1->setVisible(true);
    }
    sc_ex->setVisible(false);
}

void ScoreSprite::setEx()
{
    sc_ex->setVisible(true);
    if (sc_10) {        
        sc_10->setVisible(false);
    }
    if (sc_1) {
        sc_1->setVisible(false);        
    }
}