
#ifndef FILTER_H
#define FILTER_H

#include <string>

class Filter {
public:
    Filter();
    size_t getWidth();
    std::string& getBorder();
    std::string& getType();
    double getValue(double x);
    void setWidth(size_t w);
    void setBorder(std::string& b);
    void setType(std::string& newType);

private:
    std::string type;
    std::string border;
    size_t width;

    double sinc(double x);
};

#endif //FILTER_H
