//
// Created by david on 4/25/17.
//

#ifndef GRAPHICS_BOX_H
#define GRAPHICS_BOX_H

#include "Shape.h"

class Box : public Shape {
public:
    Box(Vector3 lowerLeft, Vector3 topRight, Vector3 aColor, Vector3 rColor);
    virtual double hit(Ray ray, double t0);
    virtual Vector3 normal(Ray ray, double t);
    virtual Vector3& getAColor();
    virtual Vector3& getRColor();
    virtual Vector3 getSColor();
    virtual bool specular();
    virtual ~Box() {};

private:
    Vector3 lowerLeft, topRight, aColor, rColor;

    bool isBetweenInclusive(double a, double b, double x);

    bool isBetweenExclusive(double a, double b, double x);
};


#endif //GRAPHICS_BOX_H
