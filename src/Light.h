#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H

#include "Vector3.h"

class Light {
public:
    Light(Vector3 color, Vector3 direction);

    Vector3 color, direction;
};


#endif //GRAPHICS_LIGHT_H
