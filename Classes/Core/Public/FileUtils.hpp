//
//  FileUtils.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/16/16.
//
//

#ifndef FileUtils_hpp
#define FileUtils_hpp

#include "stdafx.h"

namespace common {
    class FileUtils {
    private:
        typedef std::vector<std::string> SearchPaths;
    private:
        cocos2d::FileUtils *_module;

        internal::BVValueVector _lookupfiles;
        void removeSearchPath(const std::string& filename);
        void addSearchPath(const std::string &path);
        const internal::BVValueVector &getSearchPaths() const;
        
        std::string preparePath(const std::string &filename);
        static FileUtils* _instance;
        FileUtils();
    public:
        void load();
        
        void removeDirectory (const std::string &dirPath);
        bool removeFile(const std::string &filename);
        bool isFileExist(const std::string &filename);
        void createDirectory(const std::string& dirpath);
        void findPathsWithPrefix(const std::string& prefix, SearchPaths& paths);
        void purgeWithPrefix (const std::string &prefix);
        
        void saveInBackground();
        void purge();
        bool writeContentToFile(internal::BVValueMap &dict, const std::string &filename);
        internal::BVValueMap readContentFromFile(const std::string &filename);
        
        static FileUtils* sharedInstance();
    };
}

#endif /* FileUtils_hpp */
