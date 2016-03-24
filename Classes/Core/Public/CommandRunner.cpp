//
//  CommandRunner.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "CommandRunner.hpp"

using namespace common;
using namespace internal::network;
using namespace Bolts;

int indexCalbackID = 0;
const std::string generateCallbackID() {
    return fmt::format("_{0}", indexCalbackID++);
}

bool needSaveResponse(int cachePolicy) {
    if  (cachePolicy == kCachePolicyCacheElseNetwork ||
         cachePolicy == kCachePolicyNetworkElseCache ||
         cachePolicy == kCachePolicyCacheOnly ||
         cachePolicy == kCachePolicyCacheThenNetwork ) {
            return true;
    };
    
    return false;
}

CommandRunner::CommandRunner()
: delegate(nullptr)
, _reaction(nullptr)
, _networkClient(nullptr)
, _subscribed(false) {

}

CommandRunner::~CommandRunner() {
    CC_SAFE_RELEASE_NULL(_networkClient);
    CC_SAFE_RELEASE_NULL(_reaction);
    
    for (auto &item: _callbacks) {
        CC_SAFE_RELEASE(item.second);
    }
    _callbacks.clear();
    
    for (auto &item: _completed_callbacks) {
        CC_SAFE_RELEASE(item);
    }
    _completed_callbacks.clear();
    
    delegate = nullptr;
}

CommandRunner* CommandRunner::create() {
    return CommandRunner::createWithNetworkClient(ServiceLocator::network());
}

CommandRunner* CommandRunner::createWithNetworkClient(NetworkClient* netClient) {
    auto runner = new CommandRunner();
    
    if (runner->initWithNetworkClient(netClient)) {
        return runner;
    }
    
    delete runner;
    runner = nullptr;
    return nullptr;
}

bool CommandRunner::initWithNetworkClient(NetworkClient* netClient) {
    _reaction               = Reaction::createWithDelegate(this);
    _callbacks              = Callbacks();
    _completed_callbacks    = CompletedCallbacks();
    _networkClient = netClient;
    CC_SAFE_RETAIN(_networkClient);
    return true;
}

void CommandRunner::subscribe() {
    if (_subscribed == false && _reaction != nullptr) {
        _reaction->subscribe();
    }
}

void CommandRunner::unsubscribe() {
    if (_subscribed == true && _reaction != nullptr) {
        _reaction->unsubscribe();
    }
}

NetworkClient* CommandRunner::networkClient() {
    return _networkClient;
}

CommandRunner::Handler* CommandRunner::runNetworkCommandAsync(RequestCommand &command) {
    auto network = networkClient();
    auto promise = CommandRunner::CompletionSource::taskCompletionSource();
    
    if (network == nullptr || !network->isOpenConnect()) {
        _completed_callbacks.push_back(promise);
        promise->trySetError(BFError::DISCONNECT);
        return promise->task();
    }
    
    auto callback_ID = generateCallbackID();
    _callbacks.insert(PairCallbacks(callback_ID, promise));
    command.setCallbackId(callback_ID);
    
    subscribe();
    
    auto req = command.request();
    network->sendMessage(req);
    
    return promise->task();
}

CommandRunner::Handler* CommandRunner::runNetworkCommandAsyncFromCache(RequestCommand &command) {
    auto promise = CommandRunner::CompletionSource::taskCompletionSource();
    _completed_callbacks.push_back(promise);
    
    std::async([&promise, &command](){
        std::string pin;
        
        if (command.checkPinningEnabled()) {
            pin = command.fromPin();
        } else {
            pin = command.hash();
        }
        
        auto cacheExists = ServiceLocator::cache()->existsCache(pin);
        if (cacheExists) {
            auto res = ServiceLocator::cache()->loadInBackgroundWithName(pin);
            if (res != nullptr) {
                promise->trySetResult(*res);
            } else {
                promise->trySetError(BFError::EMPTY);
            }
        } else {
            promise->trySetError(BFError::EMPTY);
        }
    });
    
    return promise->task();
}

