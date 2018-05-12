#ifndef FARQUAAD_H
#define FARQUAAD_H
#include "Animation.h"
#include <iostream>
using namespace std;

class Farquaad
{
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

Farquaad::Farquaad()  {
    dimX=60;
    dimY=70;
    posX=640;
    posY=130;
    farquaad=al_load_bitmap("images/farquaadArriving.png");
    frames=3;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

Farquaad::Farquaad(int x,int y)  {
    dimX=60;
    dimY=70;
    posX=x;
    posY=y;
    farquaad=al_load_bitmap("images/farquaadArriving.png");
    frames=3;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

void Farquaad::DrawVictory()  {
    setFrames(2);
    animazione.setFrameDelay(7);
    farquaad=al_load_bitmap("images/farquaadDefeated.png");
    animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames());
}

bool Farquaad::Draw(bool scappa, bool ball, bool arrive)  {
    if(ball && !scappa && !arrive)
    {
        setFrames(5);
        animazione.setFrameDelay(8);
        farquaad=al_load_bitmap("images/farquaadBall.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), false,getFrames()))
        return false;
    }
    else if(arrive && !ball && !scappa)
    {
        setFrames(3);
        animazione.setFrameDelay(7);
            posX--;
        farquaad=al_load_bitmap("images/farquaadArriving.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    else if(scappa && !arrive && !ball)
    {
        setFrames(3);
        animazione.setFrameDelay(7);
            posX++;       
        farquaad=al_load_bitmap("images/farquaadScappa.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    else
    {
        setFrames(6);
        animazione.setFrameDelay(7);
        farquaad=al_load_bitmap("images/farquaadFermo.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    return true;
}


#endif