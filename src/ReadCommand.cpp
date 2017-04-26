#include <fstream>
#include <iostream>

#include "ReadCommand.h"

ReadCommand::ReadCommand(std::string& file, CLI& mainCLI): name("read"), filename(file), cli(mainCLI) {}

void ReadCommand::execute() {
    std::string line;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::cout << toString() << std::endl;
        while (std::getline(file, line))
        {
            if (cli.isCommand(line)) {
                Command* com = cli.parseCommand(line, true);
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