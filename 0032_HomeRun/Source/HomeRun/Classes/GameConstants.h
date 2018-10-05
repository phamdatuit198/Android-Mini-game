//
//  GameConstants.h
//  homerun
//
//  Created by admin on 5/14/13.
//
//

#ifndef homerun_GameConstants_h
#define homerun_GameConstants_h

#ifndef SCREEN_WIDTH_HALF
#define SCREEN_WIDTH_HALF   CCDirector::sharedDirector()->getWinSize().width/2
#endif

#ifndef SCREEN_HEIGHT_HALF
#define SCREEN_HEIGHT_HALF CCDirector::sharedDirector()->getWinSize().height/2
#endif

#define TESTING 0

#define TESTING_1   0

#define KEYPAD_TOUCHED_NOTIFICATION "kKeyPadTouchedNotification"

#define MAX_BALL_COUNT  10

#define px  82.5    // ?
#define py  139     // ?
#define pw  25      // ?

#define p_y_n   3
#define p_n     9
//投げる球について
//ボール初期値
#define b_sX        0//120 // ?
#define b_sY        ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 587):(-SCREEN_HEIGHT_HALF + 895))//diem bat dau cua trai bong
//size(height)
#define b_h         19  // ?
//ピッチャーが持ってるときの球のscale
#define b_s         40

//#define b_spH       27//5  // 27
//#define b_spSC      43//8
//#define b_spSLR     43//8

#define sb_lHX      -89//-3.4//-3.4//105 // ?
#define sb_rHX      89//3.4//3.4//135 // ?

#define sb_sX       0 // ?
#define sb_sY       ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 515):(-SCREEN_HEIGHT_HALF + 820))// diem bat dau cua bong cua trai bong
#define sb_s        40

//#define b_uHY       (-SCREEN_HEIGHT_HALF + 388)//-104//-90//151//154//150
//#define b_uHYS      (-SCREEN_HEIGHT_HALF + 435)//-62//-69//117//114//142
//#define b_mHY       (-SCREEN_HEIGHT_HALF + 272)//-221//-144//156//161//175
//#define b_dHY       (-SCREEN_HEIGHT_HALF + 202)//-278//-208//159//165//188
//289,333,204,160
#define b_uHY       ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 289):(-SCREEN_HEIGHT_HALF + 385))//-104//-90//151//154//150
#define b_uHYS      ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 333):(-SCREEN_HEIGHT_HALF + 440))//-62//-69//117//114//142
#define b_mHY       ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 204):(-SCREEN_HEIGHT_HALF + 251))//-221//-144//156//161//175
#define b_dHY       ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 160):(-SCREEN_HEIGHT_HALF + 185))//-278//-208//159//165//188

#define sb_HY       ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 60):(-SCREEN_HEIGHT_HALF + 70))//111//215

#define sb_MaxY     (-SCREEN_HEIGHT_HALF - b_h/2)

#define mth_1       -6
#define mth_2       -4

#define max_b_c_4   20

// Home run
#define sb_maxY_HR  ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 647):(-SCREEN_HEIGHT_HALF + 1027))// vi tri duong bien xa nhat bong bay


#define MISS_Y_1     ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 200):(-SCREEN_HEIGHT_HALF + 260))
#define MISS_Y_2     ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 10):(-SCREEN_HEIGHT_HALF + 10))
#define HR_Y_1      ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 150):(-SCREEN_HEIGHT_HALF + 180))
#define HR_Y_2      ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 30):(-SCREEN_HEIGHT_HALF + 45))

#define KEYPAD_X    0
#define KEYPAD_Y    (-SCREEN_HEIGHT_HALF + 260)

#define HR_BALL_FALL    ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 670):(-SCREEN_HEIGHT_HALF + 1100))//320.f diem bat dau bong roi xuong

#define THROW_TYPE_3_1  ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 340):(-SCREEN_HEIGHT_HALF + 560))
#define THROW_TYPE_3_2  ((SCREEN_HEIGHT_HALF == 400)?(-SCREEN_HEIGHT_HALF + 330):(-SCREEN_HEIGHT_HALF + 550))


//B_UHYS = -SCREEN_HEIGHT_HALF + 333;   // 67
//B_UHY  = -SCREEN_HEIGHT_HALF + 289;   //
//B_MHY  = -SCREEN_HEIGHT_HALF +204;
//B_DHY  = -SCREEN_HEIGHT_HALF + 160;
//
//B_SY   = -SCREEN_HEIGHT_HALF + 587;
//SB_SY  = -SCREEN_HEIGHT_HALF + 495;
//SB_HY  = -SCREEN_HEIGHT_HALF + 60;
#endif
