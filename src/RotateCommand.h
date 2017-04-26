#ifndef GRAPHICS_ROTATECOMMAND_H
#define GRAPHICS_ROTATECOMMAND_H

#include "Command.h"
#include "CLI.h"

class RotateCommand : public Command {
public:
    RotateCommand(double tIn, double xIn, double yIn, double zIn, CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~RotateCommand() {}

private:
    std::string name;
    double theta;
    double x, y, z;
    CLI& cli;
};


#endif //GRAPHICS_ROTATECOMMAND_H
