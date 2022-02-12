#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include <math.h>
#include "geometry.h"

line line_new_from_segment(segment *s)
{
    line l1 = {};
    if (s->p2.y == s->p1.y && s->p2.x == s->p1.x)
    {
        l1.type = LINE_TYPE_NULL;
    }
    else if ( ALMOST_EQ(s->p1.x, s->p2.x))
    {
        l1.type = LINE_TYPE_VERT;
        l1.a = -1;
        l1.b = s->p1.x;
    }
    else if (ALMOST_EQ(s->p1.y , s->p2.y))
    {
        l1.type = LINE_TYPE_HORIZON;
        l1.a = -1;
        l1.b = s->p1.y;
    }
    else
    {
        l1.type = LINE_TYPE_LIN;
        l1.a = (s->p1.y - s->p2.y) / (s->p1.x - s->p2.x);
        l1.b = ((s->p2.x * s->p1.y) - (s->p1.x * s->p2.y)) / (s->p2.x - s->p1.x);
    }
    return l1;
}

line line_from_ray(ray r){
    segment s = {
        .p1 = r.origin,
        .p2 = vector_sum(r.dir, r.origin),
    };
    return line_new_from_segment(&s);
}

line line_new(double a, double b)
{
    line l1 = {
        .a = a,
        .b = b,
        .type = LINE_TYPE_LIN,
    };
    return l1;
}
line line_new_vert(double x)
{
    line l1 = {
        .a = -1,
        .b = x,
        .type = LINE_TYPE_VERT,
    };
    return l1;
}
line line_new_horiz(double y)
{
    line l1 = {
        .a = -1,
        .b = y,
        .type = LINE_TYPE_HORIZON,
    };
    return l1;
}
int line_calc_from_x(double *output, line *l, double x)
{
    if (l->type == LINE_TYPE_LIN)
    {
        *output = l->a * x + l->b;
    }
    else if (l->type == LINE_TYPE_HORIZON)
    {
        *output = l->b;
    }
    else if (l->type == LINE_TYPE_VERT)
    {
        /* No values for x */
        return 1;
    }
    else
    {
        /* Return error. */
        return -1;
    }
    return 0;
}

int line_calc_from_y(double *output, line *l, double y)
{
    if (l->type == LINE_TYPE_LIN)
    {
        *output = (y - l->b) / l->a;
    }
    else if (l->type == LINE_TYPE_HORIZON)
    {
        /* No values for x */
        return 1;
    }
    else if (l->type == LINE_TYPE_VERT)
    {
        *output = l->b;
    }
    else
    {
        /* Return error. */
        return -1;
    }
    return 0;
}
void line_print(line *l)
{
    if (l->type == LINE_TYPE_LIN)
    {
        printf("Line: y = %f * x + %f   type:%d\n", l->a, l->b, (int)l->type);
    }
    else if (l->type == LINE_TYPE_VERT)
    {
        printf("Line: x = %f\n", l->b);
    }
    else if (l->type == LINE_TYPE_HORIZON)
    {
        printf("Line: y = %f\n", l->b);
    }
    else
    {
        printf("Error, invalid line type. \n");
    }
}

intersection line_intersect(line *l1, line *l2)
{
    intersection output;
    /*
        This is some kind of simple brute force :p
        H means horizontal line,
        V means vertical line,
        L mieans linear, kinda non constant line.

        Truth table:
        ==
        HH
        VV
        LL
        VH
        VL
        HL
    */

    /* == */
    if (l1->type == l2->type && ALMOST_EQ(l1->a, l2->a ) && ALMOST_EQ(l1->b,l2->b))
    {
        /* Same line. Infinite intersection. */
        output.type = INTERSECTION_LINE;
        return output;
    }
    /* HH */
    if (l1->type == LINE_TYPE_HORIZON && l2->type == LINE_TYPE_HORIZON)
    {
        output.type = INTERSECTION_LINE;
        return output;
    }
    /* VV */
    else if (l1->type == LINE_TYPE_VERT && l2->type == LINE_TYPE_VERT)
    {
        output.type = INTERSECTION_NONE;
        return output;
    }
    /* LL */
    else if (l1->type == LINE_TYPE_LIN && l2->type == LINE_TYPE_LIN)
    {
        // x = (d-b)/(a-c)
        output.p.x = (l2->b - l1->b) / (l1->a - l2->a);
        line_calc_from_x(&output.p.y, l1, output.p.x);
        output.type = INTERSECTION_POINT;
        return output;
    }

    line *vert = NULL;
    line *horiz = NULL;
    line *lin = NULL;
    if (l1->type == LINE_TYPE_VERT)
    {
        vert = l1;
    }
    else if (l2->type == LINE_TYPE_VERT)
    {
        vert = l2;
    }
    if (l1->type == LINE_TYPE_HORIZON)
    {
        horiz = l1;
    }
    else if (l2->type == LINE_TYPE_HORIZON)
    {
        horiz = l2;
    }
    if (l1->type == LINE_TYPE_LIN)
    {
        lin = l1;
    }
    else if (l2->type == LINE_TYPE_LIN)
    {
        lin = l2;
    }

    /* VH */
    if (vert != NULL && horiz != NULL)
    {
        output.p.x = vert->b;
        output.p.y = horiz->b;
        output.type = INTERSECTION_POINT;
        return output;
    }
    /* VL */
    else if (vert != NULL && lin != NULL)
    {

        output.p.x = vert->b;
        line_calc_from_x(&output.p.y, lin, output.p.x);
        output.type = INTERSECTION_POINT;
        return output;
    }
    /* HL */
    else if (horiz != NULL && lin != NULL)
    {
        output.p.y = horiz->b;
        line_calc_from_y(&output.p.x, lin, output.p.y);
        output.type = INTERSECTION_POINT;
        return output;
    }

        output.type = INTERSECTION_NONE;
        return output;
}
/* Should be fixed by the methods of the air of the triangle == 0 */
int line_contain_point(line *l, vector *p)
{
    double res;
    switch (l->type)
    {
    case LINE_TYPE_LIN:
        if (line_calc_from_x(&res, l, p->x) == 0)
            if (res == p->y)
            {
                return 1;
            }
        break;
    case LINE_TYPE_VERT:
        if (p->x == l->b)
        {
            return 1;
        }
        break;
    case LINE_TYPE_HORIZON:
        if (p->y == l->b)
        {
            return 1;
        }
        break;

    default:
        /* Error */
        break;
    }
    return 0;
}