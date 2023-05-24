#include "map.h"

// Creates and loads the whole tilemap
TileMap LoadTileMap(char *ptr_mapPath)
{
    TileMap result;
    result.amountOfTiles = 0;

    // First load the tilemap info
    char *path = malloc(strlen(SDL_GetBasePath()) + strlen("rsrc/data/tmi.inf"));
    path = strcpy(path, SDL_GetBasePath());
    path = strcat(path, "rsrc/data/tmi.inf");

    FILE *fptr_tileMapInfo = fopen(path, "r");

    if (fptr_tileMapInfo != NULL)
    {
        // Get amount of lines in a file
        int lines = 0;
        while (!feof(fptr_tileMapInfo))
        {
            char line[30];
            fgets(line, 30, fptr_tileMapInfo);
            lines++;
        }

        result.amountOfTiles = lines;

        // Load all different types of tiles dynamically;
        result.ptr_mapTileInfo = malloc(lines * sizeof(TileInfo));
        // Actual reading
        rewind(fptr_tileMapInfo);
        // Get actual data

        int globalIndex = 0;
        while (!feof(fptr_tileMapInfo))
        {
            char line[30];

            fgets(line, 30, fptr_tileMapInfo);

            int spacePositions[4];
            int index = 0;
            
            for (int i = 0; i < strlen(line); i++)
            {
                if (line[i] == ' ')
                {
                    spacePositions[index] = i;
                    index++;
                }
            }

            char number[4];
            int offset = 0;

            strncpy(number, line, spacePositions[0]);
            result.ptr_mapTileInfo[globalIndex].src.x = atoi(number);

            strcpy(number, "   ");
            strncpy(number, line + spacePositions[0] + 1, spacePositions[1] - spacePositions[0]);
            result.ptr_mapTileInfo[globalIndex].src.y = atoi(number);

            strcpy(number, "   ");
            strncpy(number, line + spacePositions[1] + 1, spacePositions[2] - spacePositions[1]);
            result.ptr_mapTileInfo[globalIndex].src.w = atoi(number);

            strcpy(number, "   ");
            strncpy(number, line + spacePositions[2] + 1, spacePositions[3] - spacePositions[2]);
            result.ptr_mapTileInfo[globalIndex].src.h = atoi(number);   

            if (line[strlen(line) - 1] == 't')
            {
                result.ptr_mapTileInfo[globalIndex].isSolid = true;
            }
            else if (line[strlen(line) - 1] == 'f')
            {
                result.ptr_mapTileInfo[globalIndex].isSolid = false;
            }
            globalIndex++;
        } 
    }
    else
    {
        printf("Couldn't locate TileMapInfo file\n");
    }

   
    fclose(fptr_tileMapInfo);
    free(path);

    // Load the actual map
    path = malloc(strlen(SDL_GetBasePath()) + strlen(ptr_mapPath));
    path = strcpy(path, SDL_GetBasePath());
    path = strcat(path, ptr_mapPath);

    FILE *fptr_mapFile = fopen(path, "r");

    if (fptr_mapFile != NULL)
    {
        
    }
    else
    {
        printf("Error: map couldn't be loaded at %s\n", path);
    }

    fclose(fptr_mapFile);
    free(path);

    free(result.ptr_mapTileInfo);
    return result;
}

void UnloadTileMap(TileMap *ptr_tileMap)
{

}