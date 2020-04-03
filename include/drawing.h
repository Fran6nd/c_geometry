#ifndef DRAWING_h
#define DRAWING_h

#include <SDL2/SDL.h>
#include "components.h"
void load_resources(SDL_Renderer *r);
void free_resources();

void tank_draw(SDL_Renderer *r, struct tank *t);
#endif