//
//  GameBoard.cpp
//  Snow_6_cocos2dx
//
//  Created by antl on 4/16/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
#include <iostream>
#include "GameBoard.h"
#include "SimpleAudioEngine.h"
#include <vector>
//#include "GameOver.h"
#include "../NDKHelper/NDKHelper.h"
#define TAG_SNOW 1550
#define TAG_BALL 1850
#define TAG_SHOOT 2950
#define TIME_UPDATE 1.0
#define NUMBER_SNOW 9
#define MAX_LIFE 20//10//20
#define SCORE_TAG 3405
using namespace cocos2d;
using namespace std;
/// observer http://login2win.blogspot.com/2008/05/c-observer-patterm.html
//using namespace CocosDenshion;
GameBoard* GameBoard::GameBoardInstance = NULL;
GameBoard* GameBoard::GetGameBoardInstance()
{
    
    return GameBoardInstance;
}


cocos2d::CCScene* GameBoard::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    if ( GameBoardInstance == NULL ) {
        GameBoardInstance = GameBoard::create();
    }
    scene->addChild(GameBoardInstance,1001);
    return scene;
    
}
#pragma mark - delete Finish
#pragma mark - ShowText Delegate

GameBoard::GameBoard()
{
    CCLog("create gameboard");
    enableShooting=true;
    EndGame=false;    
    CurrentTag=-1;
    _ArrayCharacter = new CCArray;
    ballSnow= new ballSnowAnimation();
    // set Score
    iScore=0;
    iNumberLose=1;
   
}
GameBoard::~GameBoard()
{
    CCLog("DELETE GAME BOARD");
    
    CurrentTag=-1;
    if (_ArrayCharacter)
    {
        _ArrayCharacter->release();
        _ArrayCharacter = NULL;
    }
    delete ballSnow;
    
    
    if(GameBoardInstance!=NULL)
    {
        GameBoardInstance=NULL;
    }
}
#pragma mark - INIT
void GameBoard::ShowText()
{
    CCArray* actions = CCArray::create();    
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(GameBoard::VisibleScore)));
    actions->addObject(CCDelayTime::create(1.8f));//0.9f
    actions->addObject(CCCallFuncN::create( this,callfuncN_selector(GameBoard::disibleScore)));    
    CCFiniteTimeAction* actionSchedule = CCSequence::create(actions);
    ScoreNumber->runAction(actionSchedule);    
    delete actions;
}
#pragma mark - SNOW SHOOT INSTANCE
 void GameBoard::SnowManBeginShootInstance()
{
    //CCLog("test instance");
     enableShooting=false;
     ballSnow->BeShot();  /// enable shooting
    
    
}
void GameBoard::SnowManShotedEndInstance()
{
    
    CCLog("Snow shot end");
    CharacterAnimation * currentCharacter=GameBoard::getCharactorById(CurrentTag);
    currentCharacter->beingAction=false;
    currentCharacter=NULL;
    /// increase number lose
    this->IncreaseNumber();
    
    //enableShooting=true;/// disable shooting
    enableShooting=false;
}
#pragma mark - MAN SHOOT INSTANCE
void GameBoard::ManShotedSnowManBeginInstance()
{
    CCLog("begin Shoot Snow Man ");
    enableShooting=false;  /// dissable shooting
    ///// disable current action
    CharacterAnimation * currentCharacter=GameBoard::getCharactorById(CurrentTag);
    currentCharacter->beingAction=true;
    currentCharacter=NULL;
}

void GameBoard::ManShotedSnowManEndInstance()
{
    CCLog("end Shoot Snow Man ");
    //enableShooting=true;  /// enable shooting
    ///// enable current action
    CharacterAnimation * currentCharacter=GameBoard::getCharactorById(CurrentTag);
    currentCharacter->beingAction=false;
    currentCharacter=NULL;
}

#pragma mark - delete Finish END



