#include "Vector3.h"

#include <algorithm>

Vector3::Vector3(): vec({0, 0, 0, 0}) {}

Vector3::Vector3(double a, double b, double c): vec({a, b, c}) {}

Vector3::Vector3(Vector3& other): vec({other[0], other[1], other[2]}) {}

Vector3& Vector3::operator=(Vector3& other) {
    if (this != &other) {
        Vector3 temp(other);
        std::swap(vec, other.vec);
    }
    return *this;
}

const double Vector3::operator[](int index) const {
    return vec[index];
}

double& Vector3::operator[](int index) {
    return vec[index];
}

Vector3 Vector3::cross(Vector3& other) const {
    return Vector3(vec[1] * other.vec[2] - vec[2] * other.vec[1],
                    vec[2] * other.vec[0] - vec[0] * other.vec[2],
                    vec[0] * other.vec[1] - vec[1] * other.vec[0]);
}

Vector3 Vector3::unit() const {
    double length = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    return Vector3(vec[0]/length, vec[1]/length, vec[2]/length);
}
