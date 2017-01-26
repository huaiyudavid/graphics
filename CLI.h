//
// Created by david on 1/26/17.
//

#ifndef GRAPHICS_CLI_H
#define GRAPHICS_CLI_H

#include <string>

#include "Command.h"
#include "Tokenizer.h"

class CLI {
public:
    bool isCommand(std::string& line);
    // Only use if line is not a comment
    // Returns null if invalid command
    Command* parseCommand(std::string& line);
    void test() {}

private:
    void tolower(std::string& token);

    // Fields
    Tokenizer tokenizer;
};

#endif //GRAPHICS_CLI_H