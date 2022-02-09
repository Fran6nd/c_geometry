#ifndef geometry_h
#define geometry_h

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

typedef struct
{
    union
    {
        vector pt;
        segment seg;
    };

} segment_intersection;

typedef struct {
    char type;
    union{
        vector p;
        segment s;
        line l;
    };
} intesection;

#endif