#include "geometry.h"
#include "common.h"
#include "stdlib.h"
#include <stdio.h>

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
                    goto found_intersection;
                }
            }
            break;
        }
        case INTERSECTION_LINE:
        {
            vector *tmp[2] = {NULL};
            int index = 0;
            /* If these vectors got the same arg, they share the same direction. */
            /* WRONG */
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

            /* If one */
            if (index == 1)
            {
                output.type = INTERSECTION_POINT;
                output.p = *tmp[0];
                goto found_intersection;
            }
            /* If two */
            else if (index == 2)
            {
                output.type = INTERSECTION_POINT;
                output.p = vector_get_closest_to(r->origin, output.s.p1, output.s.p2);
                goto found_intersection;
            }
            break;
        }

        default:
            break;
        }
        /* Should throw error. */
    }
    /* Default returned value by the statment. */
    output.type = INTERSECTION_NONE;
    return output;
    /* Here we do the normal vector calculation. */
found_intersection:;
    /* We create two vectors from the intersection point with segment ending as directions. */
    vector sides[] = {((vector_sub(s->p1, output.p))), ((vector_sub(s->p2, output.p)))};

    /* Now we rotate these vectors to make them perpendiculars to the segment in both directions. */
    sides[0] = vector_set_arg(sides[0], vector_get_arg(sides[0]) - 90);
    sides[1] = vector_set_arg(sides[0], vector_get_arg(sides[0]) - 180);
    /* Now we set them the same module. */
    sides[0] = vector_set_module(sides[0], 30);
    sides[1] = vector_set_module(sides[1], 30);
    /* Now the closest one must be the normal angle */
    vector closest_normal;
    closest_normal = vector_get_closest_to(vector_sub(r->origin, output.p), sides[1], sides[0]);

    output.normal = closest_normal;
    output.type = INTERSECTION_POINT;
    return output;
}