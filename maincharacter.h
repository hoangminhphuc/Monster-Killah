#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include "AllFunc.h"
#include "Spine.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 20

class maincharacter : public Spine
{
    public:
        maincharacter();
        ~maincharacter();

        enum WalkType
        {
            WALK_RIGHT = 0,
            WALK_LEFT = 1,
        };

        bool LoadImg(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
        void set_clips();

        void DoPlayer(gMAP& map_data);
        void CheckToMap(gMAP& map_data);
        void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
        void CenterEntityOnMap(gMAP& map_data);
        void UpdateImagePlayer(SDL_Renderer* des);

    private:
        float x_val;
        float y_val;

        float x_pos;
        float y_pos;

        int width_frame;
        int height_frame;

        SDL_Rect frame_clip[10];
        Input input_type;
        int frame_; // khung nao
        int status_; // khi nao la left khi nao la right
        bool on_ground;

        int map_x_;
        int map_y_; //tinh toan xem vi tri cua ban do o dau

        int come_back_time_; // thời gian sau khi bị rơi xuống vực thẳm

};

#endif // MAINCHARACTER_H
