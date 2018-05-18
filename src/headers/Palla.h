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


#endif
