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
segment_intersection segment_intersect(segment * s1, segment * s2){
    segment_intersection si;
    line l1 = line_new_from_segment(s1);
    line l2 = line_new_from_segment(s2);
    return si;
}