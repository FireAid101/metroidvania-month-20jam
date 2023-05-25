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

	ptr_game->tileMap = LoadTileMap("rsrc/maps/testmap.map", &ptr_game->gameState);
	
	ptr_game->camera.x = 0;
	ptr_game->camera.y = 0;
}

void UnloadGame(Game *ptr_game)
{
	UnloadTileMap(&ptr_game->tileMap);
    UnloadTexture(&ptr_game->test_texture);
	DestroyState(&ptr_game->gameState);
}

void UpdateGame(Game *ptr_game, float deltaTime)
{
	ptr_game->test_rect.x += deltaTime * 20.0f;
	ptr_game->test_rect.y += deltaTime * 20.0f;

	HandleCamera(&ptr_game->camera);
}

void DrawGame(Game *ptr_game)
{
    StartDrawState(&ptr_game->gameState);
    
    SDL_SetRenderDrawColor(ptr_game->gameState.ptr_renderer, 0, 255, 0, 255);

	DrawMap(ptr_game->tileMap, &ptr_game->gameState, &ptr_game->camera);

    EndDrawState(&ptr_game->gameState);
}