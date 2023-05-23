#include "graphics.h"

Texture LoadTexture(const char *path, State *state)
{
    Texture result;

    SDL_Surface *surf;

    int size = strlen(SDL_GetBasePath()) + strlen(path);

    char *finalpath = malloc(size * sizeof(char));
    finalpath = strcpy(finalpath, SDL_GetBasePath());
    finalpath = strcat(finalpath, path);

    surf = IMG_Load(finalpath);

    free(finalpath);

    if (surf == NULL)
    {
        printf("Error: File couldn't be loaded\n");
        result.ptr_data = NULL;
        return result;
    }
   
    result.ptr_data = SDL_CreateTextureFromSurface(state->ptr_renderer, surf);

    SDL_FreeSurface(surf); 

    return result;    
}

void UnloadTexture(Texture *ptr_texture)
{
    SDL_DestroyTexture(ptr_texture->ptr_data);
}