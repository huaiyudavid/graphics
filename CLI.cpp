//
// Created by david on 1/26/17.
//

#include <vector>
#include <cctype>
#include <iostream>

#include "CLI.h"
#include "MoveCommand.h"
#include "DrawCommand.h"
#include "ColorCommand.h"
#include "ReadCommand.h"

bool CLI::isCommand(std::string& line) {
    return line.length() > 0 && line[0] != '#';
}

Command* CLI::parseCommand(std::string& line, bool inFile) {
    std::vector<std::string> tokens = tokenizer.tokenize(line, ", \t");
    std::string name = tokens[0];
    tolower(name);
    if (name != "move" && name != "draw" && name != "color" && name != "read") {
        std::cout << "Error: command " << name << " not found in line \"" << line << "\"" << std::endl;
        return nullptr;
    }
    if (name == "move" || name == "draw" || name == "color") {
        std::vector<double> params;
        for (size_t i = 1; i < 4; ++i) {
            double num = 0;
            if (i < tokens.size()) {
                std::string token = tokens[i];
                if (token != "") {
                    try {
                        num = std::stod(token);
                    } catch (const std::invalid_argument &e) {
                        std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\"" << std::endl;
                        return nullptr;
                    } catch (const std::out_of_range &e) {
                        std::cout << "Error: parameter " << token << " out of range in line \"" << line << "\""
                                  << std::endl;
                        return nullptr;
                    }
                }
            }
            params.push_back(num);
        }
        if (tokens.size() > 4) {
            std::cout << "Warning: too many parameters, parameters were truncated" << std::endl;
            std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
        }

        if (name == "move") {
            return new MoveCommand(params);
        } else if (name == "draw") {
            return new DrawCommand(params);
        } else {    // color
            return new ColorCommand(params);
        }
    } else if (name == "read"){
        if (tokens.size() > 1) {
            std::string filename = tokens[1];
            if (tokens.size() > 2) {
                std::cout << "Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }
            if (inFile) {
                filename = prefix + filename;
            } else {
                prefix = filename.substr(0, filename.find_last_of("/") + 1);;
            }
            return new ReadCommand(filename, *this);
        } else {
            std::cout << "Error: Please provide a filename in line \"" << line << "\"" << std::endl;
            return nullptr;
        }
    }

    return nullptr;
}

void CLI::tolower(std::string& token) {
    for (char& c : token) {
        c = std::tolower(c);
    }
}
