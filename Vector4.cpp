#include "Vector4.h"

#include <algorithm>

Vector4::Vector4(): vec({0, 0, 0, 0}) {}

Vector4::Vector4(double a, double b, double c, double d): vec({a, b, c, d}) {}

Vector4::Vector4(Vector4& other): vec({other[0], other[1], other[2], other[3]}) {}

Vector4& Vector4::operator=(Vector4& other) {
    if (this != &other) {
        Vector4 temp(other);
        std::swap(vec, other.vec);
    }
    return *this;
}

const double Vector4::operator[](int index) const {
    return vec[index];
}

