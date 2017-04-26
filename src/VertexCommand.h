#ifndef GRAPHICS_VERTEXCOMMAND_H
#define GRAPHICS_VERTEXCOMMAND_H

#include "Command.h"
#include "CLI.h"
#include "Vector4.h"

class VertexCommand : public Command {
public:
    VertexCommand(float xIn, float yIn, float zIn, CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~VertexCommand() {}

private:
    std::string name;
    float x, y, z;

    CLI& cli;
};


#endif //GRAPHICS_VERTEXCOMMAND_H
