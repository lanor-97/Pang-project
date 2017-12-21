#ifndef BALL_H
#define BALL_H
#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

class Ball
{
private:
  int dim;
  int posX;
  int posY;
  ALLEGRO_BITMAP *ball;
public:
  Ball(){dim=0;posX=0;posY=0; ball=NULL;} //mi piace la figa
  Ball(){dim=0;posX=0;posY=0; ball=NULL;}
  Ball(int dim, int x, int y){this->dim=dim;this->posX=x; this->posY=y; ball=al_create_bitmap(dim,dim);}
  ~Ball(){al_destroy_bitmap(ball);}
  ALLEGRO_BITMAP* getBall(){return ball;}
  void setBall(ALLEGRO_BITMAP *bitmap){this->ball=bitmap;}
  int getX(){return posX;}
  int getY(){return posY;}
  int getDim(){return dim;}
  void setX(int x){this->posX=x;}
  void setY(int y){this->posY=y;}
  void setDim(int dim){this->dim=dim;}
  void Draw(){ al_draw_bitmap(ball,posX,posY,0);}

};
#endif
