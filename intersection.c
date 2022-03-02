#include "geometry.h"
#include "common.h"
#include "stdlib.h"

intersection line_intersect_segment(line *l, segment *s)
{
    line l1 = line_new_from_segment(s);
    intersection output = line_intersect_line(l, &l1);
    if (output.type != INTERSECTION_NONE)
    {
        switch (output.type)
        {
        case INTERSECTION_POINT:
        {
            if (segment_contain_point(s, &output.p))
            {
                return output;
            }
            break;
        }
        case INTERSECTION_LINE:
        {

            output.type = INTERSECTION_SEGMENT;
            output.s.p1 = s->p1;
            output.s.p2 = s->p2;
            return output;

            break;
        }

        default:
            break;
        }
        /* Should throw error. */
    }
    return output;
}

intersection ray_intersect_segment(ray *r, segment *s)
{
    line l = line_new_from_ray(*r);
    line l1 = line_new_from_segment(s);
    intersection output = line_intersect_line(&l, &l1);
    if (output.type != INTERSECTION_NONE)
    {
        switch (output.type)
        {
        case INTERSECTION_POINT:
        {
            if (segment_contain_point(s, &output.p))
            {
                if(ray_contain_point(*r, output.p)){
                    return output;
                }

            }
            output.type = INTERSECTION_NONE;
            return output;
            break;
        }
        case INTERSECTION_LINE:
        {

            output.type = INTERSECTION_SEGMENT;
            vector *tmp[2] = {NULL};
            int index = 0;
            /* If these vectors got the same arg, they share the same direction. */
            if (ray_contain_point(*r, s->p1))
            {
                tmp[index] = &s->p1;
                index++;
            }
            if (ray_contain_point(*r, s->p2))
            {
                tmp[index] = &s->p2;
                index++;
            }
            /* If none of the points is share the ray's direction. */
            if (index == 0)
            {
                output.type = INTERSECTION_NONE;
            }
            /* If one */
            else if (index = 1)
            {
                output.type = INTERSECTION_POINT;
                output.p = *tmp[0];
            }
            /* If two */
            else if (index == 2)
            {
                output.type = INTERSECTION_POINT;
                output.p = vector_get_closest_to(r->origin, output.s.p1, output.s.p2);
            }
            return output;
            break;
        }

        default:
            break;
        }
        /* Should throw error. */
    }
    return output;
}