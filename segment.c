#include "segment.h"
#include "line.h"
segment segment_new(vector p1, vector p2)
{
    segment s = {
        .p1 = p1,
        .p2 = p2,
    };
    return s;
}
int segment_contain_point(segment *s1, vector *p)
{
    line l1 = line_new_from_segment(s1);
    double res;
    if (line_contain_point(&l1, p))
    {
        if ((p->x <= s1->p1.x && p->x >= s1->p2.x) || (p->x >= s1->p1.x && p->x <= s1->p2.x))
            if ((p->y <= s1->p1.y && p->y >= s1->p2.y) || (p->y >= s1->p1.y && p->y <= s1->p2.y))
                return 1;
    }
    return 0;
}
int segment_intersect(segment *s1, segment *s2, segment_intersection *si)
{
    line l1 = line_new_from_segment(s1);
    line l2 = line_new_from_segment(s2);
    vector intersection;
    int res = line_intersect(&l1, &l2, &intersection);
    if (res != LINE_INTERSECT_NOT)
    {
        switch (res)
        {
        case LINE_INTERSECT_POINT:
            si->pt = intersection;
            return SEGMENT_INTERSECT_IS_POINT;
            break;
        case LINE_INTERSECT_INF:
            /* code */
            break;

        default:
            break;
        }
    }
    return SEGMENT_INTERSECT_IS_NONE;
}