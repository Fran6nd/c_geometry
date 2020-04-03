#include <SDL2/SDL.h>

#include "components.h"

SDL_Texture *tank_img;
SDL_Rect tank_rect = {0, 0, 50, 50};

void load_resources(SDL_Renderer *r)
{
    SDL_Surface *img = SDL_LoadBMP("img/Tank.bmp");
    SDL_SetColorKey(img, 1, 0xff0000);
    tank_img = SDL_CreateTextureFromSurface(r, img);
    SDL_FreeSurface(img);
}
void free_resources()
{
    SDL_DestroyTexture(tank_img);
}

void triangle_draw(SDL_Renderer *r,Triangle *t){
    SDL_SetRenderDrawColor(r, 255, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(r, t->_p[0].x, t->_p[0].y, t->_p[1].x, t->_p[1].y);
    SDL_RenderDrawLine(r, t->_p[2].x, t->_p[2].y, t->_p[1].x, t->_p[1].y);
    SDL_RenderDrawLine(r, t->_p[2].x, t->_p[2].y, t->_p[0].x, t->_p[0].y);
}

void tank_draw(SDL_Renderer *r, struct tank *t)
{
    tank_rect.x = t->transform.position.x - 25;
    tank_rect.y = t->transform.position.y - 25;
    SDL_Point center = {25, 25};

    SDL_RenderCopyEx(r, tank_img, NULL, &tank_rect, t->transform.rotation - 90, &center, 0);
    triangle_draw(r, &t->hitbox[0]);
    triangle_draw(r, &t->hitbox[1]);

}