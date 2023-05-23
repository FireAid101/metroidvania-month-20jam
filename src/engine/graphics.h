#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "state.h"
#include <string.h>
#include <stdio.h>

typedef struct 
{
    SDL_Texture *ptr_data;
    int width, height;
} Texture;

Texture LoadTexture(const char *path, State *state);
void UnloadTexture(Texture *ptr_texture);

#endif 