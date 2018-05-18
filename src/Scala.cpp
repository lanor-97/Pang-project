#include "headers/Scala.h"

Scala::Scala(int x, int y, bool t)  {
    tipo = t;
	posX = x;
	posY = y;
    if(tipo == 0)  {
    	dimX = 46;
    	dimY = 135;
		bitmap = al_load_bitmap("../images/scala1.png");
    }
    else  {
    	dimX = 45;
    	dimY = 166;
    	bitmap= al_load_bitmap("../images/scala2.png");
    }
}

Scala::~Scala()  {
	if(bitmap)  {
		al_destroy_bitmap(bitmap);
	}
}

bool Scala::playerHere(Giocatore* player)  {
	if(player->getX() > posX + dimX - 28)
		return false;
	if(player->getX()+player->getDimX() < posX + 28)
		return false;

	return true;
}