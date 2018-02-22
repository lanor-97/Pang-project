#ifndef ANIMATION_H
#define ANIMATION_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <iostream>
using namespace std;

class Animation{
    private:
    int frameCount;
    int frameDelay;
    int currFrame;

    public:
    Animation():frameCount(0),frameDelay(0),currFrame(0){}
    Animation(int frameCount, int frameDelay, int currFrame, int totalFrames)
    {
        this->frameCount=frameCount;
        this->frameDelay=frameDelay;
        this->currFrame=currFrame;
    }

    int getFrameCount(){return frameCount;}
    int getFrameDelay(){return frameDelay;}
    int getCurrFrame(){return currFrame;}

    void setFrameCount(int f){frameCount=f;}
    void setFrameDelay(int f){frameDelay=f;}
    void setCurrFrame(int f){currFrame=f;}

    bool eseguiFrame(ALLEGRO_BITMAP *bitmap,int dim_x, int dim_y, int x, int y, bool ridisegna, int totalFrames)
    {
        bool continua=true;
        if(++frameCount>=frameDelay)  {
				if(++currFrame>=totalFrames)  {
					currFrame=0;
                    continua=false;
				}
				frameCount=0;
			}
        al_draw_bitmap_region(bitmap,currFrame*dim_x,0,dim_x,dim_y,x,y,0);
        if(!ridisegna && currFrame>=totalFrames)
                currFrame=0;
        return continua;
    }
};
#endif