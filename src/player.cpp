#include "player.h"

Player LoadPlayer(State &state)
{
    Player result;
    result.playerCol.x = 2 * 16;
    result.playerCol.y = 2 * 16;
    result.playerCol.w = 16;
    result.playerCol.h = 16;   

    result.vX = 0;
    result.vY = 0;

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

void UpdatePlayer(Player &player, Camera &camera)
{
    // Get keyboard input
    bool movedX = false, movedY = false;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT])
    {
        movedX = true;
        player.vX -= 0.2f;

        if (player.vX < -2.0f)
        {
            player.vX = -2.0f;
        }
    }
    
    if(keys[SDL_SCANCODE_RIGHT])
    {
        movedX = true;
        player.vX += 0.2f;

        if (player.vX > 2.0f)
        {
            player.vX = 2.0f;
        }
    }
    
    if (keys[SDL_SCANCODE_UP])
    {
        movedY = true;
        player.vY -= 0.2f;

        if (player.vY < -2.0f)
        {
            player.vY = -2.0f;
        }
    }
    
    if (keys[SDL_SCANCODE_DOWN])
    {
        movedY = true;
        player.vY += 0.2f;

        if (player.vY > 2.0f)
        {
            player.vY = 2.0f;
        }
    }
    
    if (movedX == false)
    {
        if (player.vX < 0)
        {
            player.vX += 0.4f;

            if(player.vX >= 0)
            {
                player.vX = 0.0f;
            }
        }
        
        if (player.vX > 0)
        {
            player.vX -= 0.4f;

            if (player.vX <= 0)
            {
                player.vX = 0.0f;
            }
        }
    }

    if (movedY == false)
    {
        if (player.vY < 0)
        {
            player.vY += 0.4f;

            if (player.vX >= 0)
            {
                player.vX = 0.0f;
            }
        }
        
        if (player.vY > 0)
        {
            player.vY -= 0.4f;

            if (player.vY <= 0)
            {
                player.vY = 0.0f;
            }
        }
    }

    player.playerCol.x += player.vX;
    player.playerCol.y += player.vY;

    // If player reaches edges, then move the camera
    if (player.playerCol.x < camera.x + 50)
    {
        camera.x -= 2;
        camera.dx += 2;
    }
    else if (player.playerCol.x > camera.x + 270)
    {
        camera.x += 2;
        camera.dx -= 2;
    }

    if (player.playerCol.y < camera.y + 50)
    {
        camera.y -= 2;
        camera.dy += 2;
    }
    else if (player.playerCol.y > camera.y + 190)
    {
        camera.y += 2;
        camera.dy -= 2;
    }
}