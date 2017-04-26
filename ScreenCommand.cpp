#include "ScreenCommand.h"
#include "global.h"

ScreenCommand::ScreenCommand(double width, double height, CLI& mainCLI):
        width(width), height(height), name("screen"), cli(mainCLI) {}

void ScreenCommand::execute() {
    glutReshapeWindow((int)width, (int)height);
    cli.width = width;
    cli.height = height;
}

std::string ScreenCommand::toString() const {
    return name + ' ' + std::to_string(width) + ',' + std::to_string(height);
}