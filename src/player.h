#ifndef PLAYER_H
#define PLAYER_H

#include "engine/state.h" 
#include "engine/graphics.h"
#include "map.h"

struct Player
{
    //Texture playerTexture;
    SDL_Rect playerCol;    
};

Player LoadPlayer(State &state);
void UnloadPlayer(Player &player);
void DrawPlayer(Player &player, State &state, Camera camera);
void UpdatePlayer(Player &player, Camera &camera);

#endif 