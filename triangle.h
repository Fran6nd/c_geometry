#ifndef triangle_h
#define triangle_h

#include "vector.h"
#include "transform.h"
#include "segment.h"

#define FOREACH_POINT_IN_TRIANGLE(t, p) for (vector * p = t.p ; p < t.p + 3; p++)
#define FOREACH_SEGMENT_IN_TRIANGLE(t,s)\
triangle_get_segment_reset();\
segment s = triangle_get_segment_next(t);\
for(; triangle_get_segment_done() == 0;  s = triangle_get_segment_next(t))\


typedef struct triangle triangle;
struct triangle {
    vector p[3];
    // Points with offset and rotation.
    vector _p[3];
};

segment triangle_get_segment_next(triangle * t);
void triangle_get_segment_reset();
int triangle_get_segment_done();
/* Return a new segment linking two points of the triangle, n being between 0 and 2. */
segment triangle_get_segment_at(triangle * t, int n);
void triangle_update(triangle *t, Transform * tr);
struct triangle triangle_new(vector p1, vector p2, vector p3);
#endif