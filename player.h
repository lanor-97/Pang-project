#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

class Player
{
private:
  int dim;
  int posX;
  int posY;
  ALLEGRO_BITMAP *player;
public:
  Player(){dim=0;posX=0;posY=0; player=NULL;}
  Player(int dim, int x, int y){this->dim=dim;this->posX=x; this->posY=y; player=al_create_bitmap(dim-10,dim);}
  ~Player(){al_destroy_bitmap(player);}
  ALLEGRO_BITMAP* getPlayer(){return player;}
  void setPlayer(ALLEGRO_BITMAP *bitmap){this->player=bitmap;}
  int getX(){return posX;}
  int getY(){return posY;}
  int getDim(){return dim;}
  void setX(int x){this->posX=x;}
  void setY(int y){this->posY=y;}
  void setDim(int dim){this->dim=dim;}
  void Draw(){ al_draw_bitmap(player,posX,posY,0);}

};
#endif
