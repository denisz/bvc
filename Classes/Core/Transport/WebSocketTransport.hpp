//
//  WebSocketTransport.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef WebSocketTransport_hpp
#define WebSocketTransport_hpp

#include "stdafx.h"
#include <stdio.h>
#include "network/WebSocket.h"
#include "TransportProtocol.hpp"

namespace internal {
    namespace network {
        class WebSocketTransport: public TransportProtocol, public cocos2d::network::WebSocket::Delegate {
            
        private:
//            cocos2d websocket
            virtual void onOpen(cocos2d::network::WebSocket* ws);
            virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
            virtual void onClose(cocos2d::network::WebSocket* ws);
            virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
            
            cocos2d::network::WebSocket* _wsClient;
            TransportProtocol::State _readyState;
            std::string _url;
            bool _isReconnect;
            WebSocketTransport();
        public:
            ~WebSocketTransport();
            
            virtual void send(const std::string& message);
            virtual void close();
            virtual void reconnect();
            virtual void connect(const std::string& url);
            virtual TransportProtocol::State getReadyState();
            
            std::string protocol();
            
            bool init();

            
            static WebSocketTransport* create();
        };
    }
}

#endif /* WebSocketTransport_hpp */
