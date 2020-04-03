#include <stdio.h>
#include "triangle.h"
#include "vector.h"
int sign(vector p1, vector p2, vector p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int is_point_in_triangle(Triangle *t, vector p)
{
    int b1 = sign(p, t->p[0], t->p[1]) > 0;
    int b2 = sign(p, t->p[1], t->p[2]) > 0;
    int b3 = sign(p, t->p[2], t->p[0]) > 0;
    return ((b1 == b2) && (b2 == b3));
}

void triangle_update(Triangle *t, Transform *tr)
{
    int i = 0;
    for (; i < 3; i++)
    {
        double arg = vector_get_arg(&(t->p[i]));
        arg += tr->rotation;
        t->_p[i].x = t->p[i].x;
        t->_p[i].y = t->p[i].y;
        t->_p[i] = vector_set_arg((t->_p[i]), arg);
        t->_p[i] = vector_sum(t->_p[i], tr->position);
    }
}
struct Triangle triangle_new(Transform *t, vector p1, vector p2, vector p3)
{
    struct Triangle tr;
    tr.transform = &t;
    tr.p[0] = p1;
    tr.p[1] = p2;
    tr.p[2] = p3;
    return tr;
}