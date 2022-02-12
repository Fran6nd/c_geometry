#include <math.h>
#include "geometry.h"

#define PI 3.14159265358979323846264338327950288
vector vector_new(double x, double y){
    vector v = {.x = x, .y = y};
    return v;
}
vector vector_sum(vector v1, vector v2)
{
    vector output;
    output.x = v1.x + v2.x;
    output.y = v1.y + v2.y;
    return output;
}
vector vector_sub(vector v1, vector v2)
{
    vector output;
    output.x = v1.x - v2.x;
    output.y = v1.y - v2.y;
    return output;
}
vector vector_mul(vector v, double d)
{
    vector output;
    output.x = v.x * d;
    output.y = v.y * d;
    return output;
}
vector vector_div(vector v, double d)
{
    vector output;
    output.x = v.x / d;
    output.y = v.y / d;
    return output;
}
double vector_get_arg(vector *v)
{
    return 90-atan2(v->x, v->y)* (180.0 / PI);
}
double vector_get_module(vector *v)
{
    return sqrt(pow(v->x, 2) + pow(v->y, 2));
}
/* arg is given in degrees. */
vector vector_set_arg(vector v, double arg)
{
    arg = arg / (180.0 / PI);
    vector output;
    double module = vector_get_module(&v);
    output.y = sin(arg) * module;
    output.x = cos(arg) * module;
    return output;
}
vector vector_set_module(vector v, double module)
{
    v = vector_normalize(v);
    v = vector_mul(v, module);
    return v;
}
vector vector_normalize(vector v)
{
    double arg = vector_get_arg(&v);
    vector output = vector_new(0, 1);
    output = vector_set_arg(output, arg);
    return output;
}
void vector_increment(vector * v1, vector v2){
    v1->x = v1->x + v2.x;
    v1->y = v1->y + v2.y;
}
void vector_decrement(vector * v1, vector* v2){
    v1->x = v1->x - v2->x;
    v1->y = v1->y - v2->y;
}
vector vector_zero(){
    vector v = {0,0};
    return v;
}

vector vector_get_closest_to(vector target, vector v1, vector v2){
    vector v11 = vector_sub(target, v1);
    vector v22 = vector_sub(target, v2);
    double d1, d2;
    d1 = vector_get_module(&v11);
    d2 = vector_get_module(&v22);
    if(d1>d2){
        return v2;
    }
    return v1;

}