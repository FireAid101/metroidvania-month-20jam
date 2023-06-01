#include "player.h"

Player LoadPlayer(State &state)
{
    Player result;
    result.playerCol.x = 2 * 16;
    result.playerCol.y = 2 * 16;
    result.playerCol.w = 12;
    result.playerCol.h = 14;   

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
    dst.w = player.playerCol.w;
    dst.h = player.playerCol.h;
    dst.x = player.playerCol.x + camera.dx;
    dst.y = player.playerCol.y + camera.dy; 

    SDL_RenderFillRectF(state.ptr_renderer, &dst);
}

void UpdatePlayer(Player &player, Camera &camera, TileMap map)
{
    // Get keyboard input
    bool movedX = false;
    float limit = 2.0f;

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
    
    if (keys[SDL_SCANCODE_RIGHT])
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

        if (player.trigger == false)
        {
            if (player.jump == false && player.ready == true)
            {
                player.jump = true;
                player.fall = false;
            }
            player.trigger = true;
        } 
    }
    else 
    {
        player.letGo = true;
        player.trigger = false;
        player.jump = false;
        player.ready = false;
        player.fall = true;
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


    if (player.fall == true)
    {
        player.vY += 0.2f;

        if (player.vY > 4.0f)
        {
            player.vY = 4.0f;
        }
    }

    if (player.jump == true)
    {
        player.vY -= 0.35f;

        if (player.vY < -2.9f)
        {
            player.vY = -2.9f;
            player.jump = false;
            player.fall = true;
            player.trigger = true;
            player.ready = false;
        }
    }

    // Handle collision detection
    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            int location = ((camera.y / 16) * map.width) + (y * map.width) + (camera.x / 16) + x;

            SDL_FRect rect1, rect2;
            rect1 = player.playerCol;
            
            if (map.isSolid[location] == true)
            {
                rect2.x = map.dst_rects[location].x;
                rect2.y = map.dst_rects[location].y;
                rect2.w = map.dst_rects[location].w;
                rect2.h = map.dst_rects[location].h;
                
                bool left = rect1.x + rect1.w + player.vX > rect2.x && rect1.x < rect2.x && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h;                
                bool right = rect1.x + player.vX < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x + rect2.w && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h;                
                bool top = rect1.y + rect1.h + player.vY > rect2.y && rect1.y < rect2.y && rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w;                
                bool bottom = rect1.y + player.vY < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y + rect2.h && rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w;               

                if ((player.vX > 0 && left == true) || (player.vX < 0 && right == true))
                {
                    player.vX = 0;
                }

                if ((player.vY > 0 && top == true) || (player.vY < 0 && bottom == true))
                {
                    player.vY = 0;
                } 

                if (rect1.y + rect1.h + 0.2f >= rect2.y && player.letGo == true && keys[SDL_SCANCODE_UP])
                {
                    player.trigger = false;
                }

                // Cases for jumping
                if (player.jump == true && bottom == true)
                {
                    player.jump = false;
                    player.fall = true;
                    player.ready = false;
                    player.letGo = false;
                }

                if (player.vY == 0 && top == true)
                {
                    player.ready = true;
                    player.jump = false;
                    player.fall = true;
                    player.letGo = false;
                }
            }
        }
    }

    // Update player position
    player.playerCol.x += player.vX;
    player.playerCol.y += player.vY;

    // If player reaches edges, then move the camera
    if (player.playerCol.x < camera.x + 120)
    {
        camera.x -= 2;
        camera.dx += 2;
    }
    else if (player.playerCol.x > camera.x + 200)
    {
        camera.x += 2;
        camera.dx -= 2;
    }

    if (player.playerCol.y < camera.y + 80)
    {
        camera.y -= 2;
        camera.dy += 2;
    }
    else if (player.playerCol.y > camera.y + 160)
    {
        camera.y += 4;
        camera.dy -= 4;
    }
}