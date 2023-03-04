#include <iostream>
#include "AllFunc.h"
#include "Spine.h"
#include "game-map.h"
#include "maincharacter.h"
#include "Timer.h"

Spine gameBackground;


bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0) // ham sdl init tra ve 0 neu success va tra ve negative error neu fail
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //sdl_hint_render  de check xem texture dc tao chua, va se anh huong
    // den cai scale cua texture sau nay

    gameWindow = SDL_CreateWindow("VOID GENOME",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
    if (gameWindow == NULL)
    {
        success = false;
    }
    else
    {
        gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gameRenderer == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(gameRenderer,
                                   RenderColor, RenderColor,
                                   RenderColor, RenderColor);
            int imgflag = IMG_INIT_PNG;
            if (!(IMG_Init(imgflag) && imgflag))
            {
                success = false;
            }
        }
    }
    return success;
}



bool LoadBackground()
{
    bool ret1 = gameBackground.LoadImg("layers//far.png", gameRenderer);

    if(ret1 == false )
        return false;


    return true;
}


void close()
{
    gameBackground.free();

    SDL_DestroyRenderer(gameRenderer);

    gameRenderer = NULL;

    SDL_DestroyWindow(gameWindow);
    gameWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    Timer fps_timer;

    if (InitData()==false)
        return -1;

    if(LoadBackground()==false)
        return -1;


    GameMap GAME_MAP;
    GAME_MAP.loadmap("map/map01.dat");
    GAME_MAP.loadTiles(gameRenderer);


    maincharacter p_player;
    p_player.LoadImg("layers//pp_right.png", gameRenderer);
    p_player.set_clips();

    bool is_quit = false;
    while (!is_quit)
    {
        fps_timer.start();
        while (SDL_PollEvent(&gameEvent) != 0)
        {
            if (gameEvent.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandleInputAction(gameEvent, gameRenderer);
        }

        SDL_SetRenderDrawColor(gameRenderer, RenderColor,
                               RenderColor, RenderColor, RenderColor);
        SDL_RenderClear(gameRenderer);

        gameBackground.Render(gameRenderer, NULL);
        GAME_MAP.Drawmap(gameRenderer);
        gMAP map_data = GAME_MAP.getMap();


        p_player.SetMapXY(map_data.start_x, map_data.start_y);
        p_player.DoPlayer(map_data);
        p_player.Show(gameRenderer);

        GAME_MAP.SetMap(map_data);
        GAME_MAP.Drawmap(gameRenderer);

        SDL_RenderPresent(gameRenderer);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //mili giay

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0) //delay_time ma cang cao thi ctrinh cang cham
            {


            SDL_Delay(delay_time);
            }
        }

    }
    close();
    return 0;
}
