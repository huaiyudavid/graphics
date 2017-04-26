//
// Created by david on 4/25/17.
//

#ifndef GRAPHICS_TRACECOMMAND_H
#define GRAPHICS_TRACECOMMAND_H


#include "CLI.h"

class TraceCommand : public Command {
public:
    TraceCommand(CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~TraceCommand() {};
private:

    Vector3 reflection(Ray direction, int depth);

    std::string name;
    CLI& cli;
    double eps;
};


#endif //GRAPHICS_TRACECOMMAND_H
