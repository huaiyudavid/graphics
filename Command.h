//
// Created by david on 1/26/17.
//

#ifndef GRAPHICS_COMMAND_H
#define GRAPHICS_COMMAND_H

#include <string>

class Command {
public:
    virtual void execute() const;
    virtual std::string toString() const;
    virtual ~Command() {};
};

#endif //GRAPHICS_COMMAND_H
