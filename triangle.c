#include <stdio.h>
#include "triangle.h"
#include "geometry.h"

int sign(vector p1, vector p2, vector p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int is_point_in_triangle(triangle *t, vector p)
{
    int b1 = sign(p, t->p[0], t->p[1]) > 0;
    int b2 = sign(p, t->p[1], t->p[2]) > 0;
    int b3 = sign(p, t->p[2], t->p[0]) > 0;
    return ((b1 == b2) && (b2 == b3));
}

void triangle_update(triangle *t, Transform *tr)
{

    for (int i = 0; i < 3; i++)
    {
        double arg = vector_get_arg(&(t->p[i]));
        arg += tr->rotation;
        t->_p[i] = vector_set_arg((t->p[i]), vector_get_arg(&(t->p[i])) + tr->rotation);
        //printf("->arg: %f\n", arg);
        t->_p[i] = vector_sum(t->_p[i], tr->position);
    }
}
struct triangle triangle_new(vector p1, vector p2, vector p3)
{
    struct triangle tr;
    tr.p[0] = p1;
    tr.p[1] = p2;
    tr.p[2] = p3;
    tr._p[0] = p1;
    tr._p[1] = p2;
    tr._p[2] = p3;
    return tr;
}
segment triangle_get_segment_at(triangle *t, int n)
{
    return segment_new(t->p[n], n < 1 ? (t->p[n + 1]) : (t->p[0]));
}
/* -1 means no reset occured, so we should prevent from triangle_get_segment_next() */
int idx = -1;
segment triangle_get_segment_next(triangle * t){
    printf("n%d\n", idx-1);
    idx ++;
    segment s = triangle_get_segment_at(t, idx-1);
    return s; 
}
void triangle_get_segment_reset(){
    idx = 0;
}
int triangle_get_segment_done(){
    
    return (idx - 1 == 3) ? 1 : 0;
}