//
// Created by david on 1/26/17.
//

#include "MoveCommand.h"
#include <iostream>

MoveCommand::MoveCommand(std::vector<double>& p): name("move"), params(p) {}

void MoveCommand::execute() const {
    std::cout << toString() << std::endl;
}

std::string MoveCommand::toString() const {
    std::string str = name + ' ';
    for (const double& p : params) {
        str += std::to_string(p) + ' ';
    }
    return str;
}

