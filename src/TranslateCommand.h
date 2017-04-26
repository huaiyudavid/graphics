
#ifndef GRAPHICS_TRANSLATECOMMAND_H
#define GRAPHICS_TRANSLATECOMMAND_H

#include "Command.h"
#include "CLI.h"

class TranslateCommand : public Command {
public:
    TranslateCommand(double xIn, double yIn, double zIn, CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~TranslateCommand() {}

private:
    std::string name;
    double x, y, z;
    CLI& cli;
};


#endif //GRAPHICS_TRANSLATECOMMAND_H
