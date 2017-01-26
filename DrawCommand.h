#ifndef GRAPHICS_DRAWCOMMAND_H
#define GRAPHICS_DRAWCOMMAND_H

#include <vector>

#include "Command.h"

/*
 * Represents the draw command.
 */
class DrawCommand : public Command {
public:
    DrawCommand(std::vector<double>& p);
    virtual void execute() const;
    virtual std::string toString() const;
    virtual ~DrawCommand() {};

private:
    std::string name;
    std::vector<double> params;
};

#endif //GRAPHICS_DRAWCOMMAND_H
