#ifndef LINE_h
#define LINE_h

#include <stdbool.h>
#include "vector.h"
#include "segment.h"

#define LINE_TYPE_LIN 0
#define LINE_TYPE_VERT 1
#define LINE_TYPE_HORIZON 3
#define LINE_TYPE_NULL 4

#define LINE_INTERSECT_NOT 0
#define LINE_INTERSECT_POINT 1
#define LINE_INTERSECT_INF -1

typedef struct line line;
struct line
{
    double a, b;
    char type;
};

line line_new_from_segment(segment *s);
line line_new(double a, double b);
line line_new_vert(double x);
line line_new_horiz(double y);
int line_calc_from_x(double *output, line *l, double x);
int line_calc_from_y(double *output, line *l, double y);
void line_print(line *l);
/* Return LINE_INTERSECT_INF or LINE_INTERSECT_POINT or LINE_INTERSECT_NOT */
int line_intersect(line *l1, line *l2, vector *intersection);
/* Return 1 if p is on l else 0. */
int line_contain_point(line * l, vector * p);

#endif