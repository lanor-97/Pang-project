#ifndef GIOCATORE_H
#define GIOCATORE_H
#include "iostream"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
using namespace std;

class Giocatore  {
private:
  	int 	dim_x,
			dim_y,
			posX,
			posY;
  	ALLEGRO_BITMAP *bitmap;

public:
   Giocatore(int, int);
  	~Giocatore()  { al_destroy_bitmap(bitmap); }
  	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
  	int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getDim_x() const  { return dim_x; }
   int getDim_y() const  { return dim_y; }
  	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setDim_x(int d)  { dim_x=d; }
   void setDim_y(int d)  { dim_y=d; }
  	void Draw()  { al_draw_bitmap(bitmap,posX,posY,0); }
};

Giocatore::Giocatore(int dx, int dy)  {
	dim_x = dx;
	dim_y = dy;
	posX = 0;
	posY = 0;
	bitmap = al_load_bitmap("images/man.png");
}


#endif
