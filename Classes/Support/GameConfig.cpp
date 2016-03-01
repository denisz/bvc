//
//  GameConfig.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//
#include "GameConfig.hpp"

GameConfig * GameConfig::__sharedInstance = nullptr;

GameConfig::~GameConfig() {}

GameConfig::GameConfig() {}

GameConfig * GameConfig::sharedInstance() {
    if(__sharedInstance == nullptr) {
        __sharedInstance = new GameConfig();
    }
    
    return __sharedInstance;
}

void GameConfig::load() {
    
}

void GameConfig::save() {
    
}

void GameConfig::loadFilePaths() {
    unsigned char *t = nullptr;
    ssize_t configDataSize = 0;
    t = (cocos2d::FileUtils::getInstance()->getFileData("config.json", "r", &configDataSize));
    
    char *configData = new char[configDataSize + 1];
    memcpy(configData, t, configDataSize);
    configData[configDataSize] = NULL;
    
    delete[] t;
    t = NULL;
    
    auto currentLanguage = cocos2d::Application::getInstance()->getCurrentLanguage();
    auto languagePrefix = Localized::languageShortNameForType(currentLanguage);
    
    auto addResourcePath = [=](const std::string &path) {
        cocos2d::FileUtils::getInstance()->addSearchPath((path + languagePrefix).c_str());
        cocos2d::FileUtils::getInstance()->addSearchPath(path.c_str());
    };
    
    auto frameSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
    
    rapidjson::Document configDoc;
    configDoc.Parse<0>(configData);
    
    std::string layoutBaseDimensionType = configDoc["layoutBaseDimension"].GetString();
    
    float frameBaseDimension = frameSize.height;
    
    if(layoutBaseDimensionType.compare("width") == 0) {
        frameBaseDimension = frameSize.width;
    }
    
    const auto &designEntriesArray = configDoc["designResolutionEntries"];
    if(designEntriesArray.IsArray()) {
        for(int i = designEntriesArray.Size() - 1; i >= 0; --i) {
            const auto &currentDeviceEntry = designEntriesArray[i];
            
            if(currentDeviceEntry.IsObject()) {
                double currentResolutionBaseDimension = currentDeviceEntry[layoutBaseDimensionType.c_str()].GetDouble();
                
                if(frameBaseDimension > currentResolutionBaseDimension) {
                    int requiredEntryIndex = MIN(i + 1, designEntriesArray.Size() - 1);
                    const auto &requiredEntry = designEntriesArray[requiredEntryIndex];
                    double requiredBaseDimension = requiredEntry[layoutBaseDimensionType.c_str()].GetDouble();
                    
                    //
                    double layoutWidth = requiredEntry["designWidth"].GetDouble();
                    double layoutHeight = requiredEntry["designHeight"].GetDouble();
                    
                    this->setDesignLayoutSize({static_cast<float>(layoutWidth), static_cast<float>(layoutHeight)});
                    
                    float designLayoutBaseDimension = layoutHeight;
                    ResolutionPolicy policy = ResolutionPolicy::FIXED_HEIGHT;
                    
                    if(layoutBaseDimensionType.compare("width") == 0) {
                        designLayoutBaseDimension = layoutWidth;
                        //frameBaseDimension = frameSize.width;
                        policy = ResolutionPolicy::FIXED_WIDTH;
                    }
                    
                    const auto director = cocos2d::Director::getInstance();
                    
                    director->getOpenGLView()->setDesignResolutionSize(layoutWidth, layoutHeight, policy);
                    director->setContentScaleFactor(requiredBaseDimension / designLayoutBaseDimension);
                    
                    const auto visibleSize = director->getVisibleSize();
                    
                    this->setVisibleOrigin({static_cast<float>((visibleSize.width - layoutWidth) / 2.0), static_cast<float>((visibleSize.height - layoutHeight) / 2.0)});
                    //
                    
                    // load required entry and all the entries above
                    for(; requiredEntryIndex >= 0; --requiredEntryIndex) {
                        const auto &entryToLoad = designEntriesArray[requiredEntryIndex];
                        
                        if(entryToLoad.IsObject()) {
                            for(auto it = entryToLoad["paths"].Begin(); it != entryToLoad["paths"].End(); ++it) {
                                std::string path = it->GetString();
                                addResourcePath(path);
                            }
                        }
                    }
                    
                    // stop iterating all the rest entries
                    break;
                }
            }
        }
    }
    
    // load shared paths
    
    const auto &sharedPathsArray = configDoc["sharedPaths"];
    if(sharedPathsArray.IsArray()) {
        for(auto it = sharedPathsArray.Begin(); it != sharedPathsArray.End(); ++it) {
            std::string path = it->GetString();
            addResourcePath(path);
        }
    }
    
    delete[] configData;
}

cocos2d::Size GameConfig::getDesignLayoutSize() {
    return this->designLayoutSize;
}

cocos2d::Point GameConfig::getVisibleOrigin() {
    return this->visibleOrigin;
}

void GameConfig::setDesignLayoutSize(const cocos2d::Size &size) {
    this->designLayoutSize = size;
}

void GameConfig::setVisibleOrigin(const cocos2d::Point &point) {
    this->visibleOrigin = point;
}