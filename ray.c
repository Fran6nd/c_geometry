#include "geometry.h"

ray ray_new(vector origin, vector dir, double range)
{
    ray r = {
        .dir = dir,
        .origin = origin,
        .range = range,
    };
    return r;
}

int ray_contain_point(ray r, vector p)
{
    line l = line_new_from_ray(r);
    if (line_contain_point(&l, &p))
    {
        vector relative_pos_of_p = vector_sub(p, r.origin);
        /* If both vectors dir and relative_pos_of_p shares the same direction and if the origin is the point p. */
        /* Why a ray cannot contain its origin? Because to caluculate the normal vector it does not make sense. */
        /* Emitting a ray from a point inside the targeted segment does not make sense. */
        if (ALMOST_EQ(vector_get_positive_arg(relative_pos_of_p), vector_get_positive_arg(r.dir)) && !vector_eq(r.origin, p))
        {
            /* If a range is specified, check if the point is in. */
            if (r.range == 0 || vector_get_module(relative_pos_of_p) < r.range)
            {
                return 1;
            }
        }
    }
    return 0;
}