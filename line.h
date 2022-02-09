#ifndef LINE_h
#define LINE_h

#include <stdbool.h>
#include "vector.h"
#include "segment.h"

#include "geometry.h"

line line_new_from_segment(segment *s);
line line_new(double a, double b);
line line_new_vert(double x);
line line_new_horiz(double y);
int line_calc_from_x(double *output, line *l, double x);
int line_calc_from_y(double *output, line *l, double y);
void line_print(line *l);
intersection line_intersect(line *l1, line *l2);
/* Return 1 if p is on l else 0. */
int line_contain_point(line *l, vector *p);

#endif