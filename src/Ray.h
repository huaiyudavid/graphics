//
// Created by david on 4/25/17.
//

#ifndef GRAPHICS_RAY_H
#define GRAPHICS_RAY_H

#include "Vector3.h"

class Ray {
public:
    Ray(Vector3 start, Vector3 direction);

    Vector3 start, direction;
};


#endif //GRAPHICS_RAY_H
