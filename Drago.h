#ifndef DRAGO_H
#define DRAGO_H
#include "Animation.h"
#include <iostream>
using namespace std;

class Drago  {
    private:
    int 	dim_x,
			dim_y,
			posX,
			posY,
            posFuocoX,
            posFuocoY,
            dimFuocoX,
            dimFuocoY;
  	ALLEGRO_BITMAP *drago;
    ALLEGRO_BITMAP *fuoco;
    Animation animazione;
   	int frames;
   	
    public:
    Drago()
    {
        dim_x=120;
        dim_y=120;
        posX=640;
        posY=480;
        dimFuocoX=40;
        dimFuocoY=30;
        posFuocoX=posX;
        posFuocoY=posY-(dim_y/2);
        drago=al_load_bitmap("images/dragonArriving.png");
        fuoco=al_load_bitmap("images/fireBall.png");
        frames=6;
        animazione.setFrameCount(0);
        animazione.setFrameDelay(5);
        animazione.setCurrFrame(0);
    }
    Drago(int dimx,int dimy,int x,int y)
    {
        dim_x=dimx;
        dim_y=dimy;
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
    ~Drago(){al_destroy_bitmap(drago); al_destroy_bitmap(fuoco);}
    int getX() const  { return posX; }
  	int getY() const  { return posY; }
    int getFuocoX() const  { return posFuocoX; }
  	int getFuocoY() const  { return posFuocoY; }
    int getDimFuocoX() const {return dimFuocoX;}
    int getDimFuocoY() const {return dimFuocoY;}  
  	int getDim_x() const  { return dim_x; }
   	int getDim_y() const  { return dim_y; }
   	int getFrames() const {return frames;}
  	void setDrago(ALLEGRO_BITMAP *b_map)  { drago=b_map; }
    void setFuoco(ALLEGRO_BITMAP *b_map)  { fuoco=b_map; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
    void setFuocoX(int x)  { posFuocoX=x; }
  	void setFuocoY(int y)  { posFuocoY=y; }
  	void setDim_x(int d)  { dim_x=d; }
   	void setDim_y(int d)  { dim_y=d; }
   	void setFrames(int f) {frames=f;}
    bool Draw(bool,bool);
    bool DrawFire(bool,bool);
    bool hitFire(int,int, int,int);
    
};
bool Drago::Draw(bool arrive,bool spitFire)
{
    if(arrive)
    {
        setFrames(6);
        drago=al_load_bitmap("images/dragonArriving.png");
        animazione.setFrameDelay(6);
        posX--;
        if(!animazione.eseguiFrame(drago,getDim_x(),getDim_y(),getX(),getY(), true,getFrames()))
        return false;
    }
    else if(spitFire)
    {
        setFrames(6);
        animazione.setFrameDelay(10);
        drago=al_load_bitmap("images/dragonSpitting.png");
        if(!animazione.eseguiFrame(drago,getDim_x(),getDim_y(),getX(),getY(), false,getFrames()))
        return false;
    }
    else if(!spitFire && !arrive)
    {
        setFrames(12);
        drago=al_load_bitmap("images/dragonAnimation.png");
        animazione.setFrameDelay(8);
        if(!animazione.eseguiFrame(drago,getDim_x(),getDim_y(),getX(),getY(), true,getFrames()))
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
            posFuocoX=600;
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