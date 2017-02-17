#include <vector>
#include <cctype>
#include <iostream>

#include "CLI.h"
#include "MoveCommand.h"
#include "DrawCommand.h"
#include "ColorCommand.h"
#include "ReadCommand.h"
#include "TiffStatCommand.h"
#include "TiffReadCommand.h"
#include "TiffWriteCommand.h"

bool CLI::isCommand(std::string& line) {
    return line.length() > 0 && line[0] != '#';
}

Command* CLI::parseCommand(std::string& line, bool inFile) {
    std::string commands[] = {"move", "draw", "color", "read", "tiffread", "tiffstat", "tiffwrite"};
    std::vector<std::string> tokens = tokenizer.tokenize(line, ", \t");
    std::string name = tokens[0];
    tolower(name);
    bool invalidCommand = true;
    for (const std::string& command : commands) {
        if (name == command) {
            invalidCommand = false;
            break;
        }
    }
    if (invalidCommand) {
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
        if (totalReads >= MAX_READS) {
            std::cout << "Maximum number of reads exceeded (" << MAX_READS << ")" << std::endl;
            std::cout << "Please check for infinite recursion among files" << std::endl;
            return nullptr;
        }

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
            totalReads++;
            return new ReadCommand(filename, *this);
        } else {
            std::cout << "Error: Please provide a filename in line \"" << line << "\"" << std::endl;
            return nullptr;
        }
    } else if (name == "tiffstat" || name == "tiffread") {
        if (tokens.size() > 1) {
            std::string filename = tokens[1];
            if (tokens.size() > 2) {
                std::cout << "Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }
            if (inFile) {
                filename = prefix + filename;
            }
            if (name == "tiffstat") {
                return new TiffStatCommand(filename);
            } else {
                return new TiffReadCommand(filename, *this);
            }
        } else {
            std::cout << "Error: Please provide a filename in line \"" << line << "\"" << std::endl;
            return nullptr;
        }
    } else if (name == "tiffwrite") {
        if (tokens.size() > 5) {
            std::string filename = tokens[1];
            if (inFile) {
                filename = prefix + filename;
            }
            if (tokens.size() > 6) {
                std::cout << "Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<double> params;
            double x0, y0, xc, yc;

            try {
                x0 = std::stod(tokens[2]);
            } catch (const std::invalid_argument &e) {
                std::cout << "Error: invalid parameter " << tokens[2] << " in line \"" << line << "\"" << std::endl;
                return nullptr;
            } catch (const std::out_of_range &e) {
                std::cout << "Error: parameter " << tokens[2] << " out of range in line \"" << line << "\""
                          << std::endl;
                return nullptr;
            }
            try {
                y0 = std::stod(tokens[3]);
            } catch (const std::invalid_argument &e) {
                std::cout << "Error: invalid parameter " << tokens[3] << " in line \"" << line << "\"" << std::endl;
                return nullptr;
            } catch (const std::out_of_range &e) {
                std::cout << "Error: parameter " << tokens[3] << " out of range in line \"" << line << "\""
                          << std::endl;
                return nullptr;
            }
            try {
                xc = std::stod(tokens[4]);
            } catch (const std::invalid_argument &e) {
                std::cout << "Error: invalid parameter " << tokens[4] << " in line \"" << line << "\"" << std::endl;
                return nullptr;
            } catch (const std::out_of_range &e) {
                std::cout << "Error: parameter " << tokens[4] << " out of range in line \"" << line << "\""
                          << std::endl;
                return nullptr;
            }
            try {
                yc = std::stod(tokens[5]);
            } catch (const std::invalid_argument &e) {
                std::cout << "Error: invalid parameter " << tokens[5] << " in line \"" << line << "\"" << std::endl;
                return nullptr;
            } catch (const std::out_of_range &e) {
                std::cout << "Error: parameter " << tokens[5] << " out of range in line \"" << line << "\""
                          << std::endl;
                return nullptr;
            }

            if (x0 > xc) {
                std::cout << "Error: requires xc >= x0" << std::endl;
                return nullptr;
            } else if (y0 > yc) {
                std::cout << "Error: requires yc >= y0" << std::endl;
                return nullptr;
            }

            params.push_back(x0);
            params.push_back(y0);
            params.push_back(xc);
            params.push_back(yc);
            return new TiffWriteCommand(filename, params, *this);
        } else {
            std::cout << "Error: Not enough parameters for tiffwrite, please provide [filename, x0, y0, xc, yc]" << std::endl;
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
