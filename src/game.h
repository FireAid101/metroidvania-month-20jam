#ifndef GAME_H
#define GAME_H

#include "engine/state.h"
#include "engine/graphics.h"
#include "map.h"

typedef struct 
{
    State gameState;

    Texture test_texture;
    Camera camera;
    SDL_FRect test_rect;
    TileMap tileMap;
} Game;

void LoadGame(Game *ptr_game);
void UnloadGame(Game *ptr_game);
void UpdateGame(Game *ptr_game, float deltaTime);
void DrawGame(Game *ptr_game);

#endif