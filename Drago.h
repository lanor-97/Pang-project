#ifndef DRAGO_H
#define DRAGO_H
#include "Animation.h"
#include <iostream>
using namespace std;

class Drago
{
    private:
    int 	dim_x,
			dim_y,
			posX,
			posY,
            posFuocoX,
            posFuocoY;
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
        posFuocoX=posX;
        posFuocoY=posY-(dim_y/2);
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
    
};
bool Drago::Draw(bool arrive,bool spitFire)
{
    if(arrive && !spitFire)
    {
        setFrames(6);
        drago=al_load_bitmap("dragonArriving.png");
        animazione.setFrameDelay(5);
        if(!animazione.eseguiFrame(drago,getDim_x(),getDim_y(),getX(),getY(), true,getFrames()))
        return false;
    }
    else if(spitFire)
    {
        setFrames(6);
        animazione.setFrameDelay(7);
        drago=al_load_bitmap("dragonSpitting.png");
        if(!animazione.eseguiFrame(drago,getDim_x(),getDim_y(),getX(),getY(), false,getFrames()))
        return false;
    }
    else
    {
        setFrames(12);
        drago=al_load_bitmap("dragonAnimation.png");
        animazione.setFrameDelay(5);
        if(!animazione.eseguiFrame(drago,getDim_x(),getDim_y(),getX(),getY(), true,getFrames()))
        return false;
    }
    return true;
}

bool Drago::DrawFire(bool colpitoFuoco, bool spitFire)
{
    if(spitFire)
    {
        if(posFuocoX>=0 && !colpitoFuoco)
            posFuocoX-=5;
        else
            {
                posFuocoX=640;  
                return false;
            }    
        al_draw_bitmap(fuoco,posFuocoX,posFuocoY,0);
        return true;      
    }
    return false;        
}
#endif