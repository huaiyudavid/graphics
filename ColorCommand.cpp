#include "ColorCommand.h"
#include <iostream>

ColorCommand::ColorCommand(std::vector<double>& p): name("color"), params(p) {}

void ColorCommand::execute() const {
    std::cout << toString() << std::endl;
}

std::string ColorCommand::toString() const {
    std::string str = name + ' ';
    for (const double& p : params) {
        str += std::to_string(p) + ' ';
    }
    return str;
}

