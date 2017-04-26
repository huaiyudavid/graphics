//
// Created by david on 4/25/17.
//

#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include "Ray.h"

class Camera {
public:
    virtual Ray getRay(double x, double y) = 0;
    virtual ~Camera() {};
};


#endif //GRAPHICS_CAMERA_H
