#include <assert.h>
#include "line.h"
#include "vector.h"
#include "segment.h"
#include <stdio.h>

/* These tests need improvements! */

int main()
{
    printf("---> Single line tests.\n");
    {
        line l1;
        l1 = line_new(1, 0);
        double res;
        printf("Testing for line y = x\n");
        assert(line_calc_from_x(&res, &l1, 5) == 0);
        assert(res == 5);
        assert(line_calc_from_y(&res, &l1, 4) == 0);
        assert(res == 4);
        printf("Testing for line y = 2 * x + 5\n");
        l1 = line_new(2, 5);
        assert(line_calc_from_x(&res, &l1, -5) == 0);
        assert(res == -5);
        assert(line_calc_from_y(&res, &l1, 4) == 0);
        assert(res == -0.5);
        printf("Testing for line y = 4\n");
        l1 = line_new_horiz(5);
        assert(line_calc_from_x(&res, &l1, -5) == 0);
        assert(res == 5);
        /* Infinite value. Should return 1.*/
        assert(line_calc_from_y(&res, &l1, -5) == 1);
        printf("Testing for line x = -2\n");
        l1 = line_new_vert(-4);
        assert(line_calc_from_y(&res, &l1, -5) == 0);
        assert(res == -4);
        /* Infinite value. Should return 1.*/
        assert(line_calc_from_x(&res, &l1, -5) == 1);
    }

    printf("---> Intersecting lines tests.\n");
    {
        line l1, l2;
        l1 = line_new(1, 1);
        l2 = line_new(-1, 1);
        vector res;
        assert(line_intersect(&l1, &l2, &res));
        assert(res.x == 0);
        assert(res.y == 1);
        l1 = line_new_vert(2);
        assert(line_intersect(&l1, &l2, &res) == LINE_INTERSECT_POINT);
        assert(line_intersect(&l2, &l1, &res) == LINE_INTERSECT_POINT);
        assert(res.y == -1);
        assert(res.x == 2);
        l2 = line_new_horiz(2);
        assert(line_intersect(&l1, &l2, &res) == LINE_INTERSECT_POINT);
        assert(line_intersect(&l2, &l1, &res) == LINE_INTERSECT_POINT);
        assert(res.y == 2);
        assert(res.x == 2);
        l2 = line_new_vert(3);
        assert(line_intersect(&l1, &l2, &res) == LINE_INTERSECT_NOT);
        assert(line_intersect(&l2, &l1, &res) == LINE_INTERSECT_NOT);
        /* Infinite intersection. */
        l2 = line_new_vert(2);
        assert(line_intersect(&l1, &l2, &res) == LINE_INTERSECT_INF);
        assert(line_intersect(&l2, &l1, &res) == LINE_INTERSECT_INF);
    }
    printf("---> Line containing point tests.\n");
    {
        vector v = vector_new(5, 6);
        line l1 = line_new(1, 1);
        assert(line_contain_point(&l1, &v) == 1);
        l1 = line_new_vert(5);
        assert(line_contain_point(&l1, &v) == 1);
        l1 = line_new_horiz(6);
        assert(line_contain_point(&l1, &v) == 1);
        l1 = line_new(1, 2);
        assert(line_contain_point(&l1, &v) == 0);
        l1 = line_new_vert(7);
        assert(line_contain_point(&l1, &v) == 0);
        l1 = line_new_horiz(4);
        assert(line_contain_point(&l1, &v) == 0);
    }
    printf("---> Segment containing point tests.\n");
    {
        /* Diagonal segment. */
        segment s = segment_new(vector_new(1, 1), vector_new(2, 2));
        vector p = vector_new(1.5, 1.5);
        assert(segment_contain_point(&s, &p) == 1);
        p = vector_new(1, 1.5);
        assert(segment_contain_point(&s, &p) == 0);
        p = vector_new(10, 10);
        assert(segment_contain_point(&s, &p) == 0);
        /* horizontal segment. */
        s = segment_new(vector_new(0, 0), vector_new(0, 2));
        p = vector_new(0, 1);
        assert(segment_contain_point(&s, &p) == 1);
        p = vector_new(0, 3);
        assert(segment_contain_point(&s, &p) == 0);
        p = vector_new(0, 0);
        assert(segment_contain_point(&s, &p) == 1);
        /* Vertical segment. */
        s = segment_new(vector_new(0, 0), vector_new(2, 0));
        p = vector_new(1, 0);
        assert(segment_contain_point(&s, &p) == 1);
        p = vector_new(3, 0);
        assert(segment_contain_point(&s, &p) == 0);
        p = vector_new(0, 0);
        assert(segment_contain_point(&s, &p) == 1);
    }
    printf("---> Segment intersecting segment.\n");
    {
        /* Diagonal segment. */
        segment s1 = segment_new(vector_new(-1, 1), vector_new(1, -1));
        segment s2 = segment_new(vector_new(1, 1), vector_new(-1, -1));
        segment_intersection si;
        assert(segment_intersect(&s1, &s2, &si) == SEGMENT_INTERSECT_IS_POINT);
        assert(si.pt.x == 0);
        assert(si.pt.y == 0);
        s2 = segment_new(vector_new(-1, 1), vector_new(1, -1));
        assert(segment_intersect(&s1, &s2, &si) == SEGMENT_INTERSECT_IS_SEGMENT);
        assert(si.seg.p1.x == s1.p1.x || si.seg.p1.x == s1.p2.x|| si.seg.p1.x == s2.p2.x|| si.seg.p1.x == s2.p2.x);
        assert(si.seg.p1.y == s1.p1.y || si.seg.p1.y == s1.p2.y|| si.seg.p1.y == s2.p2.y|| si.seg.p1.y == s2.p2.y);
        assert(si.seg.p2.x == s1.p1.x || si.seg.p2.x == s1.p2.x|| si.seg.p2.x == s2.p1.x|| si.seg.p2.x == s2.p2.x);
        assert(si.seg.p2.y == s1.p1.y || si.seg.p2.y == s1.p2.y|| si.seg.p2.y == s2.p1.y|| si.seg.p2.y == s2.p2.y);
    }

    return 0;
}