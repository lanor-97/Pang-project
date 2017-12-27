#ifndef SFONDO_H
#define SFONDO_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class Sfondo  {
private:
	int posX;
	int posY;
	ALLEGRO_BITMAP *bitmap;
	
public:
	Sfondo(): posX(0), posY(0)  { bitmap=al_load_bitmap("sfondo1.png"); }
	~Sfondo()  { al_destroy_bitmap(bitmap); }
	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
	void Draw()  { al_draw_bitmap(bitmap,posX,posY,0); }
};


#endif
	
