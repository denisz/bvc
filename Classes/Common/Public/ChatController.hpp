//
//  ChatController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/16/16.
//
//

#ifndef ChatController_hpp
#define ChatController_hpp

#include "stdafx.h"
#include "DataSourceController.hpp"

using namespace common;

namespace game {
    class ChatController: public DataSourceController {
    public:
        enum class CHANNELS {PRIVATE, SYSTEM, PUBLIC, MERCHANT, HERALD, TOURNEY, CLANWARS};
    private:
        inline const char* toString(CHANNELS v)
        {
            switch (v)
            {
                case CHANNELS::PRIVATE:   return "PRIVATE";
                case CHANNELS::SYSTEM:    return "SYSTEM";
                case CHANNELS::PUBLIC:    return "PUBLIC";
                case CHANNELS::MERCHANT:  return "MERCHANT";
                case CHANNELS::HERALD:    return "HERALD";
                case CHANNELS::TOURNEY:   return "TOURNEY";
                case CHANNELS::CLANWARS:  return "CLANWARS";
                default:                  return "[Unknown CHANNELS]";
            }
        }
    public:
        CommandRunner::Handler* sendPublicMessageAsync(const std::string& message);
        CommandRunner::Handler* sendMessageAsync(CHANNELS channel, const std::string& message);
        CommandRunner::Handler* sendMessageAsync(CHANNELS channel, const std::string& to, const std::string& message);
        CommandRunner::Handler* sendP2PMessageAsync(const std::string& to, const std::string& message);
        virtual bool init();
        BV_CREATE_FUNC(ChatController);
    };
}


#endif /* ChatController_hpp */
