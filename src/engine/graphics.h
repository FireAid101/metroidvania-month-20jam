#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "state.h"
#include <string>
#include <iostream>

struct Texture 
{
    SDL_Texture *ptr_data;
    int width, height;
}; 

Texture LoadTexture(std::string path, State &state);
void UnloadTexture(Texture &texture);

#endif 