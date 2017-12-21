#ifndef HOOK_H
#define HOOK_H
#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

class Hook
{
private:
  int dim;
  int posX;
  int posY;
  ALLEGRO_BITMAP *hook;
public:
  Hook(){dim=0;posX=0;posY=0; hook=NULL;}
  Hook(int dim, int x, int y){this->dim=dim;this->posX=x; this->posY=y; hook=al_create_bitmap(dim/20,dim);}
  ALLEGRO_BITMAP* getHook(){return hook;}
  void setHook(ALLEGRO_BITMAP *bitmap){this->hook=bitmap;}
  int getX(){return posX;}
  int getY(){return posY;}
  int getDim(){return dim;}
  void setX(int x){this->posX=x;}
  void setY(int y){this->posY=y;}
  void setDim(int dim){this->dim=dim;}
  void Draw(){ al_draw_bitmap(hook,posX,posY,0);}
  void Destroy(){al_destroy_bitmap(hook);}
};
#endif
