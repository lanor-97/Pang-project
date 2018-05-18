#include "headers/Drago.h"

Drago::Drago()  {
	dimX=120;
    dimY=120;
    posX=640;
    posY=480;
    dimFuocoX=40;
    dimFuocoY=30;
    posFuocoX=posX-10;
    posFuocoY=posY-(dimY/2);
    drago=al_load_bitmap("../images/dragonArriving.png");
    fuoco=al_load_bitmap("../images/fireBall.png");
    frames=6;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

Drago::Drago(int dimx, int dimy, int x, int y, int fireX)  {
	dimX=dimx;
	dimY=dimy;
	posX=x;
    posY=y;
    dimFuocoX=40;
    dimFuocoY=30;
   	posFuocoX=fireX;
  	posFuocoY=posY+dimy/2;
    drago=al_load_bitmap("../images/dragonArriving.png");
    fuoco=al_load_bitmap("../images/fireBall.png");
    frames=6;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

bool Drago::Draw(bool arrive,bool spitFire)  {
	al_destroy_bitmap(drago);
    if(arrive)  {
        setFrames(6);
        drago=al_load_bitmap("../images/dragonArriving.png");
        animazione.setFrameDelay(6);
        posX--;
        if(!animazione.eseguiFrame(drago,dimX,dimY,posX,posY,true,frames))
        	return false;
    }
    else if(spitFire)  {
        setFrames(6);
        animazione.setFrameDelay(10);
        drago=al_load_bitmap("../images/dragonSpitting.png");
        if(!animazione.eseguiFrame(drago,dimX,dimY,posX,posY,false,frames))
        	return false;
    }
    else  {
        setFrames(12);
        drago=al_load_bitmap("../images/dragonAnimation.png");
        animazione.setFrameDelay(8);
        if(!animazione.eseguiFrame(drago,dimX,dimY,posX,posY,true,frames))
        	return false;
    }
    return true;
}

bool Drago::DrawFire(bool colpitoFuoco, bool fire)  {
    if(fire && !colpitoFuoco)  {
        if(posFuocoX>=-20)
            posFuocoX-=4;
        else  {
            posFuocoX=posX+dimX/4;  
            return false;
        }    
        al_draw_bitmap(fuoco,posFuocoX,posFuocoY,0);     
    }
    else if(colpitoFuoco)  {
        posFuocoX=posX+dimX/4;
        return false; 
    }    
    return true;           
}

bool Drago::hitFire(Giocatore* player)  {
    int playerPosX = player->getX(),
        playerPosY = player->getY(),
        playerDimX = player->getDimX(),
        playerDimY = player->getDimY();
    
    bool    b1 = posFuocoX > playerPosX+playerDimX,
	        b2 = posFuocoX+dimFuocoX < playerPosX,
		    b3 = posFuocoY > playerPosY+playerDimY,
            b4 = posFuocoY+dimFuocoY < playerPosY;

    if(!b1 && !b2 && !b3 && !b4)
        return true;
    return false;     
}