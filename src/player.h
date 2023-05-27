#ifndef PLAYER_H
#define PLAYER_H

#include "engine/state.h" 
#include "engine/graphics.h"
#include "map.h"

struct Player
{
    //Texture playerTexture;
    SDL_FRect playerCol;    
};

Player LoadPlayer(State &state);
void UnloadPlayer(Player &player);
void DrawPlayer(Player &player, State &state, Camera camera);
void UpdatePlayer(Player &player, float deltaTime, Camera &camera);

#endif 