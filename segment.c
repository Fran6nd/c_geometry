#include <stdio.h>
#include <math.h>
#include "geometry.h"

segment segment_new(vector p1, vector p2)
{
    segment s = {
        .p1 = p1,
        .p2 = p2,
    };
    return s;
}
int segment_contain_point(segment *s, vector *p)
{
    line l1 = line_new_from_segment(s);
    double res;
    /*
        The 3 points are aligned if the area of the triangle is 0
        [ Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By) ] / 2 == 0
        Why I do multiply the area by 100 and convert it to int? Because with too many decimals it causes bugs.
        Then we will check that the point fit into the segment's rect.
    */

    /* This is ugly. */
#define A s->p1
#define B s->p2
#define C (*p)

    if (((int)((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2 * ACCURACY)) == 0)
    {
        if ((p->x >= fmin(s->p1.x, s->p2.x)) && (p->x <= fmax(s->p1.x, s->p2.x)) && (p->y >= fmin(s->p1.y, s->p2.y)) && (p->y <= fmax(s->p1.y, s->p2.y)))
        {
            return 1;
        }
        /* I don't know yet why I need this... The case where the point is at an ending of the segment. */
        else if (ALMOST_EQ(p->x, s->p1.x) || ALMOST_EQ(p->x, s->p2.x))
        {
            if (ALMOST_EQ(p->y, s->p1.y) || ALMOST_EQ(p->y, s->p2.y))
            {
                return 1;
            }
        }
    }
#undef A
#undef B
#undef C
    return 0;
}

intersection segment_intersect(segment *ray, segment *seg)
{
    intersection output;
    line l1 = line_new_from_segment(ray);
    line l2 = line_new_from_segment(seg);
    intersection i = line_intersect_line(&l1, &l2);
    if (i.type != INTERSECTION_NONE)
    {
        switch (i.type)
        {
        case INTERSECTION_POINT:
            if (segment_contain_point(ray, &i.p) && segment_contain_point(seg, &i.p))
            {
                output.p = i.p;
                output.type = INTERSECTION_POINT;
                return output;
            }
            break;
        case INTERSECTION_LINE:
        {
            vector contained[2];
            int index = 0;
            if (segment_contain_point(seg, &ray->p1))
            {
                contained[index] = ray->p1;
                index++;
            }
            if (segment_contain_point(seg, &ray->p2))
            {
                contained[index] = ray->p2;
                index++;
            }
            if (segment_contain_point(ray, &seg->p1) && index < 2)
            {
                contained[index] = seg->p1;
                index++;
            }
            if (segment_contain_point(ray, &seg->p2) && index < 2)
            {
                contained[index] = seg->p2;
                index++;
            }
            if (index == 2)
            {
                output.s.p1 = contained[0];
                output.s.p2 = contained[1];

                output.type = INTERSECTION_SEGMENT;
                return output;
            }
            else if (index == 1)
            {
                output.p = contained[0];
                output.type = INTERSECTION_POINT;
                return output;
            }
        }

        break;

        default:
            break;
        }
    }
    output.type = INTERSECTION_NONE;
    return output;
}