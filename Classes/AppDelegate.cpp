#include "AppDelegate.h"
#include "PresentScene.h"
#include "MainScene.h"
#include "DialogueScene.h"
#include "ClassScene.h"
#include "Common.h"
#include "IntroScene.h"

USING_NS_CC;

#define DEBUG	true

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("HackaThon_TeamGajoku");
        director->setOpenGLView(glview);
    }

	// 다양한 해상도 지원
	Size winSize = Director::sharedDirector()->getWinSize();
	glview->setFrameSize(winSize.width, winSize.height);
	glview->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, kResolutionShowAll);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
   // auto scene = StartScene::createScene();

	auto testScene = MainScene::createScene();
	auto scene = PresentScene::createScene();

	// run
	if (DEBUG)
		director->runWithScene(testScene);
	else
		director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
