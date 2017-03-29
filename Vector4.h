#ifndef GRAPHICS_VECTOR4_H
#define GRAPHICS_VECTOR4_H

class Vector4 {
public:
    Vector4();
    Vector4(double a, double b, double c, double d);
    Vector4(Vector4& other);

    Vector4& operator=(Vector4& other);

    const double operator[](int index) const;

private:
    double vec[4];
};

#endif //GRAPHICS_VECTOR4_H
