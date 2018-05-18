#include "headers/PowerUp.h"

void PowerUp::Spawn(int x, int y)  {
    posX = x;
    posY = y;
    int r = rand()%numTotale;
    switch(r)  {
        case 0:
            tipo = BOLLA;
            //dimX = boh
            //dimY = boh
            bitmap = al_load_bitmap("../images/bubblePowerUp.png");   //giusto per prova
        case 1:
            tipo = ALTRO;
            //dimX = boh
            //dimY = boh
            bitmap = al_load_bitmap("../images/freezePowerUp.png");    
    }
}