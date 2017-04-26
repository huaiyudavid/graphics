//
// Created by david on 4/25/17.
//

#ifndef GRAPHICS_ORTHOCAMERA_H
#define GRAPHICS_ORTHOCAMERA_H

#include "Camera.h"
#include "Ray.h"

class OrthoCamera : public Camera {
public:
    virtual Ray getRay(double x, double y);
    virtual ~OrthoCamera();
};


#endif //GRAPHICS_ORTHOCAMERA_H
