#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>

#include "geometry.h"


#define VECTOR_TO_INT(VECT) (int)VECT.x, (int)VECT.y
#define VECTOR_DRAW(POS, DIR) SDL_RenderDrawLine(renderer, VECTOR_TO_INT(POS), VECTOR_TO_INT(vector_sum(DIR, POS)));
#define SEGMENT_DRAW(s) SDL_RenderDrawLine(renderer, VECTOR_TO_INT(s.p1), VECTOR_TO_INT(s.p2));
#define SEGMENT_FROM_VECT(pos, dir) segment_new(pos, vector_sum(pos, dir))

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius);
void ray_draw(SDL_Renderer * renderer, ray r);
void draw_arrow(SDL_Renderer * renderer, vector origin, vector head);
void draw_intersection(SDL_Renderer * renderer, intersection i);
void draw_raycast_hit(SDL_Renderer * renderer, raycast_hit i);

#endif