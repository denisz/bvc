#include "AppDelegate.h"

USING_NS_CC;
using namespace game;

static float scale = 0.5;
static cocos2d::Size designResolutionSize = cocos2d::Size(768, 1024) * scale;

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
    
    ServiceLocator::create();
    
    const auto starter  = StarterViewController::create();
    const auto root     = RootViewController::sharedInstance();
    
    root->pushViewController(starter);
    
    window = UIKit::UIWindow::createWithSize(director->getVisibleSize());
    window->setRootViewController(root);
    director->runWithScene(window->scene());

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
     CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
     CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
