#ifndef PIATTAFORMA_H
#define PIATTAFORMA_H
#include "Giocatore.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class Piattaforma  {
private:
	short	dimX,
			dimY,
			posX,
			posY;

  	ALLEGRO_BITMAP *bitmap;

public:
	Piattaforma(): dimX(0), dimY(0), posX(0), posY(0)  { bitmap=NULL; }
  	Piattaforma(float, float);
  	~Piattaforma();

  	short getDimX() const  { return dimX; }
  	short getDimY() const  { return dimY; }
  	short getX() const  { return posX; }
	short getY() const  { return posY; }

	void Draw()  { al_draw_bitmap(bitmap,posX,posY,0); }
	
	bool playerHere(Giocatore*);
	bool hitByHook(Giocatore*);
};

Piattaforma::Piattaforma(float x, float y)  {
	dimX = 94;
	dimY = 49;
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
			dx = player->getDimX();

	if(px+dx < posX)	return false;
	if(px > posX+dimX)	return false;
	return true;
}

bool Piattaforma::hitByHook(Giocatore* player)  {
	float 	x = player->getArmaX(),
			y = player->getArmaY(),
			d = player->getArmaDim();

	if(x+d < posX)		return false;
	if(x > posX+dimX)	return false;
	if(y > posY+dimY)	return false;
	return true;
}

#endif