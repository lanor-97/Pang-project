#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

class Player  {
private:
  	int dim;
  	int posX;
  	int posY;
  	ALLEGRO_BITMAP *player;

public:
  	//Player(){dim=0;posX=0;posY=0; player=NULL;}
	//da errori se si crea un oggetto ball ^ così e poi si chiama il distruttore, non c'è niente da distruggere
  	Player(int d, int x, int y): dim(d), posX(x), posY(y)  { player=al_create_bitmap(d-10,d); }
  	~Player()  { al_destroy_bitmap(player); }
  	ALLEGRO_BITMAP* getPlayer() const  { return player; }
  	int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getDim() const  { return dim; }
  	void setPlayer(ALLEGRO_BITMAP *bitmap)  { player=bitmap; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setDim(int d)  { dim=d; }
  	void Draw()  { al_draw_bitmap(player,posX,posY,0); }
};


#endif
