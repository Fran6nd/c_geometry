#include <assert.h>
#include "line.h"
#include "vector.h"
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
        assert(line_contain_point(&l1,&v) == 1);
        l1 = line_new_vert(5);
        assert(line_contain_point(&l1,&v) == 1);
        l1 = line_new_horiz(6);
        assert(line_contain_point(&l1,&v) == 1);
        l1 = line_new(1, 2);
        assert(line_contain_point(&l1,&v) == 0);
        l1 = line_new_vert(7);
        assert(line_contain_point(&l1,&v) == 0);
        l1 = line_new_horiz(4);
        assert(line_contain_point(&l1,&v) == 0);

    }
    printf("---> Intersecting segments tests.\n");
    {
    }

    return 0;
}