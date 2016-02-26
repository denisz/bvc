//
//  TransportProtocol.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/7/16.
//
//

#ifndef Transport_hpp
#define Transport_hpp

#include "stdafx.h"
#include <stdio.h>


namespace internal {
    namespace network {
        
        class TransportProtocol: public internal::AIRef {
        public:
            enum class State { CONNECTING, OPEN, CLOSING, CLOSED };
            
            
            struct Data
            {
                Data():bytes(nullptr), len(0), issued(0), isBinary(false){}
                const char* bytes;
                time_t time;
                ssize_t len, issued;
                bool isBinary;
            };
            
            //Opcode
            enum class ErrorCode
            {
                TIME_OUT,
                CONNECTION_FAILURE,
                UNKNOWN,
            };
            
            //Delegate
            class Delegate {
            public:
                virtual void onError(const TransportProtocol* transport, ErrorCode& error) = 0;
                virtual void onMessage(const TransportProtocol* transport, Data& data) = 0;
                virtual void onClose(const TransportProtocol* transport) = 0;
                virtual void onReconnect(const TransportProtocol* transport) = 0;
                virtual void onOpen(const TransportProtocol* transport) = 0;
            };
        public:
            Delegate* delegate;
            virtual void send(const std::string& message) =0;
            virtual void close() =0;
            virtual void connect(const std::string& url) =0;
            virtual void reconnect() =0;
            virtual State getReadyState() =0;
        };
    }
}
#endif /* Transport_hpp */

