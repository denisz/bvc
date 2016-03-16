//
//  NetworkClient.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "NetworkClient.hpp"

using namespace internal::network;

NetworkClient::NetworkClient()
:_transport(nullptr)
, _parser(nullptr) {
    _parser = new Parser();
}

NetworkClient::~NetworkClient() {
    CC_SAFE_DELETE(_parser);
    CC_SAFE_RELEASE_NULL(_transport);
}


NetworkClient* NetworkClient::createWithTransport(TransportProtocol* transport) {
    auto client = new NetworkClient();
    if (client->initWithTransport(transport)) {
        return client;
    }
    
    CC_SAFE_DELETE(client);
    return nullptr;
}

bool NetworkClient::initWithTransport(TransportProtocol* transport) {
    _transport = transport;
    _transport->delegate = this;
    CC_SAFE_RETAIN(_transport);
    return true;
}

void NetworkClient::connect(const std::string &url) {
    if (_transport != nullptr) {
        _transport->connect(url);
    }
}

void NetworkClient::close() {
    if (_transport != nullptr) {
        _transport->close();
    }
}
void NetworkClient::reconnect() {
    if (_transport != nullptr) {
        _transport->reconnect();
    }
}

Response* NetworkClient::tryCreateSuccesfullResponse(TransportProtocol::Data& data) {
    auto doc = _parser->parse(data.bytes);
    return Response::createWithDocument(doc);
}

Response* NetworkClient::tryCreateErrorResponse(TransportProtocol::ErrorCode &error) {
    auto doc = new rapidjson::Document();
    SetValueByPointer(*doc, "/command", "error");
    //    SetValueByPointer(doc, "/params/errorCode",  error);

    return Response::createWithDocument(doc);
}

void NetworkClient::sendMessage(const std::string &message) {
    if (_transport != nullptr) {
        _transport->send(message);
    }
}

void NetworkClient::sendMessage(Request &req) {
    auto message = req.outReadyMessage();
    return sendMessage(message);
}

//MARK
void NetworkClient::onError(const TransportProtocol *transport, TransportProtocol::ErrorCode &error) {
    auto res = tryCreateErrorResponse(error);
    if (res != nullptr) {
        res->source = Response::Source::NETWORKCLIENT;
        NotificationCenter::notify(&NetworkClient::Events::onError, res);
        CC_SAFE_RELEASE(res);
    }
}

void NetworkClient::onMessage(const TransportProtocol *transport, TransportProtocol::Data &data) {
    auto res = tryCreateSuccesfullResponse(data);
    if (res != nullptr) {
        res->source = Response::Source::NETWORKCLIENT;
        NotificationCenter::notify(&NetworkClient::Events::onReceivedMessage, res);
        CC_SAFE_RELEASE(res);
    }
}

void NetworkClient::onClose(const TransportProtocol *transport) {
    NotificationCenter::notify(&NetworkClient::Events::onClose);
}

void NetworkClient::onOpen(const TransportProtocol *transport) {
    NotificationCenter::notify(&NetworkClient::Events::onOpen);
}

void NetworkClient::onReconnect(const TransportProtocol *transport) {
    NotificationCenter::notify(&NetworkClient::Events::onReconnect);
}

bool NetworkClient::isOpenConnect() {
    if (_transport != nullptr) {
        return  _transport->getReadyState() == TransportProtocol::State::OPEN;
    }
    return false;
}