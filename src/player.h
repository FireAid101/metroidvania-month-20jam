#ifndef PLAYER_H
#define PLAYER_H

#include "engine/state.h" 
#include "engine/graphics.h"
#include "engine/phy_body.h"
#include "map.h"

#include <SDL2/SDL_rect.h>

struct Player
{
    //Texture playerTexture;
    SDL_FRect playerCol;  
    float vX = 0, vY = 0;
    bool trigger = false, jump = false, fall = true, ready = false, letGo = false;
};

Player LoadPlayer(State &state);
void UnloadPlayer(Player &player);
void DrawPlayer(Player &player, State &state, Camera camera);
void UpdatePlayer(Player &player, Camera &camera, TileMap map);

#endif 