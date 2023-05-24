#ifndef TILES_H
#define TILES_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

/*
    How I want the game to work is 3  2D dimensional arrays: 1 for src rects, 1 for positioning rects and the last one for holding info about each tile 
*/

// This data structure holds all the different tile options in a file that makes adding, removing and even editing tile properties easier 
typedef struct
{
    SDL_Rect src;
    bool isSolid;
} TileInfo;

// A grid of tiles in which the game is built on
typedef struct 
{
    TileInfo *ptr_mapTileInfo;
    int amountOfTiles;

    Texture mapTileSet;

    int width, height;
    SDL_Rect **src_rects;
    SDL_Rect **dst_rects;
    bool **isSolid;
} TileMap;

TileMap LoadTileMap(char *ptr_mapPath);
void UnloadTileMap(TileMap *ptr_tileMap);
#endif