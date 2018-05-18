#ifndef FARQUAAD_H
#define FARQUAAD_H

#include "Animation.h"
#include <iostream>
using namespace std;

class Farquaad  {
private:
    int 	dimX,
			dimY,
			posX,
			posY,
            posFuocoX,
            posFuocoY;
  	ALLEGRO_BITMAP *farquaad=NULL;
    Animation animazione;
   	int frames;
   	
public:
    Farquaad();
    Farquaad(int x,int y);
    ~Farquaad()  { if(farquaad) al_destroy_bitmap(farquaad); }

    int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getDimX() const  { return dimX; }
   	int getDimY() const  { return dimY; }
   	int getFrames() const {return frames;}

  	void setFarquaad(ALLEGRO_BITMAP *b_map)  { farquaad=b_map; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setDimX(int d)  { dimX=d; }
   	void setdimY(int d)  { dimY=d; }
   	void setFrames(int f) {frames=f;}

    bool Draw(bool,bool,bool);
    void DrawVictory();
    
};


#endif