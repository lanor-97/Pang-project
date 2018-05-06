#ifndef ARMA_H
#define ARMA_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class Arma  {
private:
	int dim,	
		posX,
		posY;
  	ALLEGRO_BITMAP *bitmap;

public:
  	Arma(int, int, int);
  	~Arma();

  	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
	int getX() const  { return posX; }
	int getY() const  { return posY; }
	int getDim() const  { return dim; }

	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
	void setX(int x)  { posX=x+24; }
	void setY(int y)  { posY=y; }

	void Draw(int H)  { al_draw_bitmap_region(bitmap,0,0,12,H,posX,posY,0); }
};

Arma::Arma(int d, int x, int y)  {
	dim = d;
	posX = x;
	posY = y;
	bitmap = al_load_bitmap("images/arpione1.png");
}

Arma::~Arma()  {
	if(bitmap)  {
		al_destroy_bitmap(bitmap);
	}
}


#endif
