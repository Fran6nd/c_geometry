#include "geometry.h"

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
}