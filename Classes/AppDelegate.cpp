#include "AppDelegate.h"

USING_NS_CC;
using namespace game;


static cocos2d::Size designResolutionSize = cocos2d::Size(512, 384);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    GameConfig::sharedInstance()->save();
    delete GameConfig::sharedInstance();
    Localized::purge();
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("bvunity", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("bvunity");
#endif
        director->setOpenGLView(glview);
    }
    
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    GameConfig::sharedInstance()->load();
    GameConfig::sharedInstance()->loadFilePaths();
    Localized::load();
    
    ServiceLocator::create();
    auto starter = StarterController::create();
    window = UIWindow::create();
    window->setRootViewController(starter->getViewController());
    director->runWithScene(window->scene());
    
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
//     SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