void GameBoard::drawScoreAtIndex(int index,long iScore)
{
    CCPoint P;
    if(index==0)
    {
        P=CCPoint(50+30,730+20);
    }
    else if(index==1)
    {
        P=CCPoint(250+30, 700+30+20);
    }
    else if(index==2)
    {
        P=CCPoint(400+30, 700+30+20);
    }
    else if(index==3)
    {
        P=CCPoint(55+40, 520+30+20);
    }
    else if(index==4)
    {
        P=CCPoint(225+40, 520+30+20);
    }
    else if(index==5)
    {
        P=CCPoint(430+40, 520+30+20);
    }
    else if(index==6)
    {
        P=CCPoint(20+50, 320+30+40);
    }
    else if(index==7)
    {
        P=CCPoint(240+50, 320+30+40);
    }
    else if(index==8)
    {
        P=CCPoint(420+50, 320+30+40);
    }
    
    char number[32] = {0};
    sprintf(number, "+%ld",iScore);
    ScoreNumber->setString(number);
    ScoreNumber->setPosition(ccp(P.x-15,P.y+10));
    textOK->setPosition(ccp(P.x,P.y-40));
    
     
}
void GameBoard::VisibleScore()
{
    ScoreNumber->setVisible(true);
    textOK->setVisible(true);
}
void GameBoard::disibleScore()
{
     ScoreNumber->setVisible(false);
     textOK->setVisible(false);
}

void GameBoard::updateScore(long Score)
{
    iScore=iScore+Score;
    char number[32] = {0};
    sprintf(number, "%ld",iScore);    
    
    lableScore1->setString(number);
}
void GameBoard::IncreaseNumber()
{
    if(iNumberLose<MAX_LIFE)
    {
        iNumberLose=iNumberLose+1;
        char number[32] = {0};
        sprintf(number, "%d/%d",iNumberLose,MAX_LIFE);
        lableScore2->setString(number);
    }else{
        //end game
        /// set Score Game
                
        CCArray* actions = CCArray::create();
        actions->addObject(CCCallFuncN::create( this,callfuncN_selector(GameBoard::repairChangeScene)));        
        actions->addObject(CCDelayTime::create(0.2));
        actions->addObject(CCCallFuncN::create( this,callfuncN_selector(GameBoard::changeScene)));
        CCFiniteTimeAction* actionSchedule = CCSequence::create(actions);
        this->runAction(actionSchedule);
               
        delete actions;
        
    }
    
}

void GameBoard::repairChangeScene()
{
    EndGame=true;
    this->unschedule(schedule_selector(GameBoard::update));
    CharacterAnimation * currentCharacter=GameBoard::getCharactorById(CurrentTag);
    currentCharacter->stopAllActions();
    CCUserDefault::sharedUserDefault()->setIntegerForKey(SCORE, iScore);
}

void GameBoard::changeScene()
{
//    CCScene *pscene = GameOver::scene();
//    CCDirector::sharedDirector()->setDepthTest(true);
//    CCTransitionScene *transition = CCTransitionCrossFade::create(1.0f, pscene);//CCTransitionPageTurn::create(1.0f, pscene, false);
//    CCDirector::sharedDirector()->replaceScene(transition);

}


