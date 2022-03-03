#include "geometry.h"

raycast_hit raycast_segment(ray r, segment s)
{
    intersection in = ray_intersect_segment(&r, &s);
    raycast_hit hit;
    if (in.type == INTERSECTION_POINT)
    {
        if (segment_contain_point(&s, &r.origin))
        {
            /* Cannot emit a ray from inside a segment. */
        }
        else
        {
            /* We create two vectors from the intersection point with segment ending as directions. */
            vector sides[] = {((vector_sub(s.p1, in.p))), ((vector_sub(s.p2, in.p)))};

            /* Now we rotate these vectors to make them perpendiculars to the segment in both directions. */
            sides[0] = vector_set_arg(sides[0], vector_get_arg(sides[0]) - 90);
            sides[1] = vector_set_arg(sides[0], vector_get_arg(sides[0]) - 180);
            /* Now we set them the same module. */
            sides[0] = vector_set_module(sides[0], 30);
            sides[1] = vector_set_module(sides[1], 30);
            /* Now the closest one must be the normal one. */
            hit.normal = vector_get_closest_to(vector_sub(r.origin, in.p), sides[1], sides[0]);
            hit.type = RAYCAST_POINT;
            hit.p = in.p;
            return hit;
        }
    }
    /* If both points of the segment are contained in the ray and both are different from the origin. */
    else if (in.type == INTERSECTION_SEGMENT && ray_contain_point(r, in.s.p1)&& ray_contain_point(r, in.s.p2) && !vector_eq(r.origin, in.s.p1) && !vector_eq(r.origin, in.s.p2))
    {
        hit.p = vector_get_closest_to(r.origin, in.s.p1, in.s.p2);
        hit.normal = vector_set_module(vector_sub(r.origin, hit.p), 30);
        hit.type = RAYCAST_POINT;
        return hit;

    }
    else
    {
        hit.type = RAYCAST_NONE;
    }
    return hit;
}