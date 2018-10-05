//
//  GameBoard.h
//  Snow_6_cocos2dx
//
//  Created by antl on 4/16/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
#ifndef a_Snow_6_cocos2dx_Header_h
#include "cocos2d.h"
#include "CCMyScene.h"
#include "../Support/CharacterAnimation.h"
#include "../Support/ballSnowAnimation.h"

#define a_Snow_6_cocos2dx_Header_h


class GameBoard :public CCMyScene 
{    
 
    CCLabelTTF *ScoreNumber;
    CCLabelTTF *textOK;    
    CCLabelTTF *lableScore1;
    CCLabelTTF *lableScore2;
    static GameBoard* GameBoardInstance;
    
    long SnowActionMilisecond;
    long ShootingSnow;
    long iScore;
    int iNumberLose;
    bool EndGame;    
    bool enableShooting;
public:
    
    
    int CurrentTag;
    cocos2d::CCArray *_ArrayCharacter;
    ballSnowAnimation *ballSnow;
    
    
    
    ///function
    GameBoard();
    ~GameBoard();
    static GameBoard* GetGameBoardInstance();
    virtual bool init();
    static cocos2d::CCScene* scene();    
    void buttonNumber(CCObject* pSender);
    void update(CCTime dt);
    CharacterAnimation * getCharactorById(int iID);
    int getRandomCharater();   
    CREATE_FUNC(GameBoard);
    void AllowSnowShooting();
    /// instance 
    void SnowManBeginShootInstance();  // snow man shoot
    void SnowManShotedEndInstance();
    
    void ManShotedSnowManBeginInstance();
    void ManShotedSnowManEndInstance(); // shoot snow man
    /// score
    void updateScore(long Score);
    void IncreaseNumber();
    /// current milisecond
    long getCurrentMiliSecond();
    void drawScoreAtIndex(int index,long iScore);
    
    //// score
    void disibleScore();
    void VisibleScore();
    void ShowText();
    /// change Scene
    void repairChangeScene();
    void changeScene();
    
    
    
  
};

#endif
