
#include "Filter.h"

#include <cmath>

Filter::Filter(): type("lanczos"), border("zero"), width(2) {}

size_t Filter::getWidth() {
    return width;
}

std::string& Filter::getBorder() {
    return border;
}

std::string& Filter::getType() {
    return type;
}

double Filter::getValue(double x) {
    if (type == "lanczos") {
        return abs(x) < width ? sinc(x)*sinc(x/width) : 0;
    }

    return 0;
}

void Filter::setWidth(size_t w) {
    width = w;
}

void Filter::setBorder(std::string &b) {
    border = b;
}

void Filter::setType(std::string& newType) {
    type = newType;
}

double Filter::sinc(double x) {
    double param = M_PI*x;
    return fabs(param) < 0.000001 ? 1 : sin(param)/(param);
}

