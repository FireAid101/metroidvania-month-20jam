#include "enemies.h"

bool IsEnemyVisible(Enemy enemy, Camera camera)
{
    return enemy.enemyCol.x + enemy.enemyCol.w > camera.x - 30 && 
        enemy.enemyCol.x + enemy.enemyCol.w < camera.x + 350 && 
        enemy.enemyCol.y + enemy.enemyCol.h > camera.y - 30 &&
        enemy.enemyCol.y + enemy.enemyCol.h < camera.y + 270;
}

Enemy LoadEnemy(State &state)
{
    Enemy result;

    result.enemyCol.x = 3 * 16;
    result.enemyCol.y = 2 * 16;
    result.enemyCol.w = 12;
    result.enemyCol.h = 14;

    return result;
}

void UnloadEnemy(Enemy &enemy)
{
    // ? will use when need be
}

void DrawEnemy(Enemy &enemy, State &state, Camera camera)
{
    if (IsEnemyVisible(enemy, camera) == true)
    {
        SDL_SetRenderDrawColor(state.ptr_renderer, 200, 0, 0, 255);

        SDL_FRect dst;
        dst.w = enemy.enemyCol.w;
        dst.h = enemy.enemyCol.h;
        dst.x = enemy.enemyCol.x + camera.dx;
        dst.y = enemy.enemyCol.y + camera.dy; 

        SDL_RenderFillRectF(state.ptr_renderer, &dst);
    }            
}

void UpdateEnemy(Enemy &enemy, Camera &camera, TileMap map)
{
    if (IsEnemyVisible(enemy, camera) == true)
    {

    
    if (enemy.fall == true)
    {
        enemy.vY += 0.2f;

        if (enemy.vY > 4.0f)
        {
            enemy.vY = 4.0f;
        }
    }

    enemy.vX += 0.2f;

    if (enemy.vX > 1.0f)
    {
        enemy.vX = 1.0f;
    }
    else if (enemy.vX < -1.0f)
    {
        enemy.vX = -1.0f;
    }

    for (int y = -5; y < 5; y++)
    {
        for (int x = -5; x < 5; x++)
        {
            int location = (round(enemy.enemyCol.y / 16) * map.width) + (y * map.width) + round(enemy.enemyCol.x / 16) + x;

            SDL_FRect rect1, rect2;

            rect1 = enemy.enemyCol;                 

            if (map.isSolid[location] == true)
            {
                rect2.x = map.dst_rects[location].x;
                rect2.y = map.dst_rects[location].y;
                rect2.w = map.dst_rects[location].w;
                rect2.h = map.dst_rects[location].h; 
                CollisionResults colRes = HandleCollisions(rect1, rect2, enemy.vX, enemy.vY);
            }
        }
    }

    enemy.enemyCol.x += enemy.vX;
    enemy.enemyCol.y += enemy.vY;
    }   
}
