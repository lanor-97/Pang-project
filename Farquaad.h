#ifndef FARQUAAD_H
#define FARQUAAD_H
#include "Animation.h"
#include <iostream>
using namespace std;

class Farquaad
{
    private:
    int 	dim_x,
			dim_y,
			posX,
			posY,
            posFuocoX,
            posFuocoY;
  	ALLEGRO_BITMAP *farquaad;
    Animation animazione;
   	int frames;
   	
    public:
    Farquaad()
    {
        dim_x=50;
        dim_y=60;
        posX=640;
        posY=480;
        farquaad=al_load_bitmap("images/farquaadArriving.png");
        frames=3;
        animazione.setFrameCount(0);
        animazione.setFrameDelay(5);
        animazione.setCurrFrame(0);
    }
    Farquaad(int dimx,int dimy,int x,int y)
    {
        dim_x=dimx;
        dim_y=dimy;
        posX=x;
        posY=y;
        farquaad=al_load_bitmap("images/farquaadArriving.png");
        frames=3;
        animazione.setFrameCount(0);
        animazione.setFrameDelay(5);
        animazione.setCurrFrame(0);
    }
    ~Farquaad(){al_destroy_bitmap(farquaad);}
    int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getDim_x() const  { return dim_x; }
   	int getDim_y() const  { return dim_y; }
   	int getFrames() const {return frames;}
  	void setFarquaad(ALLEGRO_BITMAP *b_map)  { farquaad=b_map; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setDim_x(int d)  { dim_x=d; }
   	void setDim_y(int d)  { dim_y=d; }
   	void setFrames(int f) {frames=f;}
    bool Draw(bool,bool,bool);
    void DrawVictory();
    
};
void Farquaad::DrawVictory()
{
    setFrames(2);
  animazione.setFrameDelay(7);
  farquaad=al_load_bitmap("images/farquaadDefeated.png");
  animazione.eseguiFrame(farquaad,getDim_x(),getDim_y(),getX(),getY(), true,getFrames());
}

bool Farquaad::Draw(bool scappa, bool ball, bool arrive)
{
    if(ball && !scappa && !arrive)
    {
        setFrames(5);
        animazione.setFrameDelay(7);
        farquaad=al_load_bitmap("images/farquaadBall.png");
        if(!animazione.eseguiFrame(farquaad,getDim_x(),getDim_y(),getX(),getY(), false,getFrames()))
        return false;
    }
    else if(arrive && !ball && !scappa)
    {
        setFrames(3);
        animazione.setFrameDelay(5);
        farquaad=al_load_bitmap("images/farquaadArriving.png");
        if(!animazione.eseguiFrame(farquaad,getDim_x(),getDim_y(),getX(),getY(), true,getFrames()))
        return false;
    }
    else if(scappa && !arrive && !ball)
    {
        setFrames(3);
        animazione.setFrameDelay(5);
        farquaad=al_load_bitmap("images/farquaadScappa.png");
        if(!animazione.eseguiFrame(farquaad,getDim_x(),getDim_y(),getX(),getY(), true,getFrames()))
        return false;
    }
    else
    {
        setFrames(6);
        animazione.setFrameDelay(5);
        farquaad=al_load_bitmap("images/farquaadFermo.png");
        if(!animazione.eseguiFrame(farquaad,getDim_x(),getDim_y(),getX(),getY(), true,getFrames()))
        return false;
    }
    return true;

}
#endif