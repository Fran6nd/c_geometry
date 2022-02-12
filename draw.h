#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>

#include "geometry.h"


#define VECTOR_TO_INT(VECT) (int)VECT.x, (int)VECT.y
#define VECTOR_DRAW(POS, DIR) SDL_RenderDrawLine(renderer, VECTOR_TO_INT(POS), VECTOR_TO_INT(vector_sum(DIR, POS)));
#define SEGMENT_DRAW(s) SDL_RenderDrawLine(renderer, VECTOR_TO_INT(s.p1), VECTOR_TO_INT(s.p2));
#define SEGMENT_FROM_VECT(pos, dir) segment_new(pos, vector_sum(pos, dir))

void ray_draw(SDL_Renderer * renderer, ray r){
    SDL_RenderDrawLine(renderer, VECTOR_TO_INT(r.origin), VECTOR_TO_INT(vector_sum(r.dir, r.origin)));
    vector head = vector_sum(r.dir, r.origin);
    
    vector v1 = vector_normalize(r.dir);
    v1 = vector_set_module(v1, 20);
    double arg = vector_get_arg(&v1);
    arg -= 45;
    v1 = vector_set_arg(v1, arg);
    SDL_RenderDrawLine(renderer, VECTOR_TO_INT(head), VECTOR_TO_INT(vector_sum(head, v1)));
    v1 = vector_normalize(r.dir);
    v1 = vector_set_module(v1, 20);
    arg = vector_get_arg(&v1);
    arg += 45;
    v1 = vector_set_arg(v1, arg);
    SDL_RenderDrawLine(renderer, VECTOR_TO_INT(head), VECTOR_TO_INT(vector_sum(head, v1)));

}

#endif