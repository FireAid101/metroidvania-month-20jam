#ifndef STATE_H
#define STATE_H


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// Hold all data about the window
struct State
{
	SDL_Window *ptr_window;
	SDL_Renderer *ptr_renderer;
	SDL_Event event;
	bool isDone;
};

State CreateState();
void HandleStateEvents(State &state);
void StartDrawState(State &state);
void EndDrawState(State &state);
void DestroyState(State &state);

#endif