#include "game.h"

void LoadGame(Game &game)
{
	State state = CreateState();
	game.gameState = state;
    
	game.tileMap = LoadTileMap("rsrc/maps/testmap.map", game.gameState);
	
	game.player = LoadPlayer(game.gameState);

	game.camera.x = 0;
	game.camera.y = 0;
}

void UnloadGame(Game &game)
{
	UnloadPlayer(game.player);
	UnloadTileMap(game.tileMap);
	DestroyState(game.gameState);
}

void UpdateGame(Game &game, float deltaTime)
{
	UpdatePlayer(game.player, deltaTime, game.camera);
}

void DrawGame(Game &game)
{
    StartDrawState(game.gameState);
    	
	DrawMap(game.tileMap, game.gameState, game.camera);

	DrawPlayer(game.player, game.gameState, game.camera);
 
    EndDrawState(game.gameState);
}