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
void HandleStateEvents(State *ptr_state)
{
	while(SDL_PollEvent(&ptr_state->event))
	{
		switch(ptr_state->event.type)
		{
			case SDL_QUIT:
				ptr_state->isDone = true;
				break;
		}
	}
}

void StartDrawState(State *ptr_state)
{
	SDL_SetRenderDrawColor(ptr_state->ptr_renderer, 0, 0, 0, 255);
	SDL_RenderClear(ptr_state->ptr_renderer);
}

void EndDrawState(State *ptr_state)
{
	SDL_RenderPresent(ptr_state->ptr_renderer);
}

void DestroyState(State *ptr_state)
{
	SDL_DestroyRenderer(ptr_state->ptr_renderer);
	SDL_DestroyWindow(ptr_state->ptr_window);
	IMG_Quit();
	SDL_Quit();
}