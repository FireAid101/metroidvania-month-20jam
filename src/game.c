#include "game.h"

void LoadGame(Game *ptr_game)
{
	State state = CreateState();
	ptr_game->gameState = state;
    
	ptr_game->test_rect.x = 0.0f;
	ptr_game->test_rect.y = 0.0f;
	ptr_game->test_rect.w = 100.0f;
	ptr_game->test_rect.h = 100.0f;

	ptr_game->test_texture = LoadTexture("rsrc/img/test.png", &ptr_game->gameState);    
}

void UnloadGame(Game *ptr_game)
{
    UnloadTexture(&ptr_game->test_texture);
	DestroyState(&ptr_game->gameState);
}

void UpdateGame(Game *ptr_game, float deltaTime)
{
	ptr_game->test_rect.x += deltaTime * 20.0f;
	ptr_game->test_rect.y += deltaTime * 20.0f;
}

void DrawGame(Game *ptr_game)
{
    StartDrawState(&ptr_game->gameState);
    
    SDL_SetRenderDrawColor(ptr_game->gameState.ptr_renderer, 0, 255, 0, 255);
	SDL_RenderCopyF(ptr_game->gameState.ptr_renderer, ptr_game->test_texture.ptr_data, NULL, &ptr_game->test_rect);

    EndDrawState(&ptr_game->gameState);
}