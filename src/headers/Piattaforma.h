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
  	Piattaforma(float, float, bool);
  	~Piattaforma();

  	short getDimX() const  { return dimX; }
  	short getDimY() const  { return dimY; }
  	short getX() const  { return posX; }
	short getY() const  { return posY; }

	void Draw()  { al_draw_bitmap(bitmap,posX,posY,0); }
	
	bool playerHere(Giocatore*);
	bool hitByHook(Giocatore*);
};

#endif