CommandRunner::Handler* CommandRunner::runCommandAsync(RequestCommand &command) {
    std::lock_guard<std::mutex> lock(_mutex);
    CC_SAFE_RETAIN(&command);
    
    CommandRunner::Handler* task;
    
    int cachePolicy = command.cachePolicy;
    
    if (cachePolicy == kCachePolicyIgnoreCache) {
        task = runNetworkCommandAsync(command);
    } else if (cachePolicy == kCachePolicyCacheOnly) {
        task = runNetworkCommandAsyncFromCache(command);
    } else if (command.cachePolicy == kCachePolicyNetworkOnly) {
        task = runNetworkCommandAsync(command);
    } else if (cachePolicy == kCachePolicyCacheThenNetwork) {
        task = runNetworkCommandAsyncFromCache(command)->continueWithBlock([&](CommandRunner::Handler *task)-> CommandRunner::Handler* {
            if (task->hasError()) {
                return this->runNetworkCommandAsync(command);
            } else {
                CC_SAFE_RETAIN(&command);
                this->runNetworkCommandAsync(command)->continueWithBlock([&](CommandRunner::Handler *task)-> CommandRunner::Handler* {
                    if (!task->hasError()) {
                        auto res = task->result();
                        auto cacheHash = command.hash();
                        CommandRunner::pinInBackgroundWithName(cacheHash, res);
                    }
                    
                    CC_SAFE_RELEASE(&command);
                    return nullptr;
                });
            }
            
            return nullptr;
        });
    } else if (cachePolicy == kCachePolicyNetworkElseCache) {
        task = runNetworkCommandAsync(command)->continueWithBlock([&](CommandRunner::Handler *task)-> CommandRunner::Handler* {
            if (task->hasError()) {
                return this->runNetworkCommandAsyncFromCache(command);
            }
            return nullptr;
        });
    } else if (cachePolicy == kCachePolicyCacheElseNetwork) {
        task = runNetworkCommandAsyncFromCache(command)->continueWithBlock([&](CommandRunner::Handler *task)-> CommandRunner::Handler* {
            if (task->hasError()) {
                return this->runNetworkCommandAsync(command);
            }
            return nullptr;
        });
    }
    
    return task->continueWithBlock([&](CommandRunner::Handler *task)-> CommandRunner::Handler* {
        bool needSave = needSaveResponse(command.cachePolicy);

        if (!task->hasError() && needSave) {
            auto res = task->result();
            if (res->source == Response::Source::NETWORKCLIENT) {
                auto cacheHash = command.hash();
                CommandRunner::pinInBackgroundWithName(cacheHash, res);
            }
        }
        
        CC_SAFE_RELEASE(&command);
        return nullptr;
    });
}

void CommandRunner::runCommand(RequestCommand &command) {
    auto network = networkClient();
    if (network != nullptr) {
        auto req = command.request();
        network->sendMessage(req);
    }
}

void CommandRunner::processMessage(Response& res) {
    if (res.isAnswer()) {
        std::lock_guard<std::mutex> lock(_mutex);
        
        auto it = _callbacks.find(res.callbackId());
        if (it != _callbacks.end()) {
            auto promise = it->second;
            promise->trySetResult(res);
            _completed_callbacks.push_back(promise);
            _callbacks.erase(it);
            if (_callbacks.empty()) {
                unsubscribe();
            }
        }
    }
}

void CommandRunner::processError(Response& res) {
    
}

void CommandRunner::processClose() {
    //_callbacks.clear();
    //unsubscribe();
}

void CommandRunner::processOpen() {
    
}

void CommandRunner::didSubscribe() {
    _subscribed = true;
}

void CommandRunner::didUnsubscribe() {
    _subscribed = false;
}

void CommandRunner::pinInBackgroundWithName(const std::string& name, Response* res) {
    ServiceLocator::cache()->saveInBackgroundWithName(name, res);
}

void CommandRunner::unpinObjectsInBackgroundWithName(const std::string& name) {
    
}
