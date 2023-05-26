#include "state.h"

// Actually create the state for the game to run in
State CreateState()
{
	State result;

	IMG_Init(IMG_INIT_PNG);	
	SDL_Init(SDL_INIT_EVERYTHING);

	result.ptr_window = SDL_CreateWindow("Metroidvania Jam", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, (SDL_RENDERER_ACCELERATED | SDL_WINDOW_RESIZABLE));

	result.ptr_renderer = SDL_CreateRenderer(result.ptr_window, -1, 0);

	SDL_RenderSetLogicalSize(result.ptr_renderer, 320,240);

	result.isDone = false;

	return result;
}

// For computer platforms, the web build will use something else
void HandleStateEvents(State &state)
{
	while(SDL_PollEvent(&state.event))
	{
		switch(state.event.type)
		{
			case SDL_QUIT:
				state.isDone = true;
				break;
		}
	}
}

void StartDrawState(State &state)
{
	SDL_SetRenderDrawColor(state.ptr_renderer, 0, 0, 0, 255);
	SDL_RenderClear(state.ptr_renderer);
}

void EndDrawState(State &state)
{
	SDL_RenderPresent(state.ptr_renderer);
}

void DestroyState(State &state)
{
	SDL_DestroyRenderer(state.ptr_renderer);
	SDL_DestroyWindow(state.ptr_window);
	IMG_Quit();
	SDL_Quit();
}