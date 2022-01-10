#ifndef SEGMENT_h
#define SEGMENT_h

#include <stdbool.h>
#include "vector.h"


#define LINE_TYPE_LIN 0
#define LINE_TYPE_VERT 1
#define LINE_TYPE_HORIZON 3
#define LINE_TYPE_NULL 4

typedef struct segment segment;
struct segment {
    vector p1, p2;
};

segment segment_new(vector p1, vector p2);

#endif