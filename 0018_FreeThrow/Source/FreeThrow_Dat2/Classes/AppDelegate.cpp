#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Scenes/DemoScene.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}
typedef struct tagResource {
	cocos2d::CCSize size;
	char directory[100];
} Resource;
static Resource mediumResource = {cocos2d::CCSizeMake(480,800),"480x800"};

static Resource largeResource = {cocos2d::CCSizeMake(720,1280),"720x1280"};

static cocos2d::CCSize designResolutionSize;
bool AppDelegate::applicationDidFinishLaunching()
{
	 CCDirector *pDirector = CCDirector::sharedDirector();
	    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	    // Set the design resolution
	    	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	    	std::vector < std::string > searchPaths;

	    // if the frame's height is larger than the height of medium resource size, select large resource.
	    	if (frameSize.width == largeResource.size.width) {
	    		searchPaths.push_back(largeResource.directory);
	    		pDirector->setContentScaleFactor(
	    				largeResource.size.height / largeResource.size.height);
	    		designResolutionSize = cocos2d::CCSizeMake(largeResource.size.width,
	    				largeResource.size.height);
	    		CCLOG("android ");
	    	}
	    // if the frame's height is larger than the height of small resource size, select medium resource.
	    	else if (frameSize.width == mediumResource.size.width) {
	    		searchPaths.push_back(mediumResource.directory);
	    		pDirector->setContentScaleFactor(
	    				mediumResource.size.height / mediumResource.size.height);
	    		designResolutionSize = cocos2d::CCSizeMake(mediumResource.size.width,
	    				mediumResource.size.height);
	    		CCLOG("tablet ");
	    	}
	    	else
	    	{
	    		searchPaths.push_back(largeResource.directory);
	    		    		pDirector->setContentScaleFactor(
	    		    				largeResource.size.height / largeResource.size.height);
	    		    		designResolutionSize = cocos2d::CCSizeMake(largeResource.size.width,
	    		    				largeResource.size.height);
	    		    		CCLOG("android ");
	    	}

	    	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
	    	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(
	    			designResolutionSize.width, designResolutionSize.height,
	    			kResolutionNoBorder);


	    // turn on display FPS
	   // pDirector->setDisplayStats(false);

	    // set FPS. the default value is 1.0/60 if you don't call this
	    pDirector->setAnimationInterval(1.0 / 60);

	    // create a scene. it's an autorelease object
	    CCScene *pScene = DemoScene::scene();

	    // run
	    pDirector->runWithScene(pScene);

	    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
