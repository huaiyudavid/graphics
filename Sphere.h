//
// Created by david on 4/25/17.
//

#ifndef GRAPHICS_SPHERE_H
#define GRAPHICS_SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere(double radius, Vector3 center, Vector3 aColor, Vector3 rColor, Vector3 sColor);
    virtual double hit(Ray ray, double t0);
    virtual Vector3 normal(Ray ray, double t);
    virtual Vector3& getAColor();
    virtual Vector3& getRColor();
    virtual Vector3 getSColor();
    virtual bool specular();
    virtual ~Sphere();

private:
    double radius;
    Vector3 center;
    Vector3 aColor, rColor, sColor;
};


#endif //GRAPHICS_SPHERE_H
