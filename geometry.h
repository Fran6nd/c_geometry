#ifndef geometry_h
#define geometry_h

#define ACCURACY 100
#define ALMOST_EQ(a, b) ((a * ACCURACY - b * ACCURACY) * (a * ACCURACY - b * ACCURACY)) < ACCURACY

#define INTERSECTION_POINT 1
#define INTERSECTION_NONE 0
/* Means that the intersection is a segment itself. */
#define INTERSECTION_SEGMENT -1
/* Means that the intersection is a line itself. */
#define INTERSECTION_LINE -2
/* Means that the intersection is an half line (ray) itself. */
#define INTERSECTION_RAY -3

#define RAYCAST_NONE 0
#define RAYCAST_POINT 1

#define LINE_TYPE_LIN 0
#define LINE_TYPE_VERT 1
#define LINE_TYPE_HORIZON 3
#define LINE_TYPE_NULL 4

typedef struct
{
    double x, y;
} vector;

typedef struct
{
    vector origin;
    vector dir;
    double range;
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

typedef struct{
    vector points[3];
} triangle;

/* The difference between intersection and raycast_hit is that a raycast_hit can return only the closest point found, and a normal vector to the hitten segment. */

typedef struct
{
    char type;
    union
    {
        vector p;
        segment s;
        line l;
    };
} intersection;

typedef struct
{
    char type;
    vector p;
    vector normal;
    vector incident;
    vector reflected;
    double distance;
} raycast_hit;

/* All these methods are used to deal with vector structs. */

vector vector_new(double x, double y);
vector vector_sum(vector v1, vector v2);
vector vector_sub(vector v1, vector v2);
vector vector_mul(vector v, double d);
vector vector_div(vector v, double d);
double vector_get_arg(vector v);
double vector_get_positive_arg(vector v);
double vector_get_module(vector v);
vector vector_set_arg(vector v, double arg);
vector vector_set_module(vector v, double module);
vector vector_normalize(vector v);
void vector_increment(vector *v1, vector v2);
void vector_decrement(vector *v1, vector *v2);
vector vector_zero();
vector vector_get_closest_to(vector target, vector v1, vector v2);
#define vector_eq(v1, v2) (ALMOST_EQ(v1.x, v2.x) && ALMOST_EQ(v1.y, v2.y))

/* All these methods are used to deal with line structs. */

line line_new_from_segment(segment *s);
line line_new_from_ray(ray r);
line line_new(double a, double b);
line line_new_vert(double x);
line line_new_horiz(double y);
int line_calc_from_x(double *output, line *l, double x);
int line_calc_from_y(double *output, line *l, double y);
void line_print(line *l);
/* Return 1 if p is on l else 0. */
int line_contain_point(line *l, vector *p);

/* All these methods are used to deal with segment structs. */

segment segment_new(vector p1, vector p2);
int segment_contain_point(segment *s1, vector *p);
/*
For raycasting purpose, [intersection] contains a field [normal].
To get it work properly, we will assume that the ray is starting from [ray->p1] and ending at [ray->p2].
[seg] Being a shape of the obstacle.
*/
intersection segment_intersect(segment *ray, segment *seg);

/* All these methods are used to deal with ray structs. */

ray ray_new(vector origin, vector dir, double range);
int ray_contain_point(ray r, vector p);
ray ray_set_arg(ray r, double arg);

/* Here are the triangle stuff. */

triangle triangle_new(vector p1, vector p2, vector p3);
int triangle_contain_point(triangle *t, vector p);
/* Get segment 0, 1 or 2. */
segment triangle_get_segment_at(triangle *t, int n);

/* About getting intersections. */

intersection line_intersect_line(line *l1, line *l2);
intersection line_intersect_segment(line *l, segment *s);
#define segment_intersect_line(s, l) line_intersect_segment(l, s);
intersection ray_intersect_segment(ray *r, segment *s);

/* About raycasting stuff. */

raycast_hit raycast_segment(ray r, segment s);
raycast_hit raycast_triangle(ray * r, triangle * t);

#endif