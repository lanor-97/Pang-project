#ifndef DRAGO_H
#define DRAGO_H
#include "Animation.h"
#include <iostream>
using namespace std;

class Drago  {
private:
    int 	dimX,
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
    Drago(int dimx,int dimy,int x,int y);
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

    bool hitFire(int,int, int,int);
    
};

Drago::Drago()  {
	dimX=120;
    dimY=120;
    posX=640;
    posY=480;
    dimFuocoX=40;
    dimFuocoY=30;
    posFuocoX=posX-10;
    posFuocoY=posY-(dimY/2);
    drago=al_load_bitmap("images/dragonArriving.png");
    fuoco=al_load_bitmap("images/fireBall.png");
    frames=6;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

Drago::Drago(int dimx, int dimy, int x, int y)  {
	dimX=dimx;
	dimY=dimy;
	posX=x;
    posY=y;
    dimFuocoX=40;
    dimFuocoY=30;
   	posFuocoX=posX-dimx/2;
  	posFuocoY=posY+dimy/2;
    drago=al_load_bitmap("images/dragonArriving.png");
    fuoco=al_load_bitmap("images/fireBall.png");
    frames=6;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

bool Drago::Draw(bool arrive,bool spitFire)  {
	al_destroy_bitmap(drago);
    if(arrive)  {
        setFrames(6);
        drago=al_load_bitmap("images/dragonArriving.png");
        animazione.setFrameDelay(6);
        posX--;
        if(!animazione.eseguiFrame(drago,dimX,dimY,posX,posY,true,frames))
        	return false;
    }
    else if(spitFire)  {
        setFrames(6);
        animazione.setFrameDelay(10);
        drago=al_load_bitmap("images/dragonSpitting.png");
        if(!animazione.eseguiFrame(drago,dimX,dimY,posX,posY,false,frames))
        	return false;
    }
    else  {
        setFrames(12);
        drago=al_load_bitmap("images/dragonAnimation.png");
        animazione.setFrameDelay(8);
        if(!animazione.eseguiFrame(drago,dimX,dimY,posX,posY,true,frames))
        	return false;
    }
    return true;
}

bool Drago::DrawFire(bool colpitoFuoco, bool fire)
{
    if(fire && !colpitoFuoco)
    {
        if(posFuocoX>=-20)
            posFuocoX-=4;
        else
            {
                posFuocoX=570;  
                return false;
            }    
        al_draw_bitmap(fuoco,posFuocoX,posFuocoY,0);     
    }
    else if(colpitoFuoco)
        {
            posFuocoX=605;
            return false; 
        }    
    return true;           
}

bool Drago::hitFire(int playerPosX, int playerPosY, int playerDimX, int playerDimY)
{
    bool b1 = playerPosX <= posFuocoX+dimFuocoX,
	     b2 = playerPosX+playerDimX >= posFuocoX,
		 b3 = playerPosY <= posFuocoY+dimFuocoY,
         b4 = playerPosY+playerDimY>=posFuocoY;
    if(b1 && b2 && b3 && b4)
    return true;
    else
    return false;     
}

#endif