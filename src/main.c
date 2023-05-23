#include "game.h"

int main(int argc, char **argv)
{
	Game game;

	float currentTime = 0, lastTime = 0, deltaTime = 0;

	LoadGame(&game);

	while (!game.gameState.isDone)
	{
		// Update time
		lastTime = currentTime;
		
		HandleStateEvents(&game.gameState);

		UpdateGame(&game, deltaTime);

		DrawGame(&game);

		// Finish up framerate stuff
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - lastTime) / 1000.0f;
	}

	UnloadGame(&game);
	return 0;
}
