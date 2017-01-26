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
    CLI(): tokenizer(), prefix("") {}
    bool isCommand(std::string& line);
    // Only use if line is not a comment
    // Returns null if invalid command
    Command* parseCommand(std::string& line, bool inFile);
    void test() {}

private:
    void tolower(std::string& token);

    // Fields

    // Used to parse input strings
    Tokenizer tokenizer;

    // Path to append to filenames within directories
    // Allows for file reading in other directories
    std::string prefix;
};

#endif //GRAPHICS_CLI_H