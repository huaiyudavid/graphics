//
// Created by david on 1/26/17.
//

#ifndef GRAPHICS_CLI_H
#define GRAPHICS_CLI_H

#include <string>

#include "Command.h"
#include "Tokenizer.h"
/*
 * CLI acts as the main interpreter of commands, converting strings to Command objects
 */
class CLI {
public:
    // Constructor
    CLI(): tokenizer(), prefix("") {}

    /*
     * method: isCommand
     * return: whether line begins with a comment character
     */
    bool isCommand(std::string& line);

    /*
     * method: parseCommand
     * pre: line does not begin with a comment
     * return: nullptr if invalid command
     */
    Command* parseCommand(std::string& line, bool inFile);

private:
    /*
     * method: tolower
     * post: token is modified
     * returns: token in lower case
     */
    void tolower(std::string& token);

    // Fields

    // Used to parse input strings
    Tokenizer tokenizer;

    // Path to append to filenames within directories
    // Allows for file reading in other directories
    std::string prefix;
};

#endif //GRAPHICS_CLI_H