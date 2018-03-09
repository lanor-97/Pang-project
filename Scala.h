#ifndef SCALA_H
#define SCALA_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class Scala  {
private:
	float 	dim_x,
			dim_y,
			posX,
			posY;
	bool 	tipo;
	//tipo0(0) dim_x = 46, dim_y = 135
	//tipo1(1) dim_x = 45, dim_y = 166
	ALLEGRO_BITMAP *bitmap;

public:
	Scala(): dim_x(0), dim_y(0), posX(0), posY(0), tipo(false)  { bitmap = NULL; }
  	Scala(float, float, bool);				
  	~Scala();
  	float getDim_x() const  { return dim_x; }
  	float getDim_y() const  { return dim_y; }
	float getX() const  { return posX; }
	float getY() const  { return posY; }
    bool getTipo() const {return tipo;}
	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
	void setDim_x(float x)  { dim_x = x; }
	void setDim_y(float y)  { dim_y = y; }
	void setX(int x)  { posX=x; }
	void setY(int y)  { posY=y; }
	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
	void Draw()  { al_draw_bitmap(bitmap,posX,posY,0); }
};

Scala::Scala(float x, float y, bool t)  {
    tipo = t;
	posX = x;
	posY = y;
    if(tipo == 0)  {
    	dim_x = 46;
    	dim_y = 135;
		bitmap = al_load_bitmap("images/scala1.png");
    }
    else  {
    	dim_x = 45;
    	dim_y = 166;
    	bitmap= al_load_bitmap("images/scala2.png");
    }
}

Scala::~Scala()  {
	if(bitmap)  {
		cerr<<"\ndistruggo scala_bitmap"; 
		al_destroy_bitmap(bitmap);
	}
}


#endif
