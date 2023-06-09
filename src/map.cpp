#include "map.h"

bool IsEntityVisible(SDL_FRect entRect, Camera camera)
{
     return entRect.x + entRect.w > camera.x - 30 && 
        entRect.x + entRect.w < camera.x + 350 && 
        entRect.y + entRect.h > camera.y - 30 &&
        entRect.y + entRect.h < camera.y + 270;
}

// Creates and loads the whole tilemap
TileMap LoadTileMap(std::string path, State &state)
{
    TileMap result;
    result.amountOfTiles = 0;

    // Load the tileset
    result.mapTileSet = LoadTexture("rsrc/img/testTileset.png", state);

    // First load the tilemap info
    std::string finalPath = SDL_GetBasePath();
    finalPath += "rsrc/data/tmi.inf";

    std::ifstream tileMapInfoFile;

    tileMapInfoFile.open(finalPath.c_str());

    if (tileMapInfoFile.fail() != true)
    {
        result.amountOfTiles = 0;

        while (!tileMapInfoFile.eof())
        {
            std::string line;

            std::getline(tileMapInfoFile, line);

            int spacePositions[4];
            int index = 0;
            
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == ' ')
                {
                    spacePositions[index] = i;
                    index++;
                }
            }

            int number;
            
            TileInfo info;

            number = std::atoi(line.substr(0, spacePositions[0]).c_str());            
            info.src.x = number;

            number = std::atoi(line.substr(spacePositions[0] + 1, spacePositions[1] - spacePositions[0]).c_str());            
            info.src.y = number;

            number = std::atoi(line.substr(spacePositions[1] + 1, spacePositions[2] - spacePositions[1]).c_str());
            info.src.w = number;

            number = std::atoi(line.substr(spacePositions[2] + 1, spacePositions[3] - spacePositions[2]).c_str());
            info.src.h = number;   

            if (line[line.length() - 1] == 't')
            {
                info.isSolid = true;
            }
            else if (line[line.length() - 1] == 'f')
            {
                info.isSolid = false;
            }
            result.mapTileInfo.push_back(info);
            result.amountOfTiles++;
        } 
    }
    else
    {
        std::cout << "Couldn't locate TileMapInfo file" << std::endl;
    }

    tileMapInfoFile.close();

    finalPath = SDL_GetBasePath();
    finalPath += path;

    std::ifstream mapFile;
    mapFile.open(finalPath.c_str());

    if (mapFile.fail() != true)
    {      
        std::string line;

        std::getline(mapFile, line);
         
        result.width = atoi(line.c_str());

        std::getline(mapFile, line);
        result.height = atoi(line.c_str());

        for (int y = 0; y < result.height; y++)
        {
            std::string newLine;

            std::getline(mapFile, newLine);

            // Loop through all tiles
            for (int x = 0; x < result.width; x++)
            {
                char c = newLine[x * 2];
                int index = c - '0';

                SDL_Rect src;
                SDL_Rect dst;
                bool isSolid;

                // Set position
                dst.w = 16;
                dst.h = 16;
                dst.x = 16 * x;
                dst.y = 16 * y;

                // Use of dynamic loading system with that tile infomation file - gonna save me a lot of time
                src = result.mapTileInfo[index].src;
                isSolid = result.mapTileInfo[index].isSolid;

                result.dst_rects.push_back(dst);
                result.src_rects.push_back(src);
                result.isSolid.push_back(isSolid);
            }
        }
    }
    else
    {
        std::cout << "Error: map couldn't be loaded at " << path << std::endl;
    }

    mapFile.close();
    return result;
}

void DrawMap(TileMap map, State &state, Camera &camera)
{
    for (int y = 0; y < 16; y++)
    {
        for(int x = 0; x < 21; x++)
        {
            // Get the location in the array by using simple grid map calculations
            int location = ((camera.y / 16) * map.width) + (y * map.width) + (camera.x / 16) + x;
            
            // Check to see if any tiles are even at that index
            if (location < map.dst_rects.size())
            {
                SDL_Rect rct = map.dst_rects[location];

                // Append camera movement   
                rct.x += camera.dx;
                rct.y += camera.dy;
            
                SDL_RenderCopy(state.ptr_renderer, map.mapTileSet.ptr_data, &map.src_rects[location], &rct);
            }
        }
    }
}

void UnloadTileMap(TileMap &tileMap)
{
    UnloadTexture(tileMap.mapTileSet);
}