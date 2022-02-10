#include <stdio.h>
#include <SDL2/SDL.h>
#include "vector.h"
#include "geometry.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

/* Still interseting to see what macros can do! */
#define VECTOR_TO_INT(VECT) (int)VECT.x, (int)VECT.y
#define VECTOR_DRAW(POS, DIR) SDL_RenderDrawLine(renderer, VECTOR_TO_INT(POS), VECTOR_TO_INT(vector_sum(DIR, POS)));
#define SEGMENT_DRAW(s) SDL_RenderDrawLine(renderer, VECTOR_TO_INT(s.p1), VECTOR_TO_INT(s.p2));
#define SEGMENT_FROM_VECT(pos, dir) segment_new(pos, vector_sum(pos, dir))

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
    segment seg[] = {
        {.p1.x = 5, .p1.y = 5, .p2.x = center.x, .p2.y = 5},
        {.p1.x = 5, .p1.y = 5, .p2.x = center.x, .p2.y = 25},
        {.p1.x = 25, .p1.y = 25, .p2.x = 25, .p2.y = 300},
        {.p1.x = 60, .p1.y = 400, .p2.x = 500, .p2.y = 350},
        {.p1.x = 60, .p1.y = 400, .p2.x = 500, .p2.y = 400},
        {.p1.x = 60, .p1.y = center.y, .p2.x = 500, .p2.y = center.y},
        {.p1.x = center.x, .p1.y = 20, .p2.x = center.x, .p2.y = 60},
        {.p1.x = center.x + 100, .p1.y = center.y + 100, .p2.x = center.x + 200, .p2.y = center.y + 200},

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
        for (int i = 0; i < sizeof(seg) / sizeof(seg[0]); i++)
        {
            SEGMENT_DRAW(seg[i]);
        }
        for (int i = 0; i < sizeof(seg) / sizeof(seg[0]); i++)
        {
            segment s = SEGMENT_FROM_VECT(center, vct);
            intersection si = segment_intersect(&s, &seg[i] );
            //printf("%d\n", type);
            if (si.type == INTERSECTION_POINT)
            {
                draw_circle(renderer, VECTOR_TO_INT(si.p), 5);
            }
            else if (si.type == INTERSECTION_SEGMENT)
            {
                //o\n");
                //if (segment_contain_point(&s, &si.seg.p1))
                {
                  //  printf("%d %d\n", VECTOR_TO_INT(si.seg.p1));
                    draw_circle(renderer, VECTOR_TO_INT(si.s.p1), 5);
                }
                //if (segment_contain_point(&s, &si.seg.p2))
                {
                   // printf("%d %d\n", VECTOR_TO_INT(si.seg.p2));
                    draw_circle(renderer, VECTOR_TO_INT(si.s.p2), 5);
                }

            }
            else
            {
            }
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