#include "c_geometry.h"

quad quad_new(vector p1, vector p2, vector p3, vector p4)
{
    quad output = {.half = {triangle_new(p1, p2, p3), triangle_new(p3, p4, p1)}};
    return output;
}
int quad_contain_point(quad *q, vector p){
    return (triangle_contain_point(&q->half[0], p)|| triangle_contain_point(&q->half[1], p));
}