#ifndef ANIMATION_H
#define ANIMATION_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <iostream>
using namespace std;

class Animation  {
private:
    int frameCount,
    	frameDelay,
    	currFrame;

public:
    Animation():frameCount(0),frameDelay(0),currFrame(0)  {}
    Animation(int, int, int, int);
    
    int getFrameCount() const  { return frameCount; }
    int getFrameDelay() const  { return frameDelay; }
    int getCurrFrame() const  { return currFrame; }

    void setFrameCount(int f)  { frameCount = f; }
    void setFrameDelay(int f)  { frameDelay = f; }
    void setCurrFrame(int f)  { currFrame = f; }

    bool eseguiFrame(ALLEGRO_BITMAP*, int, int, int, int, bool, int);
};


#endif