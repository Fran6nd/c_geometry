#include "geometry.h"

raycast_hit raycast_segment(ray r, segment s)
{
    intersection in = ray_intersect_segment(&r, &s);
    raycast_hit hit;
    hit.incident = vector_normalize(r.dir);
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
            sides[0] = vector_normalize(sides[0]);
            sides[1] = vector_normalize(sides[1]);
            /* Now the closest one must be the normal one. */
            hit.normal = vector_get_closest_to(vector_sub(r.origin, in.p), sides[1], sides[0]);
            hit.type = RAYCAST_POINT;
            hit.p = in.p;

            vector reflected = vector_normalize(r.dir);

            double normal_arg = vector_get_positive_arg(hit.normal);
            double incoming_arg = vector_get_positive_arg(vector_sub(vector_zero(), r.dir));
            double reflected_arg = (normal_arg - incoming_arg) + normal_arg;
            hit.reflected = vector_set_arg(reflected, reflected_arg);

            return hit;
        }
    }
    /* If both points of the segment are contained in the ray and both are different from the origin. */
    else if (in.type == INTERSECTION_SEGMENT && ray_contain_point(r, in.s.p1) && ray_contain_point(r, in.s.p2) && !vector_eq(r.origin, in.s.p1) && !vector_eq(r.origin, in.s.p2))
    {
        hit.p = vector_get_closest_to(r.origin, in.s.p1, in.s.p2);
        hit.normal = vector_normalize(vector_sub(r.origin, hit.p));
        hit.reflected = vector_sub(vector_zero(), hit.incident);
        hit.type = RAYCAST_POINT;
        return hit;
    }
    else
    {
        hit.type = RAYCAST_NONE;
    }
    return hit;
}

raycast_hit raycast_triangle(ray * r, triangle * t){
    raycast_hit output;
    int found = 0;
    for(int i = 0; i < 3; i++){
        segment s = triangle_get_segment_at(t, i);
        raycast_hit tmp = raycast_segment(*r, s);
        if(tmp.type == RAYCAST_POINT){
            if (found == 1){
                if(vector_get_module( vector_sub(r->origin, tmp.p)) < vector_get_module( vector_sub(r->origin, output.p))){
                    output = tmp;
                }
            }
            else{
                output = tmp;
            }
            found = 1;
        }

    }
    if(found == 0){
        output.type = RAYCAST_NONE;
    }
    return output;
}