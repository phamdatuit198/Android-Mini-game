//
//  GlobalData.h
//  Snow_6_cocos2dx
//
//  Created by Soa Nguyen on 5/24/13.
//
//

#ifndef Snow_6_cocos2dx_GlobalData_h
#define Snow_6_cocos2dx_GlobalData_h

int gameScore;
int currentThrowBallScore;
//int currentSenceScore;
bool exitGameInExtraMode;

//bool continueExelentMode;
int numInExelent;

int gameMode;

int numberOfShoot;
int numberThrowBallGoal;
int numOfBall;
int currentBall;
float HEIGH_OF_POWER_BAR = 200.0f;


const float MAXIMUM_POWER = 150.0f;
const float MINIMUM_POWER = 20.0f;


float MINIMUM_GOAL_POWER = 87.0f;
float MAXIMUM_GOAL_POWER = 110.0f;

float GOAL_BONUS_POWER_MAX = 105.0f;
float GOAL_BONUS_POWER_MIN = 97.0f;

const int GAME_NUMBER_SENCE = 9;

const int GOAL_ANGEL_BALL_MIN = 80;
const int GOAL_ANGEL_BALL_MAX = 100;

const int SCORE_TO_MOVE_NEXT_SENCE_IN_EXTRA = 7;
const int SCORE_TO_MOVE_NEXT_SENCE_IN_NORMAL = 5;

enum BALL_INDEX {
    BALL_LEVEL_1 = 1,
    BALL_LEVEL_2 = 2,
    BALL_LEVEL_3 = 3,
    BALL_LEVEL_4 = 4,
    BALL_LEVEL_5 = 5,
    BALL_LEVEL_6 = 6,
    BALL_LEVEL_7 = 7,
    BALL_LEVEL_8 = 8,
    BALL_LEVEL_9 = 9,
    };

enum BALL_WEIGHT {
    BALL_WEIGHT_1 = 0,
    BALL_WEIGHT_2 = 5,
    BALL_WEIGHT_3 = 10,
    BALL_WEIGHT_4 = 15,
    BALL_WEIGHT_5 = 20,
    BALL_WEIGHT_6 = 25,
    BALL_WEIGHT_7 = 30,
    BALL_WEIGHT_8 = 35,
    BALL_WEIGHT_9 = 40,
};

enum GAME_MODE {
    NORMAL = 0,
    EXTRA = 1
    };



#endif
