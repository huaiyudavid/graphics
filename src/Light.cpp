#include "Light.h"

Light::Light(Vector3 color, Vector3 direction): color(color), direction(direction.unit()) {}