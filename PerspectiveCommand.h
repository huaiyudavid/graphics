//
// Created by david on 3/29/17.
//

#ifndef GRAPHICS_PERSPECTIVECOMMAND_H
#define GRAPHICS_PERSPECTIVECOMMAND_H

#include "Command.h"
#include "CLI.h"

class PerspectiveCommand : public Command {
public:
    PerspectiveCommand(double angle, double r, double near, double far, CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~PerspectiveCommand() {}

private:
    std::string name;
    double theta, ratio;
    double n, f;
    CLI& cli;
};


#endif //GRAPHICS_PERSPECTIVECOMMAND_H
