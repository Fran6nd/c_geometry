#ifndef COMPONENTS_h
#define COMPONENTS_h

#include "transform.h"
#include "triangle.h"

struct tank {
    Transform transform;
    Triangle hitbox[2];
};

struct tank tank_new(double x, double y, double rotation);
void tank_update(struct tank *t, double dt);
#endif