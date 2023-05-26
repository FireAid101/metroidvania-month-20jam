#ifndef TILES_H
#define TILES_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "engine/state.h"
#include "engine/graphics.h"

/*
    How I want the game to work is 3  2D dimensional arrays: 1 for src rects, 1 for positioning rects and the last one for holding info about each tile 
*/

struct Camera 
{
    int dx, dy;
    int x, y;
};

void HandleCamera(Camera &camera);

// This data structure holds all the different tile options in a file that makes adding, removing and even editing tile properties easier 
struct TileInfo
{
    SDL_Rect src;
    bool isSolid;
};

// A grid of tiles in which the game is built on
struct TileMap 
{
    std::vector<TileInfo> mapTileInfo;
    int amountOfTiles;

    Texture mapTileSet;

    int width, height;
    std::vector<SDL_Rect> src_rects;
    std::vector<SDL_Rect> dst_rects;
    std::vector<bool> isSolid;
};

TileMap LoadTileMap(std::string path, State &state);
void UnloadTileMap(TileMap &tileMap);
void DrawMap(TileMap map, State &state, Camera &camera);
#endif