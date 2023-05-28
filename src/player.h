#ifndef PLAYER_H
#define PLAYER_H

#include "engine/state.h" 
#include "engine/graphics.h"
#include "map.h"
#include <SDL2/SDL_rect.h>

struct Player
{
    //Texture playerTexture;
    SDL_FRect playerCol;  
    float vX, vY;
};

Player LoadPlayer(State &state);
void UnloadPlayer(Player &player);
void DrawPlayer(Player &player, State &state, Camera camera);
void UpdatePlayer(Player &player, Camera &camera, TileMap map);

#endif 