#include "game.h"

void LoadGame(Game &game)
{
	State state = CreateState();
	game.gameState = state;
    
	game.tileMap = LoadTileMap("rsrc/maps/testmap.map", game.gameState);
	
	game.player = LoadPlayer(game.gameState);
	game.enemy = LoadEnemy(game.gameState);
	game.item = LoadItem(itemHealth, game.gameState, 5, 5);

	game.camera.x = 0;
	game.camera.y = 0;
	game.camera.dx = 0;
	game.camera.dy = 0;
}

void UnloadGame(Game &game)
{
	UnloadItem(game.item);
	UnloadEnemy(game.enemy);
	UnloadPlayer(game.player);
	UnloadTileMap(game.tileMap);
	DestroyState(game.gameState);
}

void UpdateGame(Game &game)
{
	UpdateItem(game.item, game.player, game.camera);
	UpdateEnemy(game.enemy, game.camera, game.tileMap, game.player);
	UpdatePlayer(game.player, game.camera, game.tileMap);
}

void DrawGame(Game &game)
{
    StartDrawState(game.gameState);
    	
	DrawMap(game.tileMap, game.gameState, game.camera);

	DrawItem(game.item, game.gameState, game.camera);
	DrawPlayer(game.player, game.gameState, game.camera);
	DrawEnemy(game.enemy, game.gameState, game.camera);

    EndDrawState(game.gameState);
}