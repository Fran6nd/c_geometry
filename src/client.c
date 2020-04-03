#include <SDL2/SDL.h>
#include <sys/time.h>

#include "components.h"
#include "drawing.h"

int main(int argc, char **argv)
{
    int quit = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("SDL2 Displaying Image",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    /* Clear the entire screen to our selected color. */

    load_resources(renderer);
    struct tank t = tank_new(100, 100, 0);
    Uint32 t1 = SDL_GetTicks();
    Uint32 t2 = SDL_GetTicks();
    while (!quit)
    {
        t2 = SDL_GetTicks();
        double dt = (double)t2 - t1;
        dt = dt / 1000;
        t1 = t2;

        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        tank_update(&t, dt);
        tank_draw(renderer, &t);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free_resources();

    SDL_Quit();

    return 0;
}