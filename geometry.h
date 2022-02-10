#ifndef geometry_h
#define geometry_h

#define INTERSECTION_POINT 1
#define INTERSECTION_NONE 0
/* Means that the intersection is a segment itself. */
#define INTERSECTION_SEGMENT -1
/* Means that the intersection is a line itself. */
#define INTERSECTION_LINE -2
/* Means that the intersection is an half line (ray) itself. */
#define INTERSECTION_RAY -3

#define LINE_TYPE_LIN 0
#define LINE_TYPE_VERT 1
#define LINE_TYPE_HORIZON 3
#define LINE_TYPE_NULL 4

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

typedef struct {
    char type;
    union{
        vector p;
        segment s;
        line l;
    };
} intersection;

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