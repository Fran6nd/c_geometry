#ifndef geometry_h
#define geometry_h

#define LINE_TYPE_LIN 0
#define LINE_TYPE_VERT 1
#define LINE_TYPE_HORIZON 3
#define LINE_TYPE_NULL 4

#define SEGMENT_INTERSECT_IS_POINT 1
#define SEGMENT_INTERSECT_IS_NONE 0
/* Means that the intersection is a segment itself. */
#define SEGMENT_INTERSECT_IS_SEGMENT -1

#define LINE_TYPE_LIN 0
#define LINE_TYPE_VERT 1
#define LINE_TYPE_HORIZON 3
#define LINE_TYPE_NULL 4

#define LINE_INTERSECT_NOT 0
#define LINE_INTERSECT_POINT 1
#define LINE_INTERSECT_INF -1


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