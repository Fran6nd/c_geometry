#include "geometry.h"

intersection find_intersection_ray_segment(ray r, segment s1)
{
    /*
    intersection output;
    line l1 = line_from_ray(r);
    line l2 = line_new_from_segment(&s);

    intersection i = line_intersect(&l1, &l2);
    if (i.type != INTERSECTION_NONE)
    {
        switch (i.type)
        {
        case INTERSECTION_POINT:
            if (segment_contain_point(s1, &i.p) && segment_contain_point(s2, &i.p))
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
            if (segment_contain_point(s2, &s1->p1))
            {
                contained[index] = s1->p1;
                index++;
            }
            if (segment_contain_point(s2, &s1->p2))
            {
                contained[index] = s1->p2;
                index++;
            }
            if (segment_contain_point(s1, &s2->p1) && index < 2)
            {
                contained[index] = s2->p1;
                index++;
            }
            if (segment_contain_point(s1, &s2->p2) && index < 2)
            {
                contained[index] = s2->p2;
                index++;
            }
            if (index == 2)
            {
                output.s.p1 = contained[0];
                output.s.p2 = contained[1];
                output.type = INTERSECTION_SEGMENT;
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
    */
}