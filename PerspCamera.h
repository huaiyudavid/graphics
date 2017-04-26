#ifndef GRAPHICS_PERSPCAMERA_H
#define GRAPHICS_PERSPCAMERA_H

#include "Camera.h"
#include "Ray.h"
#include "Vector3.h"
#include "CLI.h"

class PerspCamera : public Camera {
public:
    PerspCamera(Vector3 eye, Vector3 gaze, Vector3 up, double d, double au, double av, double bu, double bv, CLI& cli);
    virtual Ray getRay(double x, double y);
    virtual ~PerspCamera();

private:
    double left, right, top, bottom;
    double d;
    Vector3 eye;
    Vector3 u, v, w;
    CLI cli;
};


#endif //GRAPHICS_PERSPCAMERA_H
