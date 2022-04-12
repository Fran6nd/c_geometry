#include <stdio.h>
#include "c_geometry.h"

triangle triangle_new(vector p1, vector p2, vector p3)
{
    triangle tr;
    tr.points[0] = p1;
    tr.points[1] = p2;
    tr.points[2] = p3;
    tr.points[0] = p1;
    tr.points[1] = p2;
    tr.points[2] = p3;
    return tr;
}

static inline int sign(vector p1, vector p2, vector p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int triangle_contain_point(triangle *t, vector p)
{
    int b1 = sign(p, t->points[0], t->points[1]) > 0;
    int b2 = sign(p, t->points[1], t->points[2]) > 0;
    int b3 = sign(p, t->points[2], t->points[0]) > 0;
    return ((b1 == b2) && (b2 == b3));
}

/* Get segment 0, 1 or 2. */
segment triangle_get_segment_at(triangle *t, int n)
{
    return segment_new(t->points[n], n < 2 ? (t->points[n + 1]) : (t->points[0]));
}
