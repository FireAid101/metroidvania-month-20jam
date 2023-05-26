#include "graphics.h"

Texture LoadTexture(std::string path, State &state)
{
    Texture result;

    SDL_Surface *surf;

    std::string finalpath = SDL_GetBasePath();
    finalpath += path;

    surf = IMG_Load(finalpath.c_str());

    if (surf == NULL)
    {
        std::cout << "Error: File couldn't be loaded" << std::endl;
        result.ptr_data = NULL;
        return result;
    }
   
    result.ptr_data = SDL_CreateTextureFromSurface(state.ptr_renderer, surf);

    SDL_FreeSurface(surf); 

    return result;    
}

void UnloadTexture(Texture &texture)
{
    SDL_DestroyTexture(texture.ptr_data);
}