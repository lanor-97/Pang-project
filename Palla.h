#ifndef PALLA_H
#define PALLA_H
#include "Animation.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "iostream"
#include "cmath"
#include "stdlib.h"
#include "time.h"
using namespace std;

enum SIZE  { PIC = 0, MED, GRA};  //piccola = 20px, media = 40px
                                  //grande = 70px
class Palla  {
private:
	int 	dim;
  	float	posX,
			posY,
			bouncer,
			bouncer_h,
			cont,			//pos h
			h_max;			//coeff. altezza massima
   	SIZE size;
  	ALLEGRO_BITMAP *bitmap;
	Animation animazione;

public:
  	Palla(float, float, SIZE);
  	~Palla();
  	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
  	float getX() const  { return posX; }
  	float getY() const  { return posY; }
  	int getDim() const  { return dim; }
  	float getBouncer() const  { return bouncer; }
  	float getBouncer_h() const  { return bouncer_h; }
   	float getCont() const  { return cont; }
	SIZE getSize() const  { return size; }
  	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
  	void setX(float x)  { posX=x; }
  	void setY(float y)  { posY=y; }
  	void setDim(int d)  { dim=d; }
  	void setBouncer(float x)  { bouncer=x; }
  	void setBouncer_h(float h)  { bouncer_h = h; }
  	void Draw() const  { al_draw_bitmap(bitmap,posX,posY,0); }
	void DrawExplosion();
  	void calculateY(const int);
};


Palla::Palla(float x, float c, SIZE s)  {
	srand(time(0));	
	size = s;
	switch(s)  {
		case PIC:		dim = 20;
						h_max = 2;
						bitmap = al_load_bitmap("images/palla_pic.png");
						
						bouncer_h = 3.3 + (rand()%100)*0.004;
		break;
		
		case MED: 		dim = 40;
						h_max = 1.8;
						bitmap = al_load_bitmap("images/palla_med.png");
					
						bouncer_h = 2.35 + (rand()%100)*0.003;
		break;
		
		case GRA: 		dim = 70;
						h_max = 1.5;
						bitmap = al_load_bitmap("images/palla_gra.png");
						
						bouncer_h = 1.9 + (rand()%100)*0.002;
		break;
	}
	posX = x;
	posY = 0;
	bouncer = 2;
	cont = c;
}

Palla::~Palla()  {
	if(bitmap)  {
		cerr<<"\ndistruggo palla_bitmap";
		al_destroy_bitmap(bitmap);
	}
}

void Palla::calculateY(int SY)  { 
	SY = SY - dim;
	if(cont > 314 || cont < -314)
		cont = 1;

	float sen = sin(cont/100);
	posY = SY - (120 + abs((sen*(SY/h_max))));
	cont += bouncer_h;
}


#endif
