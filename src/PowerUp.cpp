#include "headers/PowerUp.h"

void PowerUp::Spawn(int x, int y)  {
    posX = x;
    posY = y;
    if(bitmap)
        al_destroy_bitmap(bitmap);
    
    int r = rand()%numTotale;
    switch(r)  {
        case 0:
            tipo = BOLLA;
            bitmap = al_load_bitmap("../images/bubblePowerUp.png");
            break;
        case 1:
            tipo = FREEZE;
            bitmap = al_load_bitmap("../images/freezePowerUp.png");    
    }
    spawned = true;
}

void PowerUp::playerTookIt(Giocatore* player)  {
    int playerX = player->getX(),
        playerY = player->getY(),
        playerDimX = player->getDimX(),
        playerDimY = player->getDimY();

    bool    b1 = playerX > posX + dimX,
            b2 = playerX+playerDimX < posX,
            b3 = playerY > posY + dimY,
            b4 = playerY+playerDimY < posY;
    
    if(!b1 && !b2 && !b3 && !b4)  {
        spawned = false;
    }
}