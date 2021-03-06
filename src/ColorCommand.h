#ifndef GRAPHICS_COLORCOMMAND_H
#define GRAPHICS_COLORCOMMAND_H

#include <vector>

#include "Command.h"

/*
 * Represents the color command.
 */
class ColorCommand : public Command {
public:
    ColorCommand(std::vector<double>& p);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~ColorCommand() {};

private:
    std::string name;
    std::vector<double> params;
};

#endif //GRAPHICS_COLORCOMMAND_H
