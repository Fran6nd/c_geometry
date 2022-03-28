#include <stdio.h>
#include <SDL2/SDL.h>
#include "geometry.h"
#include "draw.h"
#include <unistd.h>

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
    triangle tri[] = {
        {.points = {{50,50}, {150,150}, {150,50}}},
        {.points = {{300,300}, {400,400}, {300,400}}},
        {.points = {{25,300}, {60,400}, {25,400}}},
        {.points = {{center.x + 30,center.y + 30},{center.x + 90,center.y + 90},{center.x + 30,center.y + 90}}},
        
     //   {.points = {{50,50}, {150,150}, {150,50}}},
     //   {.points = {{50,50}, {150,150}, {150,50}}},
    };
    double theta = 25;
    vector vct = vector_new(0, 1000);
    int paused = 0;
    while (1)
    {
        if (!paused)
        {
            theta += 5;
            sleep(1);
        }

        //theta = 90;
        vct = vector_set_arg(vct, theta);
        // Break out of the loop on quit
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
        SEGMENT_DRAW(SEGMENT_FROM_VECT(center, vct));

        //VECTOR_DRAW(center, vector_new(25, 25));
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < sizeof(tri) / sizeof(tri[0]); i++)
        {
            triangle_draw(renderer, &tri[i]);
        }
        for (int i = 0; i < sizeof(tri) / sizeof(tri[0]); i++)
        {
            ray s = ray_new(center, vct, 0);
            raycast_hit si = raycast_triangle(&s, &tri[i] );
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            draw_raycast_hit(renderer, si);

        }
        SDL_RenderPresent(renderer);
        // Get the next event
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {

                break;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                paused = !paused;
            }
        }
    }

    SDL_DestroyWindow(screen);
    SDL_Quit();
    return 0;
}