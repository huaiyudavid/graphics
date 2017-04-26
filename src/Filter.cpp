
#include "Filter.h"

#include <cmath>
#include <iostream>

Filter::Filter(): type("lanczos"), border("zero"), width(2) {}

double Filter::getWidth() {
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
        return fabs(x) < width ? sinc(x)*sinc(x/width) : 0;
    } else if (type == "gaussian") {
        return fabs(x) < width ? 1/sqrt(2*M_PI)*exp(-x*x/2) : 0;
    } else if (type == "mitchell") {
        double part = 0;
        if (fabs(x) <= 1) {
            part = -21*pow(1-fabs(x), 3) + 27*pow(1-fabs(x), 2) + 9*(1-fabs(x)) + 1;
        } else if (fabs(x) >= 1 && fabs(x) <= 2) {
            part = 7*pow(2-fabs(x), 3) - 6*pow(2-fabs(x), 2);
        }
        return part/18;
    } else if (type == "hamming") {
        return fabs(x) < 2 ? .54 + .46*cos(2*M_PI*x/4) : 0;
    } else if (type == "bsplcubic") {
        double part = 0;
        if (fabs(x) <= 1) {
            part = -3*pow(1-fabs(x), 3) + 3*pow(1-fabs(x), 2) + 3*(1-fabs(x)) + 1;
        } else if (fabs(x) >= 1 && fabs(x) <= 2) {
            part = pow(2-fabs(x), 3);
        }
        return part/6;
    } else if (type == "catmullrom") {
        double part = 0;
        if (fabs(x) <= 1) {
            part = -3*pow(1-fabs(x), 3) + 4*pow(1-fabs(x), 2) + (1-fabs(x));
        } else if (fabs(x) >= 1 && fabs(x) <= 2) {
            part = pow(2-fabs(x), 3) - pow(2-fabs(x), 2);
        }
        return part/2;
    } else if (type == "tent") {
        return fabs(x) < width ? (1-fabs(x/width))/width : 0;
    } else if (type == "box") {
        return fabs(x) <= width ? 1/(2*width+1) : 0;
    }

    return 0;
}

void Filter::setWidth(double w) {
    width = w;
}

void Filter::setBorder(std::string &b) {
    border = b;
}

void Filter::setType(std::string& newType) {
    type = newType;
    if (type == "mitchell" || type == "hamming" || type == "bsplcubic" || type == "catmullrom") {
        width = 2;
        std::cout << "Filter width set to 2" << std::endl;
    }
}

double Filter::sinc(double x) {
    double param = M_PI*x;
    return fabs(param) < 0.000001 ? 1 : sin(param)/(param);
}

