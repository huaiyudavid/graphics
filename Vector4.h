#ifndef GRAPHICS_VECTOR4_H
#define GRAPHICS_VECTOR4_H

#include <string>

class Vector4 {
public:
    Vector4();
    Vector4(double a, double b, double c, double d);
    Vector4(const Vector4& other);

    Vector4& operator=(const Vector4& other);

    double& operator[](int index);
    const double operator[](int index) const;

    std::string toString() const;

private:
    double vec[4];
};

#endif //GRAPHICS_VECTOR4_H
