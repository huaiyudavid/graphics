#ifndef GRAPHICS_READCOMMAND_H
#define GRAPHICS_READCOMMAND_H

#include "Command.h"
#include "CLI.h"

/*
 * Represents the read command. Reads the file from filename and executes all command within
 * the file. Recursively executes.
 */
class ReadCommand : public Command {
public:
    ReadCommand(std::string& file, CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~ReadCommand() {}

private:
    std::string name;
    std::string filename;
    CLI& cli;
};

#endif //GRAPHICS_READCOMMAND_H
