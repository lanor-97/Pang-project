#ifndef HOOK_H
#define HOOK_H
#include <allegro5/allegro.h>

class Hook  {
private:
  	int dim;
  	int posX;
  	int posY;
  	ALLEGRO_BITMAP *hook;
  	
public:
  	//Hook(){dim=0;posX=0;posY=0; hook=NULL;}
  	//da errori se si crea un oggetto ball ^ così e poi si chiama il distruttore, non c'è niente da distruggere
  	Hook(int d, int x, int y): dim(d), posX(x), posY(y)  { hook=al_create_bitmap(dim/20,dim); }
  	~Hook()  { al_destroy_bitmap(hook); }
	ALLEGRO_BITMAP* getHook() const  { return hook; }
	int getX() const  { return posX; }
	int getY() const  { return posY; }
	int getDim() const  { return dim; }
	void setHook(ALLEGRO_BITMAP *bitmap)  { hook=bitmap; }
	void setX(int x)  { posX=x; }
	void setY(int y)  { posY=y; }
	void setDim(int d)  { dim=d; }
	void Draw()  { al_draw_bitmap(hook,posX,posY,0); }
};


#endif
