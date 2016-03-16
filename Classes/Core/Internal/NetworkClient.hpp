//
//  NetworkClient.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef NetworkClient_hpp
#define NetworkClient_hpp

#include "stdafx.h"
#include "TransportProtocol.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include "Parser.hpp"

namespace internal {
    namespace network {
        
        class NetworkClient: public AIRef, public TransportProtocol::Delegate {
        public:
            
            class Events: public  BaseObserverProtocol {
            public:
                virtual void onError(Response *res) {};
                virtual void onReceivedMessage(Response *res) {};
                virtual void onOpen()       {};
                virtual void onClose()      {};
                virtual void onReconnect()  {};
            };

            void connect(const std::string &url);
            void sendMessage(const std::string &message);
            void sendMessage(Request &req);
            void reconnect();
            void close();
            bool isOpenConnect();
        private:

            NetworkClient();
            Parser* _parser;
            TransportProtocol *_transport;
            Response* tryCreateSuccesfullResponse(TransportProtocol::Data &data);
            Response* tryCreateErrorResponse(TransportProtocol::ErrorCode &error);
            
            virtual void onError(const TransportProtocol* transport, TransportProtocol::ErrorCode &error);
            virtual void onMessage(const TransportProtocol* transport, TransportProtocol::Data &data);
            virtual void onClose(const TransportProtocol* transport);
            virtual void onOpen(const TransportProtocol* transport);
            virtual void onReconnect(const TransportProtocol* transport);
            
            bool initWithTransport(TransportProtocol *transport);
        public:
            ~NetworkClient();

            static NetworkClient* createWithTransport(TransportProtocol* transport);
        };
    }
}

#endif /* NetworkClient_hpp */
