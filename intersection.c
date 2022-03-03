#include "geometry.h"
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
                if (ray_contain_point(*r, output.p))
                {
                    output.type = INTERSECTION_POINT;
                    return output;
                }
            }
            break;
        }
        case INTERSECTION_LINE:
        {
            vector *tmp[2] = {NULL};
            int index = 0;
            /* If these vectors got the same arg, they share the same direction. */
            if (ray_contain_point(*r, s->p1) || (ray_contain_point(*r, s->p2)))
            {
                if (ray_contain_point(*r, s->p1))
                {
                    tmp[index] = &s->p1;
                    index++;
                }
                else
                {
                    tmp[index] = &r->origin;
                    index++;
                }
                if (ray_contain_point(*r, s->p2))
                {
                    tmp[index] = &s->p2;
                    index++;
                }
                else
                {
                    tmp[index] = &r->origin;
                    index++;
                }
                output.type = INTERSECTION_SEGMENT;
                output.s.p1 = *tmp[0];
                output.s.p2 = *tmp[1];
                return output;

                break;
            }
        }

        default:
            break;
        }
        /* Should throw error. */
    }
    /* Default returned value by the statment. */
    output.type = INTERSECTION_NONE;
    return output;
}