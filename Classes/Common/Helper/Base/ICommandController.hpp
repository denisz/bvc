//
//  ICommandController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#ifndef ICommandController_hpp
#define ICommandController_hpp

#include "stdafx.h"
#include "CommandRunner.hpp"

namespace game {
    class ICommandController: public common::CommandRunner::Delegate {
    private:
        common::CommandRunner* _commandRunner;
        virtual void processResponse(CommandRunner* runner, Response* response);
    protected:
        virtual bool init();
        virtual bool initWithCommandRunner(common::CommandRunner* commandRunner);        
    public:
        ICommandController();
        ~ICommandController();
        virtual CommandRunner::Handler* runCommandInBackground(common::RequestCommand &command);
        virtual void runCommand(common::RequestCommand &command);
        common::CommandRunner* commandRunner();
    };
}


#endif /* ICommandController_hpp */
