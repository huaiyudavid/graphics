//
// Created by david on 1/26/17.
//

#ifndef GRAPHICS_READCOMMAND_H
#define GRAPHICS_READCOMMAND_H

#include "Command.h"
#include "CLI.h"

class ReadCommand : public Command {
public:
    ReadCommand(std::string& file, CLI& mainCLI);
    virtual void execute() const;
    virtual std::string toString() const;
    virtual ~ReadCommand() {}

private:
    std::string name;
    std::string filename;
    CLI& cli;
};

#endif //GRAPHICS_READCOMMAND_H