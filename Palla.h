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

enum SIZE  { PIC = 0, MED, GRA };  	//piccola = 20px, media = 40px, grande = 70px
enum COLOR  { GREEN = 0, RED, BLUE };
enum DIREZIONE  { UP = 0, RIGHT, DOWN, LEFT };

class Palla  {
private:
	int 	dim;
  	float	posX,
			posY,
			bouncerX,
			bouncerY,
			cont,			//pos h
			h_max,			//coeff. altezza massima
			lastPosY;
	bool	processatoX,
			processatoY;
	COLOR colore;
   	SIZE size;
  	ALLEGRO_BITMAP *bitmap;
	Animation animazione;
	DIREZIONE 	direzioneX,
				direzioneY;

public:
  	Palla(float, float, SIZE, COLOR, bool);
  	~Palla();
  	
  	float getX() const  { return posX; }
  	float getY() const  { return posY; }
  	int getDim() const  { return dim; }
  	float getBouncerX() const  { return bouncerX; }
  	float getBouncerY() const  { return bouncerY; }
   	float getCont() const  { return cont; }
	SIZE getSize() const  { return size; }
	COLOR getColor() const  { return colore; }
	DIREZIONE getDirezioneX() const  { return direzioneX; }
	DIREZIONE getDirezioneY() const  { return direzioneY; }
	bool getProcessatoX() const  { return processatoX; }
  	bool getProcessatoY() const  { return processatoY; }

  	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
  	void setX(float x)  { posX=x; }
  	void setY(float y)  { posY=y; }
  	void toggleBouncerX()  { bouncerX = -bouncerX; toggleDirezioneX(); }
  	void setBouncerY(float y)  { bouncerY = y; }
  	void toggleDirezioneX();
  	void toggleDirezioneY();

  	void Draw() const  { al_draw_bitmap(bitmap,posX,posY,0); }
	void DrawExplosion();

	void calculateX()  { posX += bouncerX; processatoX = true; }
  	void calculateY(const int);
  	void clearProcess()  { processatoX = false; processatoY = false; }

  	int canY;
};


Palla::Palla(float x, float c, SIZE s, COLOR col, bool dir)  {
	size = s;
	colore = col;
	float a = rand();
	srand(time(0)+a);
	switch(s)  {
		case PIC:		dim = 20;
						h_max = 2;

						if(col == GREEN)
							bitmap = al_load_bitmap("images/palla_pic.png");
						else if(col == RED)
							bitmap = al_load_bitmap("images/palla_pic2.png");
						else
							bitmap = al_load_bitmap("images/palla_pic3.png");

						bouncerY = 3.3 + (rand()%5+1)*0.12;
		break;
		
		case MED: 		dim = 40;
						h_max = 1.8;

						if(col == GREEN)
							bitmap = al_load_bitmap("images/palla_med.png");
						else if(col == RED)
							bitmap = al_load_bitmap("images/palla_med2.png");
						else
							bitmap = al_load_bitmap("images/palla_med3.png");
					
						bouncerY = 2.35 + (rand()%5+1)*0.1;
		break;
		
		case GRA: 		dim = 70;
						h_max = 1.5;

						if(col == GREEN)
							bitmap = al_load_bitmap("images/palla_gra.png");
						else if(col == RED)
							bitmap = al_load_bitmap("images/palla_gra2.png");
						else
							bitmap = al_load_bitmap("images/palla_gra3.png");
						
						bouncerY = 1.9 + (rand()%5 +1)*0.06;
		break;
	}
	posX = x;
	posY = 0;
	if(dir)  {
		bouncerX = 2;
		direzioneX = RIGHT;
	}
	else  {
		bouncerX = -2;
		direzioneX = LEFT;
	}
	cont = c;
	processatoX = false;
	processatoY = false;
	direzioneY = DOWN;
	lastPosY = posY;
	canY = 0;
}

Palla::~Palla()  {
	if(bitmap)  {
		al_destroy_bitmap(bitmap);
	}
}

void Palla::calculateY(int SY)  { 
	SY = SY - dim;
	if(cont > 314 || cont < -314)
		cont = 1;

	float sen = sin(cont/100);
	lastPosY = posY;
	posY = SY - (120 + abs((sen*(SY/h_max))));
	cont += bouncerY;
	processatoY = true;

	if(posY > lastPosY)
		direzioneY = DOWN;
	else
		direzioneY = UP;

}

void Palla::toggleDirezioneX()  {
	if(direzioneX == RIGHT)
		direzioneX = LEFT;
	else
		direzioneX = RIGHT;
}

void Palla::toggleDirezioneY()  {
	if(direzioneY == UP)
		direzioneY = DOWN;
	else
		direzioneY = UP;
}


#endif
