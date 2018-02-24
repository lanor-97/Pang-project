#ifndef SCALA_H
#define SCALA_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class Scala  {
private:
	float 	dim;
  	int 	posX,
			posY;
  	ALLEGRO_BITMAP *bitmap;
    int tipo;  

public:
  	Scala(float, int, int,int);
  	~Scala()  { al_destroy_bitmap(bitmap); }
	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
	int getX() const  { return posX; }
	int getY() const  { return posY; }
    int getTipo() const {return tipo;}
	float getDim() const  { return dim; }
	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
    void setTipo(int t){tipo=t;}
	void setX(int x)  { posX=x; }
	void setY(int y)  { posY=y; }
	void setDim(float d)  { dim=d; }
	void Draw(int H)  { al_draw_bitmap(bitmap,posX,posY,0); }
};

Scala::Scala(float d, int x, int y, int t)  {
    tipo=t;
	dim =d;
	posX = x;
	posY = y;
    if(tipo==1)
	bitmap = al_load_bitmap("images/scala1.png");
    if(tipo==2)
    bitmap= al_load_bitmap("images/scala2.png");
}
#endif