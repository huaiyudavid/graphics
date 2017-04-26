
#ifndef RESIZECOMMAND_H
#define RESIZECOMMAND_H

#include <vector>

#include "Command.h"
#include "CLI.h"

class ResizeCommand : public Command {
public:
    ResizeCommand(std::vector<double>& p, CLI& mainCLI);
    ResizeCommand(double scale, CLI& mainCLI);
    virtual void execute();
    virtual std::string toString() const;
    virtual ~ResizeCommand() {}

private:
    std::string name;
    double xscale, yscale;
    CLI& cli;

    // gets the value of the sample image at the given position
    uint16_t sample(int row, int col, uint8_t rgb);

    void resizeX();
    void resizeY();

    void invertX();
    void invertY();

    void findPixelsInRange(double targetPoint, double factor, double sourceWidth, double targetWidth, bool magnify, std::vector<int>& pixels, std::vector<double>& positions);
};

#endif //GRAPHICS_RESIZECOMMAND_H
