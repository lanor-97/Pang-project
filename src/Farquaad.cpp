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

bool Farquaad::Draw(bool scappa, bool ball, bool arrive)  {
    if(ball && !scappa && !arrive)
    {
        setFrames(5);
        animazione.setFrameDelay(10);
        farquaad=al_load_bitmap("../images/farquaadBall.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), false,getFrames()))
        return false;
    }
    else if(arrive && !ball && !scappa)
    {
        setFrames(3);
        animazione.setFrameDelay(7);
            posX--;
        farquaad=al_load_bitmap("../images/farquaadArriving.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    else if(scappa && !arrive && !ball)
    {
        setFrames(3);
        animazione.setFrameDelay(7);
            posX++;       
        farquaad=al_load_bitmap("../images/farquaadScappa.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    else
    {
        setFrames(6);
        animazione.setFrameDelay(7);
        farquaad=al_load_bitmap("../images/farquaadFermo.png");
        if(!animazione.eseguiFrame(farquaad,getDimX(),getDimY(),getX(),getY(), true,getFrames()))
        return false;
    }
    return true;
}