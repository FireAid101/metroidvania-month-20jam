#include "player.h"

Player LoadPlayer(State &state)
{
    Player result;
    result.playerCol.x = 2 * 16;
    result.playerCol.y = 2 * 16;
    result.playerCol.w = 16;
    result.playerCol.h = 16;   

    return result;
}

void UnloadPlayer(Player &player)
{
    //?
}

void DrawPlayer(Player &player, State &state, Camera camera)
{
    SDL_SetRenderDrawColor(state.ptr_renderer, 0, 200, 0, 255);

    SDL_FRect dst;
    dst.w = 16;
    dst.h = 16;
    dst.x = player.playerCol.x + camera.dx;
    dst.y = player.playerCol.y + camera.dy; 

    SDL_RenderFillRectF(state.ptr_renderer, &dst);
}

void UpdatePlayer(Player &player, float deltaTime, Camera &camera)
{
    // If player reaches edges, then move the camera
    if (player.playerCol.x < camera.x + 50)
    {
        camera.x -= 1;
        camera.dx += 1;
    }
    else if (player.playerCol.x > camera.x + 270)
    {
        camera.x += 1;
        camera.dx -= 1;
    }

    if (player.playerCol.y < camera.y + 50)
    {
        camera.y -= 1;
        camera.dy += 1;
    }
    else if (player.playerCol.y > camera.y + 190)
    {
        camera.y += 1;
        camera.dy -= 1;
    }

    // Get keyboard input

    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT])
    {
        player.playerCol.x -= 40.0f * deltaTime;
    }

    if (keys[SDL_SCANCODE_RIGHT])
    {
        player.playerCol.x += 40.0f * deltaTime;
    }
    
    if (keys[SDL_SCANCODE_UP])
    {
        player.playerCol.y -= 40.0f * deltaTime;
    }

    if (keys[SDL_SCANCODE_DOWN])
    {
        player.playerCol.y += 40.0f * deltaTime;
    }
}