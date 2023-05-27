#include "game.h"

int main(int argc, char **argv)
{
	Game game;

	LoadGame(game);

	while (!game.gameState.isDone)
	{
		HandleStateEvents(game.gameState);

		UpdateGame(game);

		DrawGame(game);

		SDL_Delay(1000/60);
	}

	UnloadGame(game);
	return 0;
}
