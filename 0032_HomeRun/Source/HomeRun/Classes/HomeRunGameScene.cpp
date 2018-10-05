#include "HomeRunGameScene.h"
#include "SimpleAudioEngine.h"
#include "BackgroundLayer.h"
#include "NDKHelper.h"
#include "AppDelegate.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HomeRunGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HomeRunGame *layer = HomeRunGame::create();
    layer->setTag(1000);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HomeRunGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
//    AppDelegate* appDelegate = ((AppDelegate*)CCApplication::sharedApplication());
//            appDelegate->newgame = false;
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    CCSize sizeMain = CCDirector::sharedDirector()->getWinSize();
    CCPoint pointCenter = ccp(sizeMain.width / 2, sizeMain.height / 2);
    
    // Add background
//    BackgroundLayer *pBackground = BackgroundLayer::create();
//    pBackground->setPosition(pointCenter);
//    this->addChild(pBackground, -1);
    
    // Add game scene
//    CCSprite *gameBackgroundSprite = NULL;
//
//     gameBackgroundSprite = CCSprite::create("background.png");
//     gameBackgroundSprite->setPosition(ccp(0,0));
//     gameBackgroundSprite->setAnchorPoint(ccp(0,0));
//     this->addChild(gameBackgroundSprite);
    pHomeRunGame = HomeRunGameLayer::create();
    pHomeRunGame->setPosition(pointCenter);
    pHomeRunGame->mainGameScene = this;
    this->addChild(pHomeRunGame, 0);
    
//    pHomeRunGame->schedule(schedule_selector(HomeRunGameLayer::runAnimation), 2.f);

//    // add a "close" icon to exit the progress. it's an autorelease object
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                        "CloseNormal.png",
//                                        "CloseSelected.png",
//                                        this,
//                                        menu_selector(HelloWorld::menuCloseCallback) );
//    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
//
//    // create menu, it's an autorelease object
//    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//    pMenu->setPosition( CCPointZero );
//    this->addChild(pMenu, 1);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
//
//    // ask director the window size
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//
//    // position the label on the center of the screen
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
//
//    // add the label as a child to this layer
//    this->addChild(pLabel, 1);
//
//    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    pSprite->setPosition( ccp(size.width/2, size.height/2) );
//
//    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);
    
    return true;
}

void HomeRunGame::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HomeRunGame::finishGame(int score)
{
    NDKHelper::AddSelector("HomeRunGameSelectors",
                           "finishGameWithDictionary",
                           callfuncND_selector(HomeRunGame::finishGameWithDictionary),
                           this);
    CCDictionary *dict = CCDictionary::create();
    
    char strScore[255];
    sprintf(strScore, "%d", score);
    
    dict->setObject(CCString::create(strScore), "score");
    
    SendMessageWithParams(string("finishGameWithDictionary"), dict);

    this->scheduleOnce(schedule_selector(HomeRunGame::newGame),0.5);
}

void HomeRunGame::finishGameWithDictionary(cocos2d::CCNode *sender, void *diction)
{
    
}

void HomeRunGame::newGame()
{
    pHomeRunGame->newGame();
}

void HomeRunGame::pauseGame()
{
    pHomeRunGame->pauseGame();
}

void HomeRunGame::resumeGame()
{
    pHomeRunGame->resumeGame();
}
