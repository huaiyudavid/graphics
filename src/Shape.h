#ifndef GRAPHICS_SHAPE_H
#define GRAPHICS_SHAPE_H

#include "Ray.h"

class Shape {
public:
    // returns negative if no hit, t value otherwise
    virtual double hit(Ray ray, double t0) = 0;
    virtual Vector3 normal(Ray ray, double t) = 0;
    virtual Vector3& getAColor() = 0;
    virtual Vector3& getRColor() = 0;
    virtual Vector3 getSColor() = 0;
    virtual bool specular() = 0;
    virtual ~Shape() {};
};


#endif //GRAPHICS_SHAPE_H
