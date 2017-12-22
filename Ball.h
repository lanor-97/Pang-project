#ifndef BALL_H
#define BALL_H
#include <allegro5/allegro.h>

class Ball  {
private:
 	int dim;
  	int posX;
  	int posY;
  	ALLEGRO_BITMAP *ball;

public:
  	//Ball()  { dim=0; posX=0; posY=0; ball=NULL; }
  	//da errori se si crea un oggetto ball ^ così e poi si chiama il distruttore, non c'è niente da distruggere
  	Ball(int d, int x, int y): dim(d), posX(x), posY(y)  { ball=al_create_bitmap(d,d); }
  	~Ball()  { al_destroy_bitmap(ball); }
  	ALLEGRO_BITMAP* getBall() const  { return ball; }
  	int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getDim() const  { return dim; }
  	void setBall(ALLEGRO_BITMAP *bitmap)  {ball = bitmap; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setDim(int d)  { dim=d; }
  	void Draw()  { al_draw_bitmap(ball,posX,posY,0); }
};


#endif
