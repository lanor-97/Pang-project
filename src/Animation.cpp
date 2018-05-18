#include "headers/Animation.h"

Animation::Animation(int frameCount, int frameDelay, int currFrame, int totalFrames)  {
    this->frameCount=frameCount;
    this->frameDelay=frameDelay;
    this->currFrame=currFrame;
}

bool Animation::eseguiFrame(ALLEGRO_BITMAP *bitmap,int dim_x, int dim_y, int x, int y, bool ridisegna, int totalFrames)  {
    bool continua=true;
    al_draw_bitmap_region(bitmap,currFrame*dim_x,0,dim_x,dim_y,x,y,0);

    if(++frameCount>=frameDelay)  {
		if(++currFrame>=totalFrames)  {
			currFrame=0;
            continua=false;
		}
		frameCount=0;
	}
        
    if(!ridisegna && currFrame>=totalFrames)
        currFrame=0;
      	return continua;
}