//
// Created by david on 1/26/17.
//


#include "DrawCommand.h"
#include <iostream>

DrawCommand::DrawCommand(std::vector<double>& p): name("draw"), params(p) {}

void DrawCommand::execute() const {
    std::cout << toString() << std::endl;
}

std::string DrawCommand::toString() const {
    std::string str = name + ' ';
    for (const double& p : params) {
        str += std::to_string(p) + ' ';
    }
    return str;
}
