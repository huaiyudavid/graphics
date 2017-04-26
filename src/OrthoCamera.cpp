#include "OrthoCamera.h"

Ray OrthoCamera::getRay(double x, double y) {
    return Ray(Vector3(x, y, 0), Vector3(0, 0, -1));
}

OrthoCamera::~OrthoCamera() {}
