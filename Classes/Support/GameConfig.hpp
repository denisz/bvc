//
//  GameConfig.h
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#ifndef __solveMe__GameConfig__
#define __solveMe__GameConfig__

#include "cocos2d.h"
#include <string>
#include "Localized.hpp"

class GameConfig {
private:
    GameConfig();
    void setDesignLayoutSize(const cocos2d::Size &size);
    void setVisibleOrigin(const cocos2d::Point &point);
public:
    ~GameConfig();
    
    void load();
    void save();
    
    cocos2d::Size getDesignLayoutSize();
    cocos2d::Point getVisibleOrigin();
    
    void loadFilePaths();
    
    static GameConfig* sharedInstance();
private:
    static GameConfig *__sharedInstance;
    
    cocos2d::Point visibleOrigin;
    cocos2d::Size designLayoutSize;
};


#endif /* defined(__solveMe__GameConfig__) */