#include <SDL2/SDL.h>
#include "draw.h"
#include "geometry.h"

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius)
{
    for (int x1 = -radius; x1 <= radius; x1++)
    {
        for (int y1 = -radius; y1 <= radius; y1++)
        {
            if (x1 == -radius || y1 == -radius || x1 == radius || y1 == radius)
            {

                vector v = vector_new(x1, y1);
                v = vector_normalize(v);
                v = vector_mul(v, radius);
                SDL_RenderDrawPoint(renderer, (int)v.x + x, (int)v.y + y);
            }
        }
    }
}

void ray_draw(SDL_Renderer *renderer, ray r)
{
    SDL_RenderDrawLine(renderer, VECTOR_TO_INT(r.origin), VECTOR_TO_INT(vector_sum(r.dir, r.origin)));
    vector head = vector_sum(r.dir, r.origin);

    vector v1 = vector_normalize(r.dir);
    v1 = vector_set_module(v1, 20);
    double arg = vector_get_arg(v1);
    arg -= 45;
    v1 = vector_set_arg(v1, arg);
    SDL_RenderDrawLine(renderer, VECTOR_TO_INT(head), VECTOR_TO_INT(vector_sum(head, v1)));
    v1 = vector_normalize(r.dir);
    v1 = vector_set_module(v1, 20);
    arg = vector_get_arg(v1);
    arg += 45;
    v1 = vector_set_arg(v1, arg);
    SDL_RenderDrawLine(renderer, VECTOR_TO_INT(head), VECTOR_TO_INT(vector_sum(head, v1)));
}
void draw_arrow(SDL_Renderer *renderer, vector origin, vector head)
{
    if (origin.x != head.x || origin.y != head.y)
    {
        SDL_RenderDrawLine(renderer, VECTOR_TO_INT(origin), VECTOR_TO_INT(head));
        vector v1 = vector_normalize(vector_sub(head, origin));
        vector body = vector_sub(head, origin);
        double module = vector_get_module(body);
        v1 = vector_set_module(v1, module / 10);
        double arg = vector_get_arg(body);
        arg -= 135;
        v1 = vector_set_arg(v1, arg);
        SDL_RenderDrawLine(renderer, VECTOR_TO_INT(head), VECTOR_TO_INT(vector_sum(head, v1)));
        v1 = vector_normalize(body);
        v1 = vector_set_module(v1, module / 10);
        arg = vector_get_arg(body);
        arg += 135;
        v1 = vector_set_arg(v1, arg);
        SDL_RenderDrawLine(renderer, VECTOR_TO_INT(head), VECTOR_TO_INT(vector_sum(head, v1)));
    }
}
void draw_intersection(SDL_Renderer *renderer, intersection i)
{
    switch (i.type)
    {
    case INTERSECTION_POINT:
        draw_circle(renderer, VECTOR_TO_INT(i.p), 5);
        //draw_arrow(renderer, i.p, vector_sum(i.p, i.normal));
        break;
    case INTERSECTION_SEGMENT:
        draw_circle(renderer, VECTOR_TO_INT(i.s.p1), 5);
        draw_circle(renderer, VECTOR_TO_INT(i.s.p2), 5);
        break;
    default:
        break;
    }
}

void draw_raycast_hit(SDL_Renderer *renderer, raycast_hit i)
{
    switch (i.type)
    {
    case INTERSECTION_POINT:
        draw_circle(renderer, VECTOR_TO_INT(i.p), 5);

        draw_arrow(renderer, i.p, vector_sum(i.p, vector_set_module(i.normal, 30)));
        vector head = vector_sum(i.p, vector_set_module(i.reflected, 20));
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        draw_arrow(renderer, i.p, head);
        break;
    default:
        break;
    }
}
void triangle_draw(SDL_Renderer * renderer, triangle * t){
    for(int i = 0; i < 3; i++){
        segment s = triangle_get_segment_at(t, i);
        SEGMENT_DRAW(s);
    }
}