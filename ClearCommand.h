#ifndef GRAPHICS_CLEARCOMMAND_H
#define GRAPHICS_CLEARCOMMAND_H


#include "CLI.h"

class ClearCommand : public Command {
public:
    ClearCommand(CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~ClearCommand() {};
private:
    std::string name;
    CLI& cli;
};


#endif //GRAPHICS_CLEARCOMMAND_H
