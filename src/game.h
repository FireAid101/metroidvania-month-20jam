#ifndef GAME_H
#define GAME_H

#include "engine/state.h"
#include "engine/graphics.h"
#include "map.h"

struct Game 
{
    State gameState;

    Texture test_texture;
    Camera camera;
    SDL_FRect test_rect;
    TileMap tileMap;
};

void LoadGame(Game &game);
void UnloadGame(Game &game);
void UpdateGame(Game &game, float deltaTime);
void DrawGame(Game &game);

#endif