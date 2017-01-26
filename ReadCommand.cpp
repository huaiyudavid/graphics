//
// Created by david on 1/26/17.
//

#include <fstream>
#include <iostream>

#include "ReadCommand.h"

ReadCommand::ReadCommand(std::string& file, CLI& mainCLI): name("read"), filename(file), cli(mainCLI) {}

void ReadCommand::execute() const {
    std::string line;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::cout << toString() << std::endl;
        while (std::getline(file, line))
        {
            if (cli.isCommand(line)) {
                Command* com = cli.parseCommand(line);
                if (com != nullptr) {
                    com->execute();
                }
                delete com;
            }
        }
        file.close();
        std::cout << "finished reading \"" << filename << "\"" << std::endl;
    }
    else {
        std::cout << "Error: invalid file name \"" << filename << "\"" << std::endl;
    }
}

std::string ReadCommand::toString() const {
    return name + " \"" + filename + "\"";
}