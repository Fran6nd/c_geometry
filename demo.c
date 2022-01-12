#include <stdio.h>
#include <SDL2/SDL.h>
#include "vector.h"
#include "line.h"

#define VECTOR_TO_INT(VECT) (int)VECT.x, (int) VECT.y
//#define VECTOR_DRAW(POS, DIR) SDL_RenderDrawLine(renderer, VECTOR_TO_INT(POS), VECTOR_TO_INT(DIR));

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *screen = SDL_CreateWindow("My application",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          0);
    if (!screen)
    {
        fprintf(stderr, "Could not create window\n");
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer)
    {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    vector center = vector_new(320, 240);

    while (1)
    {
        // Break out of the loop on quit
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, VECTOR_TO_INT(center), 100, 100);
        SDL_RenderPresent(renderer);
        // Get the next event
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {

                break;
            }
        }
    }

    SDL_DestroyWindow(screen);
    SDL_Quit();
    return 0;
}