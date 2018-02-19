#ifndef SFONDO_H
#define SFONDO_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class Sfondo  {
private:
	ALLEGRO_BITMAP *bitmap;

public:
	Sfondo(unsigned x);
	~Sfondo()  { al_destroy_bitmap(bitmap); }
	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
	void Draw()  { al_draw_bitmap(bitmap,0,0,0); }
};

Sfondo::Sfondo(unsigned x)  {
	switch(x)  {
		case 0:	bitmap=al_load_bitmap("images/shrek1.jpg");
		break;

		case 1:	bitmap=al_load_bitmap("images/sfondo2.jpg");
		break;

		case 3: bitmap=al_load_bitmap("images/sfondo3Piani.jpg");
		break;
	}
}

#endif
