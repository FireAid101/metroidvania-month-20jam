#ifndef GAME_H
#define GAME_H

#include "engine/state.h"
#include "engine/graphics.h"
#include "map.h"
#include "player.h"
#include "enemies.h"

struct Game 
{
    State gameState;

    Player player;
    Enemy enemy;

    Camera camera;
    TileMap tileMap;
};

void LoadGame(Game &game);
void UnloadGame(Game &game);
void UpdateGame(Game &game);
void DrawGame(Game &game);

#endif