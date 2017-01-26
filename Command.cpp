//
// Created by david on 1/26/17.
//

#include <iostream>

#include "Command.h"

void Command::execute() const {
    std::cout << "Command execute" << std::endl;
}

std::string Command::toString() const {
    return "Command";
}