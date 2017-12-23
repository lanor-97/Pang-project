#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

class Player  {
private:
  	int dim_x;
    int dim_y;
  	int posX;
  	int posY;
  	ALLEGRO_BITMAP *player;

public:
    Player() { dim_x=0; dim_y=0; posX=0;posY=0; player=NULL;}
    //da errori se si crea un oggetto ball ^ così e poi si chiama il distruttore, non c'è niente da distruggere
    Player(int dx, int dy, int x, int y): dim_x(dx), dim_y(dy), posX(x), posY(y)  { player=NULL; }
  	~Player()  { al_destroy_bitmap(player); }
  	ALLEGRO_BITMAP* getPlayer() const  { return player; }
  	int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getDim_x() const  { return dim_x; }
    int getDim_y() const  { return dim_y; }
  	void setPlayer(ALLEGRO_BITMAP *bitmap)  { player=bitmap; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setDim_x(int d)  { dim_x=d; }
    void setDim_y(int d)  { dim_y=d; }
  	void Draw()  { al_draw_bitmap(player,posX,posY,0); }
};


#endif
