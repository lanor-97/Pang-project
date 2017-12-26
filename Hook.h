#ifndef HOOK_H
#define HOOK_H
#include <allegro5/allegro.h>

class Hook  {
private:
	float dim;
  	int posX;
  	int posY;
  	ALLEGRO_BITMAP *hook;
  	
public:
  	//Hook(){dim=0;posX=0;posY=0; hook=NULL;}
  	//da errori se si crea un oggetto ball ^ così e poi si chiama il distruttore, non c'è niente da distruggere
  	Hook(float d, int x, int y): dim(d), posX(x), posY(y)  { 
  		hook=NULL; 
  	}
  	~Hook()  { al_destroy_bitmap(hook); }
	ALLEGRO_BITMAP* getHook() const  { return hook; }
	int getX() const  { return posX; }
	int getY() const  { return posY; }
	float getDim() const  { return dim; }
	void setHook(ALLEGRO_BITMAP *bitmap)  { hook=bitmap; }
	void setX(int x)  { posX=x; }
	void setY(int y)  { posY=y; }
	void setDim(float d)  { dim=d; }
	void Draw()  { al_draw_bitmap(hook,posX,posY,0); }
};


#endif
