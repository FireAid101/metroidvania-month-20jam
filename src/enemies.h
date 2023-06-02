#ifndef ENEMIES_H
#define ENEMIES_H

#include "player.h"

struct Enemy
{
    SDL_FRect enemyCol;
    float vX = 0, vY = 0;
    bool jump = false, fall = true, ready = false;
};

bool IsEnemyVisible(Enemy enemy, Camera camera);
Enemy LoadEnemy(State &state);
void UnloadEnemy(Enemy &enemy);
void DrawEnemy(Enemy &enemy, State &state, Camera camera);
void UpdateEnemy(Enemy &enemy, Camera &camera, TileMap map, Player &player);

#endif