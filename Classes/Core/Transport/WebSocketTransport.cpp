
//  WebSocketTransport.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "WebSocketTransport.hpp"

using namespace internal::network;

WebSocketTransport::WebSocketTransport()
: _url("")
, _isReconnect(false) {
    _readyState = internal::network::TransportProtocol::State::CONNECTING;
    _wsClient = new cocos2d::network::WebSocket();
}

bool WebSocketTransport::init() {
    return true;
}

WebSocketTransport::~WebSocketTransport() {
    CC_SAFE_DELETE(_wsClient);
}

WebSocketTransport* WebSocketTransport::create() {
    auto transport = new WebSocketTransport();
    if (transport->init()) {
        return transport;
    }
    
    CC_SAFE_DELETE(transport);
    return nullptr;
}

void WebSocketTransport::send(const std::string& message) {
    std::cout << std::endl << "<< Send message" << std::endl;
    std::cout << message << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    _wsClient->send(message);
}

std::string WebSocketTransport::protocol() {
    return "websocket";
}

TransportProtocol::State WebSocketTransport::getReadyState() {
    return _readyState;
}

void WebSocketTransport::close() {
    _wsClient->close();
    _readyState = TransportProtocol::State::CLOSING;
}

void WebSocketTransport::reconnect() {
    if (_readyState == TransportProtocol::State::CLOSING
        || _readyState == TransportProtocol::State::CLOSED) {
        _isReconnect = true;
        close();
    }
}

void WebSocketTransport::connect(const std::string& url) {
    _wsClient->init(*this, url);
    _url = url;
    _readyState = internal::network::TransportProtocol::State::CONNECTING;
}

//Implementation cocos2d websocket delegate
void WebSocketTransport::onOpen(cocos2d::network::WebSocket* ws) {
    std::cout << "Open websocket connection" << std::endl;
    
    if (delegate != nullptr) {
        _readyState = internal::network::TransportProtocol::State::OPEN;
        delegate->onOpen(this);
    }
}

void WebSocketTransport::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
    std::cout << std::endl << ">> Received message websocket" << std::endl;
    std::cout << data.bytes << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    
    if (delegate != nullptr) {
        auto _data = internal::network::TransportProtocol::Data();
        _data.isBinary = data.isBinary;
        _data.bytes = data.bytes;
        _data.len = data.len;
        _data.issued = data.issued;
        _data.time = std::time(nullptr);
        delegate->onMessage(this, _data);
    }
}

void WebSocketTransport::onClose(cocos2d::network::WebSocket* ws) {
    std::cout << "Close websocket connection " << std::endl;
    
    if (_isReconnect) {
        connect(_url);
        _isReconnect = false;
        if (delegate != nullptr) {
            delegate->onReconnect(this);
        }
    } else {
        _readyState = network::TransportProtocol::State::CLOSED;
        if (delegate != nullptr) {
            delegate->onClose(this);
        }
    }
}

void WebSocketTransport::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
    std::cout << "Error websocket" << std::endl;
    
    if (delegate != nullptr) {
        auto code = network::TransportProtocol::ErrorCode::UNKNOWN;
        
        if (error == cocos2d::network::WebSocket::ErrorCode::TIME_OUT) {
            code = network::TransportProtocol::ErrorCode::TIME_OUT;
        } else if (error == cocos2d::network::WebSocket::ErrorCode::CONNECTION_FAILURE) {
            code = network::TransportProtocol::ErrorCode::CONNECTION_FAILURE;
        }
        
        delegate->onError(this, code);
    }
}