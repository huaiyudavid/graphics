#include "ResetCommand.h"
#include "global.h"

#include <iostream>

ResetCommand::ResetCommand(CLI& mainCLI): name("reset"), cli(mainCLI) {}

void ResetCommand::execute() {
    std::cout << "clearning" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0,0);
    glFlush();

    cli.stack.clear();
    cli.currentMatrix = Matrix44();
}

std::string ResetCommand::toString() const {
    return name;
}