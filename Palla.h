#ifndef PALLA_H
#define PALLA_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "iostream"
#include "cmath"
using namespace std;

enum SIZE  { PIC = 0, MED, GRA};  //piccola = 20px, media = 40px
                                  //grande = 70px
class Palla  {
private:
	int dim;
  	float	posX,
			posY,
			bouncer,
			cont,		
			h_max;		//coeff. altezza massima
    SIZE size;
  	ALLEGRO_BITMAP *bitmap;

public:
  	Palla(float, SIZE);
  	~Palla()  { al_destroy_bitmap(bitmap); }
  	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
  	float getX() const  { return posX; }
  	float getY() const  { return posY; }
  	int getDim() const  { return dim; }
  	float getBouncer() const  { return bouncer; }
    float getCont() const  { return cont; }
  	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
  	void setX(float x)  { posX=x; }
  	void setY(float y)  { posY=y; }
  	void setDim(int d)  { dim=d; }
  	void setBouncer(float x)  { bouncer=x; }
  	void Draw()  { al_draw_bitmap(bitmap,posX,posY,0); }
  	float calculateY(const int);
};

Palla::Palla(float c, SIZE s)  {
	size = s;
	switch(s)  {
		case PIC:	dim = 20;
					h_max = 3;
					bitmap = al_load_bitmap("images/palla_pic.png");
		break;
		
		case MED: 	dim = 40;
					h_max = 2;
					bitmap = al_load_bitmap("images/palla_med.png");
		break;
		
		case GRA: 	dim = 70;
					h_max = 1.5;
					bitmap = al_load_bitmap("images/palla_gra.png");
		break;
	}
	posX = 0;
	posY = 0;
	bouncer = 2;
	cont = c;
}

float Palla::calculateY(const int SY)  { 
    if(cont > 314)
		    cont = 1;
      
    float abc = SY-(abs(sin(cont/100))*(SY/h_max))-dim;
  	cont += abs(bouncer);
  	return abc;
}


#endif
