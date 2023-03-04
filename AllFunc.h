#ifndef ALLFUNC_H_
#define ALLFUNC_H_

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
static SDL_Window* gameWindow = NULL;
static SDL_Renderer* gameRenderer = NULL;
static SDL_Event gameEvent;



//screen
const int FRAME_PER_SECOND = 40;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int colorkeyR = 167;
const int colorkeyG = 175;
const int colorkeyB = 180;


const int RenderColor = 0Xff;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define max_map_hor 400
#define max_map_ver 10

typedef struct Input //xu li input di chuyen nvat
{
    int left_, right_, up_, down_, jump_;

};


typedef struct gMAP
{
    int start_x, start_y, max_x, max_y;

    int tile[max_map_ver][max_map_hor];
    char* file_name;

};

#endif
