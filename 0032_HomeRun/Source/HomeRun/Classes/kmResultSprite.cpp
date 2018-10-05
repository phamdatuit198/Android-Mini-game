//
//  kmResultSprite.cpp
//  homerun
//
//  Created by admin on 5/20/13.
//
//

#include "kmResultSprite.h"

USING_NS_CC;

bool kmResultSprite::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    
    hr_100 = CCSprite::create("f_n1.png");
    hr_100->setPosition(ccp(-66.5f, 0.f));
    this->addChild(hr_100);
    
    hr_10 = CCSprite::create("f_n0.png");
    hr_10->setPosition(ccp(-29.5f, 0));
    this->addChild(hr_10);
    
    hr_1 = CCSprite::create("f_n0.png");
    hr_1->setPosition(ccp(7.5, 0));
    this->addChild(hr_1);
    
    CCSprite *mSprite = CCSprite::create("f_m.png");
    mSprite->setPosition(ccp(55.5, -5.f));
    this->addChild(mSprite);
    
    return true;
}

void kmResultSprite::setValue(int km, bool isHR)
{
    int km_10 = floor(km/10);
    int km_1 = km % 10;
    CCString *fileName = CCString::createWithFormat("f_n%d.png", km_10);
    this->removeChild(hr_10, true);
    hr_10 = CCSprite::create(fileName->getCString());
    if (hr_10) {        
        hr_10->setPosition(ccp(-29.5f, 0.f));
        this->addChild(hr_10);
        hr_10->setVisible(isHR || km_10 > 0);
    }
    fileName = CCString::createWithFormat("f_n%d.png", km_1);
    this->removeChild(hr_1, true);
    hr_1 = CCSprite::create(fileName->getCString());
    if (hr_1) {
        hr_1->setPosition(ccp(7.5f, 0.f));
        this->addChild(hr_1);
    }
    hr_100->setVisible(isHR);
}