bool GameBoard::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }    
    

    
    this->drawImageWithLayer("bg_01.png", CCPoint(0 , 0),CCPoint(0 , 0));    
    this->drawImageWithLayer("playingGameBg.png", CCPoint(0 , 120),CCPoint(0 , 0));
    //this->drawImageWithLayer("GameTitle.png", CCPoint(110 , 850),CCPoint(0 , 0));
    
    
    this->drawImageWithLayer("newText_03.png", CCPoint(450 , 70),CCPoint(0 , 0));
    lableScore2= this->drawLable("1/20", "HGRPP1.TTC", CCPoint(520 , 66), CCPoint(0 , 0), 32);
    lableScore2->setColor(ccc3(0,94,188));
    
    
    
    this->drawImageWithLayer("result_test02.png", CCPoint(70 , 70),CCPoint(0 , 0));
    lableScore1= this->drawLable("0", "HGRPP1.TTC", CCPoint(270 , 66), CCPoint(0 , 0), 32);
    this->drawImageWithLayer("Playtext_02.png", CCPoint(340 , 70),CCPoint(0 , 0));
    lableScore1->setColor(ccc3(0,94,188));
    
    
    
    
    
    
    CCPointArray* p= CCPointArray::create(NUMBER_SNOW);
     p->addControlPoint(CCPoint(50, 700+30));
     p->addControlPoint(CCPoint(250, 700+30));
     p->addControlPoint(CCPoint(400, 700+30));
    //3
    
     p->addControlPoint(CCPoint(55, 520+30));
     p->addControlPoint(CCPoint(225, 520+30));
     p->addControlPoint(CCPoint(430, 520+30));
    //7
    
     p->addControlPoint(CCPoint(20, 320+30));
     p->addControlPoint(CCPoint(240, 320+30));
     p->addControlPoint(CCPoint(420, 320+30));
    /// character
    for (int index=0; index<NUMBER_SNOW; index++) {
        CharacterAnimation *charactor = new CharacterAnimation();
        charactor->setTag(index+TAG_SNOW);
        float scale=1.0f;
        if(index<3)
        {
            scale=0.5f;
        }
        else if(index>=3&&index<6)
        {
             scale=0.6f;
        }
        else
        {
             scale=0.75f;
        }
        CCSpriteBatchNode*patchNode= charactor->iCreateAnimation("SnowMan", p->getControlPointAtIndex(index),CCPoint(0 , 0), scale);
        patchNode->setTag(index+TAG_SNOW);
        this->addChild(patchNode);/// add sprite sheet
        _ArrayCharacter->addObject(charactor);
        char number[32] = {0};
        sprintf(number, "%d",index+1);
        CCLabelTTF* numberLetter = CCLabelTTF::create(number, "HGRPP1.TTC", 34);
        numberLetter->setColor(ccBLACK);
        numberLetter->setAnchorPoint(ccp(0,0));
        
        if(index<3)
        {
            numberLetter->setPosition(ccp(p->getControlPointAtIndex(index).x+42 , p->getControlPointAtIndex(index).y+16));
        }
        else if(index>=3&& index<6){
            numberLetter->setPosition(ccp(p->getControlPointAtIndex(index).x+54 , p->getControlPointAtIndex(index).y+20));
        }
        else{
            numberLetter->setPosition(ccp(p->getControlPointAtIndex(index).x+75 , p->getControlPointAtIndex(index).y+40));
        }
        this->addChild(numberLetter, 1);
        
    }
    
    this->schedule( schedule_selector(GameBoard::update), TIME_UPDATE );
    
    
    
    /// menu Number
    CCMenu* pMenu = CCMenu::create();
    pMenu->setAnchorPoint(CCPoint(0,0));
    pMenu->setPosition(CCPoint(0,0));
    for (int index=0; index<NUMBER_SNOW; index++) {
        
       // char* CNumber= new char;
        
        //CCMenuItemFont *number=CCMenuItemFont::create(CNumber, this, menu_selector(GameBoard::buttonNumber));
        CCMenuItemImage *number=CCMenuItemImage::create("SBtn.png", "SBtn_hover.png", this, menu_selector(GameBoard::buttonNumber));
        number->setScale(1.3);
        number->setTag(index);
        number->setAnchorPoint(CCPoint(0,0));
        
        char CNumber[32] = {0};
        sprintf(CNumber, "%d", (index+1));
        if(index<=4)
        {
            number->setPosition(CCPoint(40-10+index*118,250-20));
            CCLabelTTF*item= this->drawLable(CNumber, "HGRPP1.TTC", CCPoint(40-10+index*118+27+10,250+14+12-20), ccp(0,0), 23);
            item->setColor(ccBLACK);
            item->setScale(2);
        }
        else{
             number->setPosition(CCPoint(100-10+(index-5)*118,150-20));
            CCLabelTTF*item= this->drawLable(CNumber, "HGRPP1.TTC", CCPoint(100-10+(index-5)*118+27+10,150+14+12-20), ccp(0,0), 23);
            item->setColor(ccBLACK);
            item->setScale(2);
        }
        
        pMenu->addChild(number);
        
        
        //delete CNumber;
    }
    this->addChild(pMenu);
    
    /// add Ball- Snow - Animation to game    
    CCSpriteBatchNode*patchNodeSnow= ballSnow->iCreateBallAnimation("new",ccp(250, 400),CCPoint(0 , 0), 1,0);/// type=0
    patchNodeSnow->setTag(TAG_BALL);
    this->addChild(patchNodeSnow,5);
    // add shoot snow man to game
   
    
    
    ScoreNumber=this->drawLable("0", "HGRPP1.TTC", CCPoint(70 , 25), CCPoint(0 , 0), 50);
    ScoreNumber->setColor(ccBLUE);
    ScoreNumber->setZOrder(6);
    ScoreNumber->setVisible(false);
    textOK=this->drawLable("ok!", "HGRPP1.TTC", CCPoint(70 , 25), CCPoint(0 , 0), 50);
    textOK->setColor(ccRED);
    textOK->setZOrder(6);
    textOK->setVisible(false);
    
    
    
    
    
    return true;
}



