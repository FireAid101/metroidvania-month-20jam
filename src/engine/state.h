#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


// Hold all data about the window
typedef struct
{
	SDL_Window *ptr_window;
	SDL_Renderer *ptr_renderer;
	SDL_Event event;
	bool isDone;
} State;

State CreateState();
void HandleStateEvents(State *ptr_state);
void StartDrawState(State *ptr_state);
void EndDrawState(State *ptr_state);
void DestroyState(State *ptr_state);


#endif
