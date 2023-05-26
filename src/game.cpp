#include "game.h"

void LoadGame(Game &game)
{
	State state = CreateState();
	game.gameState = state;
    
	game.test_rect.x = 0.0f;
	game.test_rect.y = 0.0f;
	game.test_rect.w = 100.0f;
	game.test_rect.h = 100.0f;
	
 	game.test_texture = LoadTexture("rsrc/img/test.png", game.gameState);    

	game.tileMap = LoadTileMap("rsrc/maps/testmap.map", game.gameState);
	
	game.camera.x = 0;
	game.camera.y = 0;
}

void UnloadGame(Game &game)
{
	UnloadTileMap(game.tileMap);
    UnloadTexture(game.test_texture);
	DestroyState(game.gameState);
}

void UpdateGame(Game &game, float deltaTime)
{
	game.test_rect.x += deltaTime * 20.0f;
	game.test_rect.y += deltaTime * 20.0f;

	HandleCamera(game.camera);
}

void DrawGame(Game &game)
{
    StartDrawState(game.gameState);
    
    SDL_SetRenderDrawColor(game.gameState.ptr_renderer, 0, 255, 0, 255);

	DrawMap(game.tileMap, game.gameState, game.camera);

    EndDrawState(game.gameState);
}