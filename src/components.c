#include <SDL2/SDL.h>
#include "components.h"

#include "vector.h"
#include "triangle.h"

const int SPEED = 100;
const int ANGULAR_VELOCITY = 90;

struct tank tank_new(double x, double y, double rotation)
{
    struct tank t;
    t.transform = transform_new(x, y, rotation);
    vector ul, ur, dl, dr;
    ul.x = -25;
    ul.y = -25;
    ur.x = 25;
    ur.y = -25;
    dl.x = -25;
    dl.y = 25;
    dr.x = 25;
    dr.y = 25;
    t.hitbox[0] = triangle_new(&(t.transform), ul, ur, dl);
    t.hitbox[1] = triangle_new(&(t.transform), ur, dr, dl);
    return t;
}
void tank_update(struct tank *t, double dt)
{
    Uint8 *keystate = SDL_GetKeyboardState(NULL);

    //continuous-response keys
    vector speed = vector_zero();
    int angular_velocity = 0;
    if (keystate[SDL_SCANCODE_LEFT])
    {
        angular_velocity -= 90;
    }
    if (keystate[SDL_SCANCODE_RIGHT])
    {
        angular_velocity += 90;
    }
    if (keystate[SDL_SCANCODE_UP])
    {
        vector increment = vector_set_arg(vector_mul(vector_normalize(t->transform.position), 100), t->transform.rotation);

        vector_increment(&speed, &(increment));
    }
    if (keystate[SDL_SCANCODE_DOWN])
    {
        vector increment = vector_set_arg(vector_mul(vector_normalize(t->transform.position), 100), t->transform.rotation);
        vector_decrement(&speed, &(increment));
    }
    t->transform.velocity = speed;
    t->transform.angular_velocity = angular_velocity;
    transform_update(&t->transform, dt);
    triangle_update(&(t->hitbox[0]), &t->transform);
    triangle_update(&(t->hitbox[1]), &t->transform);
}