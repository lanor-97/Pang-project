#ifndef PIATTAFORMA_H
#define PIATTAFORMA_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class Piattaforma  {
private:
	float	dim_x,
			dim_y,
			posX,
			posY;

  	ALLEGRO_BITMAP *bitmap;

public:
	Piattaforma(): dim_x(0), dim_y(0), posX(0), posY(0)  { bitmap=NULL; }
  	Piattaforma(float, float);
  	~Piattaforma()  { cerr<<"\ndistruggo piattaforma_bitmap"; if(bitmap) al_destroy_bitmap(bitmap); }
  	float getDim_x() const  { return dim_x; }
  	float getDim_y() const  { return dim_y; }
  	int getX() const  { return posX; }
	int getY() const  { return posY; }
	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
	void setX(int x)  { posX=x; }
	void setY(int y)  { posY=y; }
	void Draw(int H)  { al_draw_bitmap(bitmap,posX,posY,0); }
};

Piattaforma::Piattaforma(float x, float y)  {
	dim_x = 94;
	dim_y = 49;
	posX = x;
	posY = y;
	bitmap = al_load_bitmap("images/piattaforma.png");
}
#endif