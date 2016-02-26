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

USING_NS_CC;

class GameConfig {
private:
    GameConfig();
    void setDesignLayoutSize(const Size &size);
    void setVisibleOrigin(const Point &point);
public:
    ~GameConfig();
    
    void load();
    void save();
    
    Size getDesignLayoutSize();
    Point getVisibleOrigin();
    
    void loadFilePaths();
    
    static GameConfig* sharedInstance();
private:
    static GameConfig *__sharedInstance;
    
    Point visibleOrigin;
    Size designLayoutSize;
};


#endif /* defined(__solveMe__GameConfig__) */