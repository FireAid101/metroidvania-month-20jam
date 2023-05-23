#include "graphics.h"

Texture LoadTexture(const char *path, State *state)
{
    Texture result;

    SDL_Surface *surf = NULL;

    surf = IMG_Load(strcat(SDL_GetBasePath(), path));

    if (surf == NULL)
    {
        printf("Error: File couldn't be loaded\n");
    }
   
    result.ptr_data = SDL_CreateTextureFromSurface(state->ptr_renderer, surf);

    SDL_FreeSurface(surf); 

    return result;    
}

void UnloadTexture(Texture *ptr_texture)
{
    SDL_DestroyTexture(ptr_texture->ptr_data);
}