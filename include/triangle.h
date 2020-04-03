#ifndef TRIANGLE_h
#define TRIANGLE_h

#include "vector.h"
#include "transform.h"

typedef struct Triangle Triangle;
struct Triangle {
    Transform * transform;
    vector p[3];
    // Points with offset and rotation.
    vector _p[3];
};

void triangle_update(Triangle *t, Transform * tr);
struct Triangle triangle_new(Transform * t, vector p1, vector p2, vector p3);
#endif