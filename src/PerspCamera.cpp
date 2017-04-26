#include "PerspCamera.h"

PerspCamera::PerspCamera(Vector3 eye, Vector3 gaze, Vector3 up, double d, double au, double av, double bu, double bv, CLI& cli):
    left(au), right(bu), top(bv), bottom(av), d(d), eye(eye), cli(cli) {
    w = -gaze.unit();
    u = up.cross(w).unit();
    v = w.cross(u);
}

Ray PerspCamera::getRay(double x, double y) {
    double uScalar = left + (right - left) * (x + 0.5)/cli.width;
    double vScalar = bottom + (top - bottom) * (y + 0.5)/cli.height;
    return Ray(eye, w*(-d) + u*uScalar + v*vScalar);
}

PerspCamera::~PerspCamera() {}