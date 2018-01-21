#ifndef VITA_H
#define VITA_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class Vita  {
private:
	int numVite;
	ALLEGRO_BITMAP *bitmap;
	
public:
	Vita(int n): numVite(n)  { bitmap=al_load_bitmap("images/vita.png"); }
	~Vita()  { al_destroy_bitmap(bitmap); }
	int getNumVite() const  { return numVite; }
	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
	void setNumVite(int n)  { numVite = n; }
	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
	void Draw(float x, float y)  { al_draw_bitmap(bitmap, x, y, 0); }
	Vita& operator++(int)  { numVite++; return *this; }
	Vita& operator--(int)  { numVite--; return *this; }
	bool operator>=(int x)  { return numVite >= x; }
	bool operator<=(int x)  { return numVite <= x; }
};


#endif
