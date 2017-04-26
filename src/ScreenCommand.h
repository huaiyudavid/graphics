//
// Created by david on 4/25/17.
//

#ifndef GRAPHICS_SCREENCOMMAND_H
#define GRAPHICS_SCREENCOMMAND_H

#include "CLI.h"

class ScreenCommand : public Command {
public:
    ScreenCommand(double width, double height, CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~ScreenCommand() {};
private:
    double width, height;
    std::string name;
    CLI& cli;
};


#endif //GRAPHICS_SCREENCOMMAND_H
