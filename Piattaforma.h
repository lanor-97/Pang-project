#ifndef PIATTAFORMA_H
#define PIATTAFORMA_H
#include "Giocatore.h"
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
  	~Piattaforma();
  	float getDim_x() const  { return dim_x; }
  	float getDim_y() const  { return dim_y; }
  	int getX() const  { return posX; }
	int getY() const  { return posY; }
	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
	void setX(int x)  { posX=x; }
	void setY(int y)  { posY=y; }
	void Draw()  { al_draw_bitmap(bitmap,posX,posY,0); }
	bool playerHere(Giocatore*);
	bool hitByHook(Giocatore*);
};

Piattaforma::Piattaforma(float x, float y)  {
	dim_x = 94;
	dim_y = 49;
	posX = x;
	posY = y;
	bitmap = al_load_bitmap("images/piattaforma.png");
}

Piattaforma::~Piattaforma()  {
	if(bitmap)  {
		cerr<<"\ndistruggo piattaforma_bitmap"; 
		al_destroy_bitmap(bitmap);
	}
}

bool Piattaforma::playerHere(Giocatore* player)  {
	float	px = player->getX(),
			dx = player->getDim_x();

	if(px+dx < posX)	return false;
	if(px > posX+dim_x)	return false;
	return true;
}

bool Piattaforma::hitByHook(Giocatore* player)  {
	float 	x = player->getX_arma(),
			y = player->getY_arma(),
			d = player->getDim_arma();

	if(x+d < posX)		return false;
	if(x > posX+dim_x)	return false;
	if(y > posY+dim_y)	return false;
	return true;
}

#endif