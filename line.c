#include "line.h"
#include <stdlib.h>
#include <stdio.h>

line line_new_from_segment(segment * s)
{
    line l1 = {};
    if (s->p2.y == s->p1.y && s->p2.x == s->p1.x)
    {
        l1.type = LINE_TYPE_NULL;
    }
    else if (s->p1.x == s->p2.x)
    {
        l1.type = LINE_TYPE_VERT;
    }
    else if (s->p1.y == s->p2.y)
    {
        l1.type = LINE_TYPE_HORIZON;
        l1.a = s->p1.y;
    }
    else
    {
        l1.type = LINE_TYPE_LIN;
        l1.a = (s->p1.y - s->p2.y) / (s->p1.x - s->p2.x);
        l1.b = ((s->p2.x * s->p1.y) - (s->p1.x * s->p2.y)) / (s->p2.x - s->p1.x);
    }
    return l1;
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
        printf("Line: y = %f * x + %f\n", l->b, l->b);
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
int line_intersect(line *l1, line *l2, vector *intersection)
{
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
    if (l1->type == l2->type && l1->a == l2->a && l1->b == l2->b)
    {
        /* Same line. Infinite intersection. */
        return LINE_INTERSECT_INF;
    }
    /* HH */
    if (l1->type == LINE_TYPE_HORIZON && l2->type == LINE_TYPE_HORIZON)
    {
        return LINE_INTERSECT_NOT;
    }
    /* VV */
    else if (l1->type == LINE_TYPE_VERT && l2->type == LINE_TYPE_VERT)
    {
        return LINE_INTERSECT_NOT;
    }
    /* LL */
    else if (l1->type == LINE_TYPE_LIN && l2->type == LINE_TYPE_LIN)
    {
        // x = (d-b)/(a-c)
        intersection->x = (l2->b - l1->b) / (l1->a - l2->a);
        line_calc_from_x(&intersection->y, l1, intersection->x);
        return LINE_INTERSECT_POINT;
    }



    line * vert = NULL;
    line*horiz = NULL;
    line * lin = NULL;
    if(l1->type == LINE_TYPE_VERT){
        vert = l1;
    }
    else if(l2->type == LINE_TYPE_VERT){
        vert = l2;
    }
    if(l1->type == LINE_TYPE_HORIZON){
        horiz = l1;
    }
    else if(l2->type == LINE_TYPE_HORIZON){
        horiz = l2;
    }
    if(l1->type == LINE_TYPE_LIN){
        lin = l1;
    }
    else if(l2->type == LINE_TYPE_LIN){
        lin = l2;
    }




    /* VH */
     if (vert != NULL && horiz != NULL)
    {
        intersection->x = vert->b;
        intersection->y = horiz->b;
        return LINE_INTERSECT_POINT;
    }
    /* VL */
    else if (vert != NULL && lin != NULL)
    {

        intersection->x = vert->b;
        line_calc_from_x(&intersection->y, lin, intersection->x);
        return LINE_INTERSECT_POINT;
    }
    /* HL */
    else if (horiz != NULL && lin != NULL)
    {
        intersection->y = horiz->b;
        line_calc_from_y(&intersection->x, lin, intersection->y);
        return LINE_INTERSECT_POINT;
    }

    return LINE_INTERSECT_NOT;
}
// y = ax+b