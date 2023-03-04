#include "maincharacter.h"
#include "AllFunc.h"

// kich thuoc cua 1 frame nhan vat max phai la 64x64 de khi nhay vao nhung o
//trong cua map, nhan vat co the lot qua dc (vi 1 o tilemap co size 64x64)
maincharacter::maincharacter()
{
    frame_ = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status_ = -1;
    input_type.left_ = 0;
    input_type.right_ = 0;
    input_type.jump_ = 0;
    input_type.up_ = 0;
    input_type.down_ = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
    come_back_time_ = 0;
}

maincharacter::~maincharacter()
{
    //dtor
}


bool maincharacter::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Spine::LoadImg(path, screen);
    if (ret == true)
    {
        width_frame = rect_.w/10;
        height_frame = rect_.h;
    }

    return ret;
}

void maincharacter::set_clips()
{
   if (width_frame > 0 && height_frame > 0)
   {
       frame_clip[0].x = 0;
       frame_clip[0].y = 0;
       frame_clip[0].w = width_frame;
       frame_clip[0].h = height_frame;

       frame_clip[1].x = width_frame;
       frame_clip[1].y = 0;
       frame_clip[1].w = width_frame;
       frame_clip[1].h = height_frame;

       frame_clip[2].x = 2*width_frame;
       frame_clip[2].y = 0;
       frame_clip[2].w = width_frame;
       frame_clip[2].h = height_frame;

       frame_clip[3].x = 3*width_frame;
       frame_clip[3].y = 0;
       frame_clip[3].w = width_frame;
       frame_clip[3].h = height_frame;

       frame_clip[4].x = 4*width_frame;
       frame_clip[4].y = 0;
       frame_clip[4].w = width_frame;
       frame_clip[4].h = height_frame;

       frame_clip[5].x = 5*width_frame;
       frame_clip[5].y = 0;
       frame_clip[5].w = width_frame;
       frame_clip[5].h = height_frame;

       frame_clip[6].x = 6*width_frame;
       frame_clip[6].y = 0;
       frame_clip[6].w = width_frame;
       frame_clip[6].h = height_frame;

       frame_clip[7].x = 7*width_frame;
       frame_clip[7].y = 0;
       frame_clip[7].w = width_frame;
       frame_clip[7].h = height_frame;

       frame_clip[8].x = 8*width_frame;
       frame_clip[8].y = 0;
       frame_clip[8].w = width_frame;
       frame_clip[8].h = height_frame;

       frame_clip[9].x = 9*width_frame;
       frame_clip[9].y = 0;
       frame_clip[9].w = width_frame;
       frame_clip[9].h = height_frame;


   }
}

void maincharacter::Show(SDL_Renderer* des)
{

    UpdateImagePlayer(des);

    if (input_type.left_ == 1 || input_type.right_ == 1)
    {
        frame_++;
    }
    else
    {
            frame_ = 0;
    }

    if(frame_ >= 10)
    {
        frame_ = 0; // neu frame_++ o tren ma cong mai thi se khong dung lai dc
    // chi co toi da 10 frame
    }
    if (come_back_time_ == 0){
    rect_.x = x_pos - map_x_;
    rect_.y = y_pos - map_y_;
    //vi x_pos la tinh tu diem bat dau, nen khi man hinh di chuyen,
    //can phai tru them cai luong man hinh cuon chieu theo

    SDL_Rect* current_clip = &frame_clip[frame_]; // lay frame hien tai

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};

    SDL_RenderCopy(des, gText, current_clip, &renderQuad); // day cai gText len man hinh voi cai frame hien ta

    }
}


void maincharacter::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = WALK_RIGHT;
                input_type.right_ = 1;
                input_type.left_  = 0;
                UpdateImagePlayer(screen);

            }
            break;
        case SDLK_LEFT:
            {
                status_ = WALK_LEFT;
                input_type.left_ = 1;
                input_type.right_ = 0;
                UpdateImagePlayer(screen);
            }
            break;


        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = WALK_RIGHT;
                input_type.right_ = 0; // set lai ve 0 de khi nha? phim ra khong chay frame nua
            }
            break;
        case SDLK_LEFT:
            {
                status_ = WALK_LEFT;
                input_type.left_ = 0;
            }
            break;


        }

    }

    if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button == SDL_BUTTON_RIGHT)
        {
            input_type.jump_ = 1;
        }
    }
}


void maincharacter::DoPlayer(gMAP& map_data) // tinh dau cuoi cua map, tinh va cham
{
    if (come_back_time_ == 0)
    {


    x_val = 0;
    y_val += 0.8; //cong lien tuc de nhan vat roi tu tu xuong

    if(y_val >= MAX_FALL_SPEED)
    {
        y_val = MAX_FALL_SPEED;
    }

    if(input_type.left_ == 1)
    {
        x_val -= PLAYER_SPEED;
    }
    else if(input_type.right_ ==1)
    {
        x_val +=PLAYER_SPEED;
    }

    if (input_type.jump_ ==1)
    {
        if (on_ground == true)
        {


        y_val = - PLAYER_JUMP_VAL;
        }

        on_ground = false;
        input_type.jump_ = 0;

    }

    CheckToMap(map_data);
    CenterEntityOnMap(map_data); //tinh toan thong so ban do de dich chuyen
    }

    if (come_back_time_ > 0)
    {
        come_back_time_ --;
        if(come_back_time_ == 0)
        {
            if(x_pos > 256)
            {


            x_pos-=256;
            map_x_-=256;
            }
            else {
                x_pos = 0;
            }
            y_pos = 0;
            x_val = 0;
            y_val = 0;
        }
    }
}


void maincharacter::CenterEntityOnMap(gMAP& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH)/2;
    // vi tri nhan vat - khung hinh/2
    // khi di chuyen 1 nua ban do thi khung hinh cung bat dau di chuyen theo
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }

    map_data.start_y = y_pos - (SCREEN_HEIGHT)/2;
    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if (map_data.start_y +SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

void maincharacter::CheckToMap(gMAP& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;


    //CHECK HORIZONTAL
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE; //true thi lay ve trc
    x1 = (x_pos + x_val) / TILE_SIZE; //ktra nvat dang dung o o bnhieu
    x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;

    if (x1>=0 && x2<max_map_hor && y1 >= 0 && y2 < max_map_ver)
    {
        if(x_val > 0) // nvat dang di chuyen ve ben phai
        {
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if(x_val < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                x_pos = (x1+1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }



    //CHECK VERTICAL
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos +y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SIZE;

    if (x1>=0 && x2<max_map_hor && y1 >= 0 && y2 < max_map_ver)
    {
        if (y_val > 0)
        {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= (height_frame + 1); // day la khi nhan vat dung tren mat dat, cham o TILE MAP
                y_val = 0;
                on_ground = true; // gan bien cham mat dat cho on_ground de sau nay dung`

            }
        }
        else if(y_val < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos = (y1+1)*TILE_SIZE;
                y_val = 0;
            }
        }
    }

    x_pos +=x_val;
    y_pos +=y_val;

    if(x_pos < 0)
    {
        x_pos = 0;
    }
    else if(x_pos + width_frame > map_data.max_x) //vi tri cua nvat + chieu rong nvat > max chieu rong
    {
        x_pos = map_data.max_x - width_frame - 1;
    }

    if(y_pos > map_data.max_y)
    {
        come_back_time_ = 60;
    }
}

void maincharacter::UpdateImagePlayer(SDL_Renderer* des)
{
    if(on_ground == true)
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("layers//pp_left.png", des);
        }
        else
        {
            LoadImg("layers//pp_right.png", des);
        }
    }
    else
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("layers//jump_right.png", des);
        }
        else
        {
            LoadImg("layers//jump_right.png", des);
        }
    }
}
