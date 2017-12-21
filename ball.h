#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

class Ball  {
private:
  int 	dim,
  		posX,
  		posY;
  ALLEGRO_BITMAP *ball;
public:
  Ball(): dim(0), posX(0), posY(0), ball(NULL)  {}
  Ball(int d, int x, int y): dim(d), posX(x), posY(y)  { 
  	ball = al_create_bitmap(d,d);
  }
  ALLEGRO_BITMAP* getBall()  { return ball; }
  void setBall(ALLEGRO_BITMAP *bitmap)  { ball = bitmap; }
  int getX() const { return posX; }
  int getY() const { return posY; }
  int getDim() const { return dim; }
  void setX(int x)  { posX = x; }
  void setY(int y)  { posY = y; }
  void setDim(int d)  { dim = d; }
  void Draw()  { al_draw_bitmap(ball,posX,posY,0); }
};
#endif
