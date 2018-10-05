//
//  BarTimeGame.cpp
//  Yougashi
//
//  Created by dattd on 5/16/13.
//
//

#include "BarTimeGame.h"
USING_NS_CC;

#define MAX_TIME 120

BarTimeGameLayer::~BarTimeGameLayer(){
    CC_SAFE_RELEASE(_progressTime);
    CC_SAFE_RELEASE(_lblTime);
}
bool BarTimeGameLayer::init(){
    if(!CCLayer::init()){
        return false;
    }
//    this->timeGame  = MAX_TIME ;//3:30
//    this->_lblTime =CCLabelTTF::create("2:00", "Arial", 40.0f);// 210s
//    this->_lblTime->setPosition(ccp(0, this->getContentSize().height/2+3));
//    this->_lblTime->setContentSize(CCSizeMake(60, this->getContentSize().height/2));
//    
//    this->_lblTime->setColor(ccRED);
//    this->addChild(this->_lblTime,1);
    
//    CCSprite *bgProgressBar=CCSprite::create("background_barTime.png");
//    bgProgressBar->setScale(0.6);
//    sizeBg.width=bgProgressBar->getContentSize().width * 0.581;
//    sizeBg.height=bgProgressBar->getContentSize().height *0.359;
//    bgProgressBar->setPosition(ccp(328, this->getContentSize().height/2-this->getContentSize().width * 0.34));
//   
//    this->addChild(bgProgressBar,1);
    
    //this->_progressTime=CCLayerColor::create(ccc4(255, 0, 0, 255), 40, 173);
    
    //this->_progressTime->setPosition(ccp(2, 2));
    //this->_progressTime->setContentSize(CCSize(36, 5));
    //this->_progressTime->retain();
    //this->addChild(this->_progressTime,1);
    
    this->_progressTime1=CCSprite::create("power/red_pixel.png");
    this->_progressTime1->setAnchorPoint(ccp(0, 0));
    this->_progressTime1->setPosition(ccp(2, 2));
    this->_progressTime1->setScaleY(1);
    this->_progressTime1->retain();
    this->addChild(this->_progressTime1,1);

    return true;
}
void BarTimeGameLayer::executeUpdateProgressTime(int value){
    
    
    this->timeGame=this->timeGame - value;

    if(this->timeGame ==90){
        this->animationTimeRemaining();
    }

    if(this->timeGame == 0){
        sizeBg.width=0;
        this->_lblTime->setString("0:00");
        this->_lblTime->setContentSize(CCSizeMake(60, this->getContentSize().height/2));
        this->_progressTime->setContentSize(sizeBg);

        this->stopAnimationTimeRemaining();
        return;
    }

    sizeBg.width-=sizeBg.width/this->timeGame;

    int min= this->timeGame / 60;
    int second= this->timeGame - min *60;
    char str[10]={0};
    sprintf(str,"%d:%02d", min,second);
    this->_lblTime->setString(str);
    this->_lblTime->setContentSize(CCSizeMake(60, this->getContentSize().height/2));
    this->_progressTime1->setContentSize(sizeBg);
}
void BarTimeGameLayer::animationTimeRemaining(){
    CCRepeatForever *animation=CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.5f),CCDelayTime::create(0.2f),CCFadeOut::create(0.5f),NULL));
    animation->setTag(100);
    this->_progressTime1->runAction(animation);
    this->_progressTime1->setColor(ccRED);
    
    CCRepeatForever *animation1=CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.5f),CCDelayTime::create(0.2f),CCFadeOut::create(0.5f),NULL));
    animation1->setTag(101);
    this->_lblTime->runAction(animation1);
    this->_lblTime->setColor(ccRED);
}
void BarTimeGameLayer::changeProgressTime(int value){
//    CCSize size=this->_progressTime1->getContentSize();
//    size.height+=value;
    //this->_progressTime1->setContentSize(size);
    int scale=this->_progressTime1->getScaleY();
    this->_progressTime1->setScaleY(scale + value);
}
void BarTimeGameLayer::stopAnimationTimeRemaining(){
    this->_progressTime1->stopActionByTag(100);
    delete this->_progressTime1->getActionByTag(100);
    
    this->_lblTime->stopActionByTag(101);
    delete this->_lblTime->getActionByTag(101);
    this->_lblTime->setColor(ccRED);
    this->_lblTime->runAction(CCFadeIn::create(0.1f));
    
}
