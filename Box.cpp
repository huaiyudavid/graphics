#include "Box.h"

Box::Box(Vector3 lowerLeft, Vector3 topRight, Vector3 aColor, Vector3 rColor):
    lowerLeft(lowerLeft), topRight(topRight), aColor(aColor), rColor(rColor) {}

double Box::hit(Ray ray, double t0) {
    double tmin = (lowerLeft[0] - ray.start[0]) / ray.direction[0];
    double tmax = (topRight[0] - ray.start[0]) / ray.direction[0];

    if (tmin > tmax) std::swap(tmin, tmax);

    double tymin = (lowerLeft[1] - ray.start[1]) / ray.direction[1];
    double tymax = (topRight[1] - ray.start[1]) / ray.direction[1];

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    double tzmin = (lowerLeft[2] - ray.start[2]) / ray.direction[2];
    double tzmax = (topRight[2] - ray.start[2]) / ray.direction[2];

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return tmin > t0 ? tmin : -1;
}

Vector3 Box::normal(Ray ray, double t) {
    static const Vector3 normals[] = { // A cube has 3 possible orientations
            Vector3(1,0,0),
            Vector3(0,1,0),
            Vector3(0,0,1)
    };

    Vector3 inter = ray.start + ray.direction*t;
    Vector3 aabbCenter = (topRight - lowerLeft)*.5;

    const Vector3 interRelative = inter - aabbCenter;
    const double xyCoef = interRelative[1] / interRelative[0];
    const double zyCoef = interRelative[1] / interRelative[2];

    const int coef = (isBetweenInclusive(-1, 1, xyCoef) ? 1 :
                      (isBetweenExclusive(-1, 1, zyCoef) ? 2 : 0));
    // Here it's exclusive to avoid coef to be 3
    Vector3 tempNormal = normals[coef];
    for (int i = 0; i < 3; i++) {
        if (interRelative[i] < 0) {
            tempNormal[i] *= -1;
        }
    }
    return tempNormal; // The sign he is used to know direction of the normal
}

bool Box::isBetweenInclusive(double a, double b, double x) {
    return x >= a && x <= b;
}

bool Box::isBetweenExclusive(double a, double b, double x) {
    return x > a && x < b;
}

Vector3& Box::getAColor() {
    return aColor;
}
Vector3& Box::getRColor() {
    return rColor;
}
Vector3 Box::getSColor() {
    return Vector3();
}

bool Box::specular() {
    return false;
}