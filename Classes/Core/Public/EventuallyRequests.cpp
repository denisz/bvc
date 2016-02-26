//
//  EventuallyRequests.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/15/16.
//
//

#include "EventuallyRequests.hpp"

using namespace common;
using namespace internal::network;

EventuallyRequests::EventuallyRequests() {
    FileUtils::sharedInstance()->createDirectory(kEventuallyDirPath);
}

bool EventuallyRequests::deferredRequest(Request &req) {
    internal::BVValueMap dict;
    dict["time"] = std::to_string(req.timestamp);
    dict["req"]  = req.outReadyMessage();
    
    return FileUtils::sharedInstance()->writeContentToFile(dict, generateFileName(req));
}

EventuallyRequests::HandlerEventually EventuallyRequests::process() {
    auto promise = Bolts::BFTaskCompletionSource<Bolts::BFBool>::taskCompletionSource();
    auto paths = std::vector<std::string>();
    FileUtils::sharedInstance()->findPathsWithPrefix(kEventuallyDirPath, paths);

    for (auto path: paths) {
        auto map = FileUtils::sharedInstance()->readContentFromFile(path);
    }

    return promise->task();
}

std::string EventuallyRequests::generateFileName(Request &req) {
    auto time = std::to_string(req.timestamp);
    return fmt::format("{0}{1}.xml", kEventuallyDirPath, time);
}

EventuallyRequests* EventuallyRequests::create() {
    auto ref = new EventuallyRequests();
    return ref;
}