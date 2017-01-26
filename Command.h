#ifndef GRAPHICS_COMMAND_H
#define GRAPHICS_COMMAND_H

#include <string>

/*
 * Command abstract class, represents all possible commands.
 */
class Command {
public:
    /*
     * method: execute
     * details: performs the job of the command
     */
    virtual void execute() const;

    /*
     * method: toString
     * return: string representation of this command
     */
    virtual std::string toString() const;

    virtual ~Command() {};
};

#endif //GRAPHICS_COMMAND_H
