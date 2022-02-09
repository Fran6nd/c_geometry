#ifndef SEGMENT_h
#define SEGMENT_h

#include <stdbool.h>
#include "vector.h"
#include "geometry.h"

segment segment_new(vector p1, vector p2);
int segment_contain_point(segment *s1, vector *p);
intersection segment_intersect(segment *s1, segment *s2);

#endif