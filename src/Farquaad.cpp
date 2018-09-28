#include "headers/Farquaad.h"

Farquaad::Farquaad()  {
    dimX=60;
    dimY=75;
    posX=640;
    posY=130;
    farquaad=al_load_bitmap("../images/farquaadArriving.png");
    frames=3;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

Farquaad::Farquaad(int x,int y)  {
    dimX=60;
    dimY=75;
    posX=x;
    posY=y;
    farquaad=al_load_bitmap("../images/farquaadArriving.png");
    frames=3;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

void Farquaad::DrawVictory()  {
    setFrames(2);
    animazione.setFrameDelay(7);
    farquaad=al_load_bitmap("../images/farquaadDefeated.png");
    animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames());
}

bool Farquaad::Draw(bool scappa, bool ball, bool arrive, bool timeRunning)  {
    if(farquaad) al_destroy_bitmap(farquaad);
    
    if(ball && !scappa && !arrive)
    {
        if(timeRunning)
            setFrames(5);
        else
            setFrames(1); 
        animazione.setFrameDelay(10);
        farquaad=al_load_bitmap("../images/farquaadBall.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), false,getFrames()))
        return false;
    }
    else if(arrive && !ball && !scappa)
    {
        if(timeRunning)
            setFrames(3);
        else
            setFrames(1); 
        animazione.setFrameDelay(7);
            posX--;
        farquaad=al_load_bitmap("../images/farquaadArriving.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    else if(scappa && !arrive && !ball)
    {
        if(timeRunning)
            setFrames(3);
        else
            setFrames(1); 
        animazione.setFrameDelay(7);
            posX++;       
        farquaad=al_load_bitmap("../images/farquaadScappa.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    else
    {
        if(timeRunning)
            setFrames(6);
        else
            setFrames(1); 
        animazione.setFrameDelay(7);
        farquaad=al_load_bitmap("../images/farquaadFermo.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    return true;
}