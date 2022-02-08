#ifndef struct_h
#define struct_h

typedef struct
{
    double x, y;
} vector;

typedef struct {
    vector origin;
    float angle;
} ray;

typedef struct
{
    double a, b;
    char type;
} line;

typedef struct
{
    vector p1, p2;
} segment;

typedef struct segment_intersection
{
    union
    {
        vector pt;
        segment seg;
    };

} segment_intersection;

#endif