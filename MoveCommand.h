//
// Created by david on 1/26/17.
//

#ifndef GRAPHICS_MOVECOMMAND_H
#define GRAPHICS_MOVECOMMAND_H

#include <vector>

#include "Command.h"

class MoveCommand : public Command {
public:
    MoveCommand(std::vector<double> p);
    virtual void execute() const;
    virtual std::string toString() const;
    virtual ~MoveCommand() {};

private:
    std::string name;
    std::vector<double> params;
};

#endif //GRAPHICS_MOVECOMMAND_H
