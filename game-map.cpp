#include "game-map.h"
#include <iostream>



void GameMap::loadmap(char* nam)
{
    FILE* fp = NULL;
    fopen_s(&fp, nam, "rb");
    if (fp == NULL)
    {
        return;
    }

    game_map.max_x = 0;
    game_map.max_y = 0;
    for (int i = 0; i < max_map_ver; i++)
    {
        for (int j = 0; j < max_map_hor; j++)
        {
            fscanf(fp,"%d", &game_map.tile[i][j]);
            int val = game_map.tile[i][j];
            if ( val > 0)
            {
                if ( j > game_map.max_x)
                {
                    game_map.max_x = j;
                }
                if ( i > game_map.max_y)
                {
                    game_map.max_y = i;
                }
            }
        }
    }

    game_map.max_x = (game_map.max_x +1)*TILE_SIZE;
    game_map.max_y = (game_map.max_y + 1)*TILE_SIZE;

    game_map.start_x = 0;
    game_map.start_y = 0;

    game_map.file_name = nam;
    fclose(fp);

}

void GameMap::loadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    FILE* fp = NULL;

    for (int i = 0; i < TILEMAX; i++)
    {
        sprintf_s(file_img, "map/%d.png", i);

        fopen_s(&fp, file_img, "rb");
        if ( fp == NULL)
        {
            continue;
        }

        fclose(fp);

        tile_mat[i].LoadImg(file_img, screen);
    }
}

void GameMap::Drawmap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;


    int map_x = 0;
    int map_y = 0;

    map_x = game_map.start_x/TILE_SIZE;
    map_y = game_map.start_y/TILE_SIZE;
    x1 = (game_map.start_x%TILE_SIZE)*(-1);
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    y1 = (game_map.start_y%TILE_SIZE)*(-1);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i =y1; i < y2; i+=TILE_SIZE)
    {
        map_x = game_map.start_x/TILE_SIZE;
        for (int j = x1; j < x2; j+=TILE_SIZE)
        {
            int val = game_map.tile[map_y][map_x];
            if (val > 0)
            {
                tile_mat[val].SetRect(j, i);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }


}
