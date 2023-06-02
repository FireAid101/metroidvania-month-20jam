#include "items.h"

Item LoadItem(EItemType itemType, State &state, int gridX, int gridY)
{
    Item result;

    switch (itemType)
    {
        case itemHealth:
            result.col.x = (gridX * 16) + 8;
            result.col.y = (gridY * 16) + 8; 
            result.col.w = 8;
            result.col.h = 8;
            break;
    }

    result.itemType = itemType;
    return result;
}

void UnloadItem(Item &item)
{

}

void UpdateItem(Item &item, Player &player, Camera camera)
{
    if (IsEntityVisible(item.col, camera) == true)
    {
        switch(item.itemType)
        {
            case itemHealth:
                SDL_Rect itemRect, playerRect;

                itemRect.x = item.col.x;
                itemRect.y = item.col.y;
                itemRect.w = item.col.w;
                itemRect.h = item.col.h;

                playerRect.x = player.playerCol.x; 
                playerRect.y = player.playerCol.y; 
                playerRect.w = player.playerCol.w; 
                playerRect.h = player.playerCol.h; 

                if (SDL_HasIntersection(&itemRect, &playerRect) == SDL_TRUE)
                {
                    if (player.health < player.max_health)
                    {
                        player.health += 1;
                        player.hit = true;
                        player.oppVx = -player.vX;
                        player.oppVy = -player.vY;
                    }
                }
                break;
        }    
    } 
}

void DrawItem(Item &item, State &state, Camera camera)
{
    if (IsEntityVisible(item.col, camera))
    {
        switch(item.itemType)
        {
            case itemHealth:
            SDL_SetRenderDrawColor(state.ptr_renderer, 255, 0, 0, 255);
                    
            SDL_FRect dst;
            dst.w = item.col.w;
            dst.h = item.col.h;
            dst.x = item.col.x + camera.dx;
            dst.y = item.col.y + camera.dy;

            SDL_RenderFillRectF(state.ptr_renderer, &dst); 
            break;
        }
   }
}