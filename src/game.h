#ifndef GAME_H
#define GAME_H

#include "engine/state.h"
#include "engine/graphics.h"

typedef struct 
{
    State gameState;

    Texture test_texture;
    SDL_FRect test_rect;
} Game;

void LoadGame(Game *ptr_game);
void UnloadGame(Game *ptr_game);
void UpdateGame(Game *ptr_game, float deltaTime);
void DrawGame(Game *ptr_game);

#endif