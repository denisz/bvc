#include "BaseObserverProtocol.h"
#include "NotificationCenter.h"

BaseObserverProtocol::BaseObserverProtocol() {
    static unsigned int observersCount = 0;
    observerId = ++observersCount;
}

BaseObserverProtocol::~BaseObserverProtocol() {
    NotificationCenter::unsubscribe(this);
}