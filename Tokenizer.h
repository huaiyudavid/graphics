//
// Created by david on 1/26/17.
//

#ifndef GRAPHICS_TOKENIZER_H
#define GRAPHICS_TOKENIZER_H

#include <vector>
#include <string>

class Tokenizer {
public:
   std::vector<std::string> tokenize(std::string& line, const std::string& delims);
};

#endif //GRAPHICS_TOKENIZER_H
