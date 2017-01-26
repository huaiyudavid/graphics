//
// Created by david on 1/26/17.
//

#ifndef GRAPHICS_TOKENIZER_H
#define GRAPHICS_TOKENIZER_H

#include <vector>
#include <string>

/*
 * Tokenizer splits string inputs into tokens.
 */
class Tokenizer {
public:
    /*
     * method: tokenize
     * params: line - string to tokenize
     *          delims - string of individual delimiting characters
     * details: each token is separated by exactly 1 delimiting character. A single trailing
     *          delimiting character is allowed at the end of the line.
     * return: vector of tokens represented as strings
     */
    std::vector<std::string> tokenize(std::string& line, const std::string& delims);
};

#endif //GRAPHICS_TOKENIZER_H
