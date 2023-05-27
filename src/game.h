#ifndef GAME_H
#define GAME_H

#include "engine/state.h"
#include "engine/graphics.h"
#include "map.h"
#include "player.h"

struct Game 
{
    State gameState;

    Player player;

    Camera camera;
    TileMap tileMap;
};

void LoadGame(Game &game);
void UnloadGame(Game &game);
void UpdateGame(Game &game, float deltaTime);
void DrawGame(Game &game);

#endif