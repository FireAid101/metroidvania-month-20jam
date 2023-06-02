#ifndef ITEMS_H
#define ITEMS_H

#include "engine/state.h"
#include "engine/graphics.h"

enum EItemType
{
    itemHealth,
};

struct Item
{
    EItemType itemType;
    SDL_FRect col;
};

#endif