#ifndef PHY_BODY_H
#define PHY_BODY_H

#include <SDL2/SDL.h>

struct CollisionResults
{
    bool left, right, top, bottom;
};

CollisionResults HandleCollisions(SDL_FRect rect1, SDL_FRect rect2, float &vX, float &vY);

#endif