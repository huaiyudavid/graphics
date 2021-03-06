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
#include "ResizeCommand.h"
#include "PushCommand.h"
#include "PopCommand.h"
#include "TranslateCommand.h"
#include "ScaleCommand.h"
#include "RotateCommand.h"
#include "OrthoCommand.h"
#include "PerspectiveCommand.h"
#include "LookatCommand.h"
#include "VertexCommand.h"
#include "ResetCommand.h"
#include "ScreenCommand.h"
#include "ClearCommand.h"
#include "TraceCommand.h"
#include "OrthoCamera.h"
#include "PerspCamera.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Box.h"
#include "Light.h"

bool CLI::isCommand(std::string& line) {
    return line.length() > 0 && line[0] != '#';
}

Command* CLI::parseCommand(std::string& line, bool inFile) {
    std::string commands[] = {"move", "draw", "color", "read",
                              "tiffread", "tiffstat", "tiffwrite", "resize", "zoom", "border", "select",
                              "push", "pop", "translate", "scale", "rotate", "ortho", "perspective", "lookat", "vertex", "reset",
                              "screen", "orthocamera", "camera", "background", "sphere", "triangle", "box", "ilight", "clear", "trace"};
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
            std::cout << "1Warning: too many parameters, parameters were truncated" << std::endl;
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
                std::cout << "2Warning: too many parameters, parameters were truncated" << std::endl;
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
                std::cout << "3Warning: too many parameters, parameters were truncated" << std::endl;
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
                std::cout << "4Warning: too many parameters, parameters were truncated" << std::endl;
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
    } else if (name == "resize") {
        std::vector<double> params;
        for (size_t i = 1; i < 3; ++i) {
            double num = 1;
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
        if (tokens.size() > 3) {
            std::cout << "5Warning: too many parameters, parameters were truncated" << std::endl;
            std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
        }

        return new ResizeCommand(params, *this);
    } else if (name == "zoom") {
        if (tokens.size() > 1) {
            std::string token = tokens[1];
            double num = 1;
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
            if (tokens.size() > 2) {
                std::cout << "6Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            return new ResizeCommand(num, *this);
        } else {
            std::cout << "Error: Please provide a scale in line \"" << line << "\"" << std::endl;
            return nullptr;
        }
    } else if (name == "border") {
        if (tokens.size() > 1) {
            std::string borderType = tokens[1];
            tolower(borderType);
            if (tokens.size() > 2) {
                std::cout << "7Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }
            std::string borderTypes[] = {"zero", "freeze", "circular"};
            bool invalidBorder = true;
            for (const std::string& type : borderTypes) {
                if (borderType == type) {
                    invalidBorder = false;
                    break;
                }
            }
            if (invalidBorder) {
                std::cout << "Error: Please give a valid border type in line \"" << line << "\"" << std::endl;
                std::cout << "Valid border types:" << std::endl;
                for (const std::string& type : borderTypes) {
                    std::cout << type << std::endl;
                }
                return nullptr;
            }
            filter.setBorder(borderType);
            std::cout << "Border type set to " << borderType << std::endl;
        } else {
            std::cout << "Error: Please provide a border type in line \"" << line << "\"" << std::endl;
            return nullptr;
        }
    } else if (name == "select") {
        if (tokens.size() > 1) {
            std::string filterType = tokens[1];
            tolower(filterType);
            std::string filterTypes[] = {"lanczos", "gaussian", "mitchell", "hamming", "bsplcubic", "catmullrom", "tent", "box"};
            bool invalidFilter = true;
            for (const std::string& type : filterTypes) {
                if (filterType == type) {
                    invalidFilter = false;
                    break;
                }
            }
            if (invalidFilter) {
                std::cout << "Error: Please give a valid filter type in line \"" << line << "\"" << std::endl;
                std::cout << "Valid filter types:" << std::endl;
                for (const std::string& type : filterTypes) {
                    std::cout << type << std::endl;
                }
                return nullptr;
            }
            if (tokens.size() > 2) {
                if (filterType == "gaussian" || filterType == "lanczos" || filterType == "tent" || filterType == "box") {
                    std::string token = tokens[2];
                    double width = 2;
                    try {
                        width = std::stod(token);
                    } catch (const std::invalid_argument &e) {
                        std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\"" << std::endl;
                        return nullptr;
                    } catch (const std::out_of_range &e) {
                        std::cout << "Error: parameter " << token << " out of range in line \"" << line << "\""
                                  << std::endl;
                        return nullptr;
                    }
                    if (width <= 0) {
                        std::cout << "Error: Filter width must be a positive number" << std::endl;
                        return nullptr;
                    }
                    if (tokens.size() > 3) {
                        std::cout << "8Warning: too many parameters, parameters were truncated" << std::endl;
                        std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
                    }
                    filter.setWidth(width);
                    std::cout << "Filter width set to " << width << std::endl;
                } else {
                    std::cout << "9Warning: too many parameters, parameters were truncated" << std::endl;
                    std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
                }
            }
            filter.setType(filterType);
            std::cout << "Filter type set to " << filterType << std::endl;
        } else {
            std::cout << "Error: Please provide a filter type in line \"" << line << "\"" << std::endl;
            return nullptr;
        }
    } else if (name == "push" || name == "pop" || name == "reset") {
        if (name == "push") {
            return new PushCommand(*this);
        } else if (name == "pop") {
            return new PopCommand(*this);
        } else if (name == "reset") {
            return new ResetCommand(*this);
        }
    } else if (name == "translate" || name == "scale" || name == "vertex") {
        if (tokens.size() > 3) {
            if (tokens.size() > 4) {
                std::cout << "10Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

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

            if (name == "translate") {
                return new TranslateCommand(params[0], params[1], params[2], *this);
            } else if (name == "scale") {
                return new ScaleCommand(params[0], params[1], params[2], *this);
            } else {
                return new VertexCommand((float)params[0], (float)params[1], (float)params[2], *this);
            }
        } else {
            std::cout << "Error: Not enough parameters, please provide [x, y, z]" << std::endl;
            return nullptr;
        }
    } else if (name == "rotate") {
        if (tokens.size() > 4) {
            if (tokens.size() > 5) {
                std::cout << "11Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<double> params;

            for (size_t i = 1; i < 5; ++i) {
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

            return new RotateCommand(params[0], params[1], params[2], params[3], *this);
        } else {
            std::cout << "Error: Not enough parameters, please provide [theta, x, y, z]" << std::endl;
            return nullptr;
        }
    } else if (name == "ortho") {
        if (tokens.size() > 6) {
            if (tokens.size() > 7) {
                std::cout << "12Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<double> params;

            for (size_t i = 1; i < 7; ++i) {
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

            return new OrthoCommand(params[0], params[1], params[2], params[3], params[4], params[5], *this);
        } else {
            std::cout << "Error: Not enough parameters, please provide [l, r, b, t, n, f]" << std::endl;
            return nullptr;
        }
    } else if (name == "perspective") {
        if (tokens.size() > 4) {
            if (tokens.size() > 5) {
                std::cout << "13Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<double> params;

            for (size_t i = 1; i < 5; ++i) {
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

            return new PerspectiveCommand(params[0], params[1], params[2], params[3], *this);
        } else {
            std::cout << "Error: Not enough parameters, please provide [f, a, n, f]" << std::endl;
            return nullptr;
        }
    } else if (name == "lookat") {
        if (tokens.size() > 9) {
            if (tokens.size() > 10) {
                std::cout << "14Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<float> params;

            for (size_t i = 1; i < 10; ++i) {
                float num = 0;
                if (i < tokens.size()) {
                    std::string token = tokens[i];
                    if (token != "") {
                        try {
                            num = std::stof(token);
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

            return new LookatCommand(params[0], params[1], params[2],
                                          params[3], params[4], params[5],
                                          params[6], params[7], params[8], *this);
        } else {
            std::cout << "Error: Not enough parameters, please provide [f, a, n, f]" << std::endl;
            return nullptr;
        }
    } else if (name == "screen") {
        if (tokens.size() > 2) {
            if (tokens.size() > 3) {
                std::cout << "15Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<float> params;

            for (size_t i = 1; i < 3; ++i) {
                float num = 0;
                if (i < tokens.size()) {
                    std::string token = tokens[i];
                    if (token != "") {
                        try {
                            num = std::stof(token);
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

            return new ScreenCommand(params[0], params[1], *this);
        }
    } else if (name == "orthocamera") {
        delete cam;
        cam = new OrthoCamera();
    } else if (name == "camera") {
        if (tokens.size() > 14) {
            if (tokens.size() > 15) {
                std::cout << "16Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<float> params;

            for (size_t i = 1; i < 15; ++i) {
                float num = 0;
                if (i < tokens.size()) {
                    std::string token = tokens[i];
                    if (token != "") {
                        try {
                            num = std::stof(token);
                        } catch (const std::invalid_argument &e) {
                            std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\""
                                      << std::endl;
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

            delete cam;
            cam = new PerspCamera(Vector3(params[0], params[1], params[2]),
                                    Vector3(params[3], params[4], params[5]),
                                    Vector3(params[6], params[7], params[8]),
                                    params[9], params[10], params[11], params[12], params[13], *this);
        }
    } else if (name == "background") {
        if (tokens.size() > 3) {
            if (tokens.size() > 4) {
                std::cout << "17Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<float> params;

            for (size_t i = 1; i < 4; ++i) {
                float num = 0;
                if (i < tokens.size()) {
                    std::string token = tokens[i];
                    if (token != "") {
                        try {
                            num = std::stof(token);
                            if (num > 1) {
                                std::cout << "Error: color out of range [0, 1]" << std::endl;
                                return nullptr;
                            }
                        } catch (const std::invalid_argument &e) {
                            std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\""
                                      << std::endl;
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

            background = Vector3(params[0], params[1], params[2]);
        }
    } else if (name == "sphere") {
        if (tokens.size() > 10) {
            if (tokens.size() > 14) {
                std::cout << "18Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<float> params;

            for (size_t i = 1; i < 11; ++i) {
                float num = 0;
                if (i < tokens.size()) {
                    std::string token = tokens[i];
                    if (token != "") {
                        try {
                            num = std::stof(token);
                        } catch (const std::invalid_argument &e) {
                            std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\""
                                      << std::endl;
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

            if (tokens.size() > 13) {
                for (size_t i = 11; i < 14; ++i) {
                    float num = 0;
                    if (i < tokens.size()) {
                        std::string token = tokens[i];
                        if (token != "") {
                            try {
                                num = std::stof(token);
                            } catch (const std::invalid_argument &e) {
                                std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\""
                                          << std::endl;
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
            } else {
                for (int i = 0; i < 3; ++i) {
                    params.push_back(0);
                }
            }

            shapes.push_back(new Sphere(params[0],
                                        Vector3(params[1], params[2], params[3]),
                                        Vector3(params[4], params[5], params[6]),
                                        Vector3(params[7], params[8], params[9]),
                                        Vector3(params[10], params[11], params[12])));
        }
    } else if (name == "triangle") {
        if (tokens.size() > 15) {
            if (tokens.size() > 16) {
                std::cout << "19Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<float> params;

            for (size_t i = 1; i < 16; ++i) {
                float num = 0;
                if (i < tokens.size()) {
                    std::string token = tokens[i];
                    if (token != "") {
                        try {
                            num = std::stof(token);
                        } catch (const std::invalid_argument &e) {
                            std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\""
                                      << std::endl;
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

            shapes.push_back(new Triangle(Vector3(params[0], params[1], params[2]),
                     Vector3(params[3], params[4], params[5]),
                     Vector3(params[6], params[7], params[8]),
                     Vector3(params[9], params[10], params[11]),
                     Vector3(params[12], params[13], params[14])));
        }
    } else if (name == "box") {
        if (tokens.size() > 12) {
            if (tokens.size() > 13) {
                std::cout << "20Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<float> params;

            for (size_t i = 1; i < 13; ++i) {
                float num = 0;
                if (i < tokens.size()) {
                    std::string token = tokens[i];
                    if (token != "") {
                        try {
                            num = std::stof(token);
                        } catch (const std::invalid_argument &e) {
                            std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\""
                                      << std::endl;
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

            shapes.push_back(new Box(Vector3(params[0], params[1], params[2]),
                                     Vector3(params[3], params[4], params[5]),
                                     Vector3(params[6], params[7], params[8]),
                                     Vector3(params[9], params[10], params[11])));
        }
    } else if (name == "ilight") {
        if (tokens.size() > 6) {
            if (tokens.size() > 7) {
                std::cout << "21Warning: too many parameters, parameters were truncated" << std::endl;
                std::cout << "(Be sure to only have 1 delimiting character between values)" << std::endl;
            }

            std::vector<float> params;

            for (size_t i = 1; i < 7; ++i) {
                float num = 0;
                if (i < tokens.size()) {
                    std::string token = tokens[i];
                    if (token != "") {
                        try {
                            num = std::stof(token);
                        } catch (const std::invalid_argument &e) {
                            std::cout << "Error: invalid parameter " << token << " in line \"" << line << "\""
                                      << std::endl;
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

            lights.push_back(Light(Vector3(params[0], params[1], params[2]),
                                   Vector3(params[3], params[4], params[5])));
        }
    } else if (name == "clear") {
        return new ClearCommand(*this);
    } else if (name == "trace") {
        return new TraceCommand(*this);
    }

    return nullptr;
}

void CLI::tolower(std::string& token) {
    for (char& c : token) {
        c = std::tolower(c);
    }
}

CLI::~CLI() {
    delete cam;
    for (auto shape : shapes) {
        delete shape;
    }
}
