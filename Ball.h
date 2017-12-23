#ifndef BALL_H
#define BALL_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "iostream"
#include "cmath"
using namespace std;

class Ball  {
private:
 	int dim;
  	float posX;
  	float posY;
  	float bouncer;
  	float cont;
  	ALLEGRO_BITMAP *ball;

public:
  	Ball(float c): dim(0), posX(0), posY(0), bouncer(2), cont(c)  { ball=NULL; }
  	//da errori se si crea un oggetto ball ^ così senza nel main assegnargli una bitmap
  	//poi se si chiama il distruttore, non c'è niente da distruggere
  	Ball(int d, float x, float y): dim(d), posX(x), posY(y), bouncer(2)  { ball=al_create_bitmap(d,d); }
  	~Ball()  { al_destroy_bitmap(ball); }
  	ALLEGRO_BITMAP* getBall() const  { return ball; }
  	float getX() const  { return posX; }
  	float getY() const  { return posY; }
  	int getDim() const  { return dim; }
  	float getBouncer() const  { return bouncer; }
  	void setBall(ALLEGRO_BITMAP *bitmap)  { ball = bitmap; }
  	void setX(float x)  { posX=x; }
  	void setY(float y)  { posY=y; }
  	void setDim(int d)  { dim=d; }
  	void setBouncer(float x)  { bouncer=x; }
  	void Draw()  { al_draw_bitmap(ball,posX,posY,0); }
  	float calculateY(const int);
};

float Ball::calculateY(const int SY)  { 
	if(cont > 314)
		cont = 1;
  	float abc = SY-(abs(sin(cont/100))*(SY/2))-dim;
  	cont += abs(bouncer);
  	return abc;
}


#endif
