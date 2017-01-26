//
// Created by david on 1/26/17.
//

#ifndef GRAPHICS_COLORCOMMAND_H
#define GRAPHICS_COLORCOMMAND_H

#include <vector>

#include "Command.h"

class ColorCommand : public Command {
public:
    ColorCommand(std::vector<double>& p);
    virtual void execute() const;
    virtual std::string toString() const;
    virtual ~ColorCommand() {};

private:
    std::string name;
    std::vector<double> params;
};

#endif //GRAPHICS_COLORCOMMAND_H
