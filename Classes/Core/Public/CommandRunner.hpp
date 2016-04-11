//
//  CommandRunner.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef CommandRunner_hpp
#define CommandRunner_hpp

#include "stdafx.h"
#include "RequestCommand.hpp"
#include "ServiceLocator.hpp"
#include "Reaction.hpp"
#include "NetworkClient.hpp"

namespace common {
    class CommandRunner: public internal::AIRef, public common::Reaction::Delegate  {
    public:
        class Delegate {
            virtual void processResponse(CommandRunner *runner, Response *response) = 0;
        };
        
        const int TIMEOUT = 10;
        
        typedef Bolts::BFTaskCompletionSource<Response> CompletionSource;
        typedef Bolts::BFTask<Response> Handler;
        typedef std::vector<CompletionSource*> CompletedCallbacks;
        typedef std::pair<std::string, CompletionSource*> PairCallbacks;
        typedef std::map<const std::string, CompletionSource*> Callbacks;
        
    private:
        bool _subscribed;
        Reaction* _reaction;

        virtual void processOpen();
        virtual void didSubscribe();
        virtual void processClose();
        virtual void didUnsubscribe();
        virtual void processError(internal::network::Response &res);
        virtual void processMessage(internal::network::Response &res);

        std::mutex _mutex;
        
        NetworkClient* _networkClient;
        NetworkClient* networkClient();
        
        Callbacks  _callbacks;
        CompletedCallbacks _completed_callbacks;
        
        Handler* runNetworkCommandAsync(RequestCommand &command);
        Handler* runNetworkCommandAsyncFromCache(RequestCommand &command);
        
        void subscribe();
        void unsubscribe();
        
        CommandRunner();
        bool initWithNetworkClient(NetworkClient* netClient);
    public:
        ~CommandRunner();
        
        Delegate* delegate;
        Handler* runCommandAsync(RequestCommand &command);
        void runCommand(RequestCommand &command);
        
        static CommandRunner* create();
        static CommandRunner* createWithNetworkClient(NetworkClient* netClient);
        
        static void pinInBackgroundWithName(const std::string& name, Response* res);
        static void unpinObjectsInBackgroundWithName(const std::string& name);
    };
}

#endif /* CommandRunner_hpp */
