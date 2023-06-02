#ifndef ITEMS_H
#define ITEMS_H

#include "engine/state.h"
#include "engine/graphics.h"
#include "map.h"
#include "player.h"

enum EItemType
{
    itemHealth,
};

struct Item
{
    EItemType itemType;
    SDL_FRect col;
};

Item LoadItem(EItemType itemType, State &state, int gridX, int gridY);
void UnloadItem(Item &item);
void UpdateItem(Item &item, Player &player, Camera camera);
void DrawItem(Item &item, State &state, Camera camera);

#endif