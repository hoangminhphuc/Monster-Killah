#ifndef GAME-MAP_H
#define GAME-MAP_H


#include "Spine.h"

#define TILEMAX 20
class Tile : public Spine
{
public:
    Tile(){;}
    ~Tile(){;}
};


class GameMap
{
    public:
         GameMap(){;}
         ~GameMap(){;}

        void loadmap(char* nam);
        void loadTiles(SDL_Renderer* screen);
        void Drawmap(SDL_Renderer* screen);
        gMAP getMap() const {return game_map;};
        void SetMap(gMAP& map_data) {game_map = map_data;};
    private:
        gMAP game_map;
        Tile tile_mat[TILEMAX];


};



#endif // GAME-MAP_H
