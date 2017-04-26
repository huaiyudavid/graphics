#ifndef GRAPHICS_POPCOMMAND_H
#define GRAPHICS_POPCOMMAND_H


#include "Command.h"
#include "CLI.h"

class PopCommand : public Command {
public:
    PopCommand(CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~PopCommand() {}

private:
    std::string name;
    CLI& cli;
};


#endif //GRAPHICS_POPCOMMAND_H
