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
	int 	dim;
  	float	posX,
			posY,
			bouncer,
			cont,		//cont per algoritmo fisica
			h_max;		//coeff. altezza massima
    SIZE 	size;
  	ALLEGRO_BITMAP 	*bitmap_g,
					*bitmap_m,
					*bitmap_p;

public:
  	Palla(float, SIZE);
  	~Palla();
  	bool getBitmap() const  { return bitmap_g && bitmap_m && bitmap_p; }
  	float getX() const  { return posX; }
  	float getY() const  { return posY; }
  	int getDim() const  { return dim; }
  	//float getBouncer() const  { return bouncer; }
    //float getCont() const  { return cont; }
  	//void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
  	void setX(float x)  { posX=x; }
  	void setY(float y)  { posY=y; }
  	void setDim(int d)  { dim=d; }
  	void setBouncer(float x)  { bouncer=x; }
  	void Draw()  { al_draw_bitmap(bitmap_g,posX,posY,0); }
  	float calculateY(int);
  	void Move(int, int);
};

Palla::Palla(float c, SIZE s)  {
	size = s;
	switch(s)  {
		case PIC:	dim = 20;
					h_max = 3;
		break;
		
		case MED: 	dim = 40;
					h_max = 2;
		break;
		
		case GRA: 	dim = 70;
					h_max = 1.5;
		break;
	}
	posX = 0;
	posY = 0;
	bouncer = 2;
	cont = c;
	bitmap_g = al_load_bitmap("images/palla_gra.png");
	bitmap_m = al_load_bitmap("images/palla_med.png");
	bitmap_p = al_load_bitmap("images/palla_pic.png");
}

Palla::~Palla()  {
	al_destroy_bitmap(bitmap_g);
	al_destroy_bitmap(bitmap_m);
	al_destroy_bitmap(bitmap_p);
}

float Palla::calculateY(int SH)  { 
    if(cont > 314)
		    cont = 1;
      
    float abc = SH-(abs(sin(cont/100))*(SH/h_max))-dim;
  	cont += abs(bouncer);
  	return abc;
}

void Palla::Move(int SW, int SH)  {
	if(posX < 0 || posX > SW - dim) {
		bouncer = -bouncer;
	}

	posX = posX + bouncer;
	posY = calculateY(SH);
}


#endif
