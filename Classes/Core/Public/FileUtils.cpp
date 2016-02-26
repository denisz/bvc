//
//  FileUtils.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/16/16.
//
//

#include "FileUtils.hpp"

using namespace common;
const std::string kLookupFilesPath = "lookupfiles.xml";

FileUtils* FileUtils::_instance;

FileUtils::FileUtils()
: _module(cocos2d::FileUtils::getInstance()){
    _lookupfiles = internal::BVValueVector();
}

FileUtils* FileUtils::sharedInstance() {
    if (FileUtils::_instance == nullptr) {
        FileUtils::_instance = new FileUtils();
    }
    
    return FileUtils::_instance;
}

std::string FileUtils::preparePath(const std::string &filename) {
    return _module->getWritablePath() + filename;
}

void FileUtils::load() {
    auto fullpath = preparePath(kLookupFilesPath);
    auto paths = _module->getValueVectorFromFile(fullpath);
    
    for (auto path: paths) {
        _lookupfiles.push_back(internal::BVValue(path.asString()));
    }
}

void FileUtils::addSearchPath(const std::string& path) {
    if (!isFileExist(path)) {
        _lookupfiles.push_back(internal::BVValue(path));
    }
}

void FileUtils::removeSearchPath(const std::string& path) {
    auto paths = _lookupfiles;
    auto _path = internal::BVValue(path);
    auto it = std::find(paths.begin(), paths.end(), _path);
    if (it != paths.end()) {
        paths.erase(it);
    }
}

const internal::BVValueVector& FileUtils::getSearchPaths() const {
    return _lookupfiles;
}

void FileUtils::saveInBackground() {
    auto fullpath = preparePath(kLookupFilesPath);
    auto paths = getSearchPaths();
    _module->writeValueVectorToFile(paths, fullpath);
}

bool FileUtils::writeContentToFile(internal::BVValueMap& dict, const std::string& filename) {
    auto fullpath = preparePath(filename);
    if (_module->writeValueMapToFile(dict, fullpath)) {
        std::cout << "Save file " <<  fullpath << std::endl;
        addSearchPath(filename);
        saveInBackground();
        return true;
    }
    
    return false;
}

internal::BVValueMap FileUtils::readContentFromFile(const std::string &filename) {
    auto fullpath = preparePath(filename);
    return _module->getValueMapFromFile(fullpath);
}

bool FileUtils::removeFile(const std::string& filename) {
    auto fullpath = preparePath(filename);
    if (_module->removeFile(fullpath)) {
        removeSearchPath(fullpath);
        return true;
    }
    
    return false;
}

void FileUtils::findPathsWithPrefix(const std::string& prefix, SearchPaths& paths) {
    auto searchPaths = getSearchPaths();
    
    for (auto item: searchPaths) {
        auto path = item.asString();
        std::size_t found = path.find(prefix);
        if (found!=std::string::npos) {
            paths.push_back(path);
        }
    }
}

bool FileUtils::isFileExist(const std::string& filename) {
    auto path = internal::BVValue(filename);
    return std::find(_lookupfiles.begin(), _lookupfiles.end(), path) != _lookupfiles.end();
}

void FileUtils::removeDirectory (const std::string &dirPath) {
    _module->removeDirectory(dirPath);
}

void FileUtils::purgeWithPrefix (const std::string &prefix) {
    auto paths = std::vector<std::string>();
    findPathsWithPrefix(prefix, paths);
    
    for (auto path: paths) {
        removeFile(path);
    }
    
    saveInBackground();
}


void FileUtils::purge() {
    _module->purgeCachedEntries();
}

void FileUtils::createDirectory(const std::string& dirpath) {
    auto fullpath = preparePath(dirpath);
    _module->createDirectory(fullpath);
}
