//
// Created by david on 3/29/17.
//

#ifndef GRAPHICS_LOOKATCOMMAND_H
#define GRAPHICS_LOOKATCOMMAND_H

#include "Command.h"
#include "CLI.h"

class LookatCommand : public Command {
public:
    LookatCommand(float fX, float fY, float fZ, float atX, float atY, float atZ, float upX, float upY, float upZ, CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~LookatCommand() {}

private:
    std::string name;
    float fx, fy, fz;
    float atx, aty, atz;
    float upx, upy, upz;
    CLI& cli;
};


#endif //GRAPHICS_LOOKATCOMMAND_H
