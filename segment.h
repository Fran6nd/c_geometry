#ifndef SEGMENT_h
#define SEGMENT_h

#include <stdbool.h>
#include "vector.h"

#define LINE_TYPE_LIN 0
#define LINE_TYPE_VERT 1
#define LINE_TYPE_HORIZON 3
#define LINE_TYPE_NULL 4

#define SEGMENT_INTERSECT_IS_POINT 1
#define SEGMENT_INTERSECT_IS_NONE 0
/* Means that the intersection is a segment itself. */
#define SEGMENT_INTERSECT_IS_SEGMENT -1

#include "structs.h"

segment segment_new(vector p1, vector p2);
int segment_contain_point(segment *s1, vector *p);
int segment_intersect(segment *s1, segment *s2, segment_intersection *si);

#endif