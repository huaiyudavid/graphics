
#ifndef GRAPHICS_VECTOR3_H
#define GRAPHICS_VECTOR3_H

class Vector3 {
public:
    Vector3();
    Vector3(double a, double b, double c);
    Vector3(const Vector3& other);

    Vector3& operator=(const Vector3& other);

    const double operator[](int index) const;
    double& operator[](int index);

    Vector3 cross(const Vector3& other) const;
    Vector3 unit() const;

private:
    double vec[3];
};

#endif //GRAPHICS_VECTOR3_H