void GameBoard::AllowSnowShooting()
{
    enableShooting=true;
}
void GameBoard::buttonNumber(CCObject* pSender)
{
    
    ///set shoot snow enemy
    if(enableShooting==false){CCLog("disable Shooting click");  return;}
    
    CCNode* node = (CCNode*) pSender;
    int tag = node->getTag();
    CCLOG("Tag %d- CurrentTag %d",tag,CurrentTag);
    
    if((tag+TAG_SNOW)==CurrentTag)
    {
        CCLog("Right shooting");
        CharacterAnimation * getCurrentCharacter=GameBoard::getCharactorById(tag+TAG_SNOW);
        if(getCurrentCharacter!=NULL)
        {
            getCurrentCharacter->charater->stopAllActions();
            getCurrentCharacter->beingAction=false;
            getCurrentCharacter->resetCharacter();
            enableShooting=false;
        }
        getCurrentCharacter=NULL;
        
        
        ShootingSnow=this->getCurrentMiliSecond();// get timer shooting
        CCLog("Shooting  SnowActionMilisecond %ld  Snow Shoot--------  %ld",SnowActionMilisecond,ShootingSnow);
         float KresultScore=abs(ShootingSnow- SnowActionMilisecond)/1000.0f;///giay
        if(KresultScore<0.66)
        {
            KresultScore=0;
        }
         CCLog("SCore --------  %8.8f",KresultScore);
         //float tempresult=(1000-resultScore)/100;
         
         long resultScore =10.0f-((KresultScore)*10.0)/1.4;
        if(resultScore<=0)//==0
        {
            resultScore=1;
        }
        
        CCLog("+++++++++++%f +++++++++++ %d",KresultScore,resultScore);
        this->updateScore(resultScore);
        this->drawScoreAtIndex(tag, resultScore);
        ballSnow->shooting(tag);
    
    }
    else{
        CCLog("Wrong shooting");
    }
    
    
}
void GameBoard::update(CCTime dt)
{
    if(EndGame==true){return;}
    //CCSpriteBatchNode*tempC=(CCSpriteBatchNode*)this->getChildByTag(indexCharacter+TAG_SNOW);
    //CCLOG("tempC =%d",indexCharacter);
    //CCLOG("tempC tag = %d",tempC->getTag());
   
    
    
    
    if(CurrentTag==-1){
        
        int indexCharacter=GameBoard::getRandomCharater();
        CharacterAnimation * getNewCharacter=GameBoard::getCharactorById(indexCharacter+TAG_SNOW);
        if(getNewCharacter!=NULL)
        {
            //CCLOG("Action Character with tag  %d",getNewCharacter->getTag());
            CurrentTag=getNewCharacter->getTag();
            CCLog("first time Snow Action milisecond --------  %ld",this->getCurrentMiliSecond());
            SnowActionMilisecond=this->getCurrentMiliSecond();  /// get timer current action
            getNewCharacter->ActionOneTime();
        }
    }
    else{
    
        CharacterAnimation * currentCharacter=GameBoard::getCharactorById(CurrentTag);
        if(currentCharacter->beingAction==true){return;}
        
        
        
        int indexCharacter=GameBoard::getRandomCharater();
        CharacterAnimation * getNewCharacter=GameBoard::getCharactorById(indexCharacter+TAG_SNOW);
    
        if(getNewCharacter!=NULL)
        {
            //CCLOG("Action Character with tag  %d",getNewCharacter->getTag());
            CurrentTag=getNewCharacter->getTag();
           // CCLog("Begin Snow Action milisecond --------  %ld",this->getCurrentMiliSecond());
            SnowActionMilisecond=this->getCurrentMiliSecond();  /// get timer current action
            getNewCharacter->ActionOneTime();
        }
    }
   
    
}
long GameBoard::getCurrentMiliSecond()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);

    //CCLog("%ld",(now.tv_sec/1000 +1)*1000);
    
    return (now.tv_sec * 1000 + now.tv_usec / 1000 );
    //return (now.tv_usec/1000 );
}
int GameBoard::getRandomCharater()
{
    int result=rand()%NUMBER_SNOW;   
    
    return result;
}
CharacterAnimation * GameBoard::getCharactorById(int iID)
{
    for (int index=0; index<_ArrayCharacter->count(); index++) {
                
        CharacterAnimation *  temp=(CharacterAnimation *)_ArrayCharacter->objectAtIndex(index);
       
        if(temp->getTag()==iID)
        {
            return temp;
        }
    }
    return NULL;
}



