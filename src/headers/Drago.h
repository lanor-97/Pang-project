#ifndef DRAGO_H
#define DRAGO_H

#include "Animation.h"
#include "Giocatore.h"
#include <iostream>
using namespace std;

class Drago  {
private:
    int 	  dimX,
			      dimY,
			      posX,
		      	posY,
            posFuocoX,
            posFuocoY,
            dimFuocoX,
            dimFuocoY,
            frames;
  	ALLEGRO_BITMAP *drago;
    ALLEGRO_BITMAP *fuoco;
    Animation animazione;
   	
public:
    Drago();
    Drago(int dimx,int dimy,int x,int y, int fireX);
    ~Drago(){al_destroy_bitmap(drago); al_destroy_bitmap(fuoco);}

    int getX() const  { return posX; }
  	int getY() const  { return posY; }
    int getFuocoX() const  { return posFuocoX; }
  	int getFuocoY() const  { return posFuocoY; }
    int getDimFuocoX() const {return dimFuocoX;}
    int getDimFuocoY() const {return dimFuocoY;}
	  int getFrames() const {return frames;}

  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
    void setFuocoX(int x)  { posFuocoX=x; }
  	void setFuocoY(int y)  { posFuocoY=y; }
  	void setDimX(int d)  { dimX=d; }
   	void setDimY(int d)  { dimY=d; }
   	void setFrames(int f) {frames=f;}

    bool Draw(bool,bool);
    bool DrawFire(bool,bool);

    bool hitFire(Giocatore*);
    
};



#endif