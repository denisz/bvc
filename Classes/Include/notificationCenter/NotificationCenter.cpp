#include "NotificationCenter.h"

std::map<int, void (*)(BaseObserverProtocol*)> NotificationCenter::unsubscribeMap;
