//
// Created by david on 3/29/17.
//

#ifndef GRAPHICS_PUSHCOMMAND_H
#define GRAPHICS_PUSHCOMMAND_H

#include "Command.h"
#include "CLI.h"

class PushCommand : public Command {
public:
    PushCommand(CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~PushCommand() {}

private:
    std::string name;
    CLI& cli;
};


#endif //GRAPHICS_PUSHCOMMAND_H
