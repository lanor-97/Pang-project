#ifndef GIOCATORE_H
#define GIOCATORE_H
#include "iostream"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
using namespace std;

class Giocatore  {
private:
  	int 	dim_x,
			dim_y,
			posX,
			posY;
  	ALLEGRO_BITMAP *bitmap;
    int frames;

public:
   Giocatore(int, int,int);
  	~Giocatore()  { al_destroy_bitmap(bitmap); }
  	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
  	int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getDim_x() const  { return dim_x; }
   int getDim_y() const  { return dim_y; }
   int getFrames() const {return frames;}
  	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setDim_x(int d)  { dim_x=d; }
   void setDim_y(int d)  { dim_y=d; }
   void setFrames(int f) {frames=f;}
    void Draw(int currFrame, bool keyLeft, bool keyRight, bool drawShoot, bool toLeft, bool caduto);
};

Giocatore::Giocatore(int dx, int dy, int f)  {
	dim_x = dx;
	dim_y = dy;
  frames=f;
	posX = 0;
	posY = 0;
	bitmap =al_load_bitmap("images/shrekFermoSinistra.png");
}

void Giocatore:: Draw(int currFrame, bool keyLeft, bool keyRight, bool drawShoot, bool toLeft, bool caduto){
  if(keyLeft && !drawShoot && !caduto)
  {
    setBitmap(al_load_bitmap("images/shrekSinistra.png"));
    al_draw_bitmap_region(bitmap,currFrame*getDim_x(),0,getDim_x(),getDim_y(),getX(),getY(),0);
  }
  else if(keyRight && !drawShoot && !caduto)
  {
    setBitmap(al_load_bitmap("images/shrekDestra.png"));
    al_draw_bitmap_region(bitmap,currFrame*getDim_x(),0,getDim_x(),getDim_y(),getX(),getY(),0);
  }
  else if(drawShoot && toLeft && !caduto)
  {
    setBitmap(al_load_bitmap("images/shrekHookSinistra.png"));
    al_draw_bitmap_region(bitmap,currFrame*getDim_x(),0,getDim_x(),getDim_y(),getX(),getY(),0);
  }
  else if(drawShoot && !toLeft && !caduto)
  {
    setBitmap(al_load_bitmap("images/shrekHookDestra.png"));
    al_draw_bitmap_region(bitmap,currFrame*getDim_x(),0,getDim_x(),getDim_y(),getX(),getY(),0);
  }
  else if(caduto && toLeft)
  {
    setBitmap(al_load_bitmap("images/shrekColpitoSinistra.png"));
    al_draw_bitmap_region(bitmap,currFrame*getDim_x(),0,getDim_x(),getDim_y(),getX(),getY(),0);
  }
  else if(caduto && !toLeft)
  {
    setBitmap(al_load_bitmap("images/shrekColpitoDestra.png"));
    al_draw_bitmap_region(bitmap,currFrame*getDim_x(),0,getDim_x(),getDim_y(),getX(),getY(),0);
  }

  else if(!drawShoot && toLeft && !caduto)
  {
    setBitmap(al_load_bitmap("images/shrekFermoSinistra.png"));
    al_draw_bitmap(bitmap,posX,posY,0);
  }
  else if(!drawShoot && !caduto)
  {
    setBitmap(al_load_bitmap("images/shrekFermoDestra.png"));
    al_draw_bitmap(bitmap,posX,posY,0);
  }
  
}


#endif
