#include "map.h"

// Camera Handle function -- DO NOT USE IN GAME - THIS IS JUST UNTIL I HAVE A PLAYER
void HandleCamera(Camera *ptr_camera)
{
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    if (key_state[SDL_SCANCODE_LEFT])
    {
        ptr_camera->x -= 5;
        ptr_camera->dx += 5;
    }

    if (key_state[SDL_SCANCODE_RIGHT])
    {
        ptr_camera->x += 5;
        ptr_camera->dx -= 5;        
    }
    
    if (key_state[SDL_SCANCODE_UP])
    {
        ptr_camera->y -= 5;
        ptr_camera->dy += 5;    
    }

    if (key_state[SDL_SCANCODE_DOWN])
    {
        ptr_camera->y += 5;
        ptr_camera->dy -= 5;    
    }
}

// Creates and loads the whole tilemap
TileMap LoadTileMap(char *ptr_mapPath, State *ptr_state)
{
    TileMap result;
    result.amountOfTiles = 0;

    // Load the tileset
    result.mapTileSet = LoadTexture("rsrc/img/testTileset.png", ptr_state);

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
        // Get map data
        char temp[30];

        // Get width and height on the first two lines
        
        fgets(temp, 30, fptr_mapFile);
        
        result.width = atoi(temp);

        fgets(temp, 30, fptr_mapFile);
        result.height = atoi(temp);

        // Now allocate the sizes to the map
        result.dst_rects = malloc(result.height);
        result.isSolid = malloc(result.height);
        result.src_rects = malloc(result.height);

        for (int i = 0; i < result.height; i++)
        {
            result.dst_rects[i] = malloc(result.width * sizeof(SDL_Rect));
            result.src_rects[i] = malloc(result.width * sizeof(SDL_Rect));
            result.isSolid[i] = malloc(result.width * sizeof(bool));
        }           

        for (int y = 0; y < result.height; y++)
        {
            char row[(result.width * 2) + 1];

            fgets(row, (result.width * 2) + 1, fptr_mapFile);

            // Loop through all tiles
            for (int x = 0; x < result.width; x++)
            {
                int index = atoi(&row[x * 2]);

                // Set position
                result.dst_rects[y][x].w = 16;
                result.dst_rects[y][x].h = 16;
                result.dst_rects[y][x].x = 16 * x;
                result.dst_rects[y][x].y = 16 * y;

                // Use of dynamic loading system with that tile infomation file - gonna save me a lot of time
                result.src_rects[y][x] = result.ptr_mapTileInfo[index].src;
                result.isSolid[y][x] = result.ptr_mapTileInfo[index].isSolid;
            }
        }
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

void DrawMap(TileMap map, State *ptr_state, Camera *ptr_camera)
{
    for (int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 25; x++)
        {
            if (&map.dst_rects[ptr_camera->y + y][ptr_camera->x + x] != NULL)
            {
                SDL_Rect rct = map.dst_rects[ptr_camera->y + y][ptr_camera->x + x];
               
                rct.x += ptr_camera->dx;
                rct.y += ptr_camera->dy;
            
                SDL_RenderCopy(ptr_state->ptr_renderer, map.mapTileSet.ptr_data, &map.src_rects[ptr_camera->y + y][ptr_camera->x + x], &rct);
            }
        }
    }
}

void UnloadTileMap(TileMap *ptr_tileMap)
{
    UnloadTexture(&ptr_tileMap->mapTileSet);

    free(ptr_tileMap->dst_rects);
    free(ptr_tileMap->src_rects);
    free(ptr_tileMap->isSolid);
}