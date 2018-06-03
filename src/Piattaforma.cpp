#include "headers/Piattaforma.h"

Piattaforma::Piattaforma(float x, float y, bool b)  {	//b = tipo, 0 = normale, 1 = estesa
	
	posX = x;
	posY = y;
	if(!b)  {
		bitmap = al_load_bitmap("../images/piattaforma.png");
		dimX = 94;
		dimY = 49;
	}
	else  {
		bitmap = al_load_bitmap("../images/piattaformaEstesa.png");
		dimX = 640;
		dimY = 45;
	}
	
}

Piattaforma::~Piattaforma()  {
	if(bitmap)  {
		al_destroy_bitmap(bitmap);
	}
}

bool Piattaforma::playerHere(Giocatore* player)  {
	float	px = player->getX(),
			dx = player->getDimX();

	if(px+dx < posX)	return false;
	if(px > posX+dimX)	return false;
	return true;
}

bool Piattaforma::hitByHook(Giocatore* player)  {
	float 	x = player->getArmaX(),
			y = player->getArmaY(),
			d = player->getArmaDim();

	if(x+d < posX)		return false;
	if(x > posX+dimX)	return false;
	if(y > posY+dimY)	return false;
	return true;
}

bool Piattaforma::powerUpHere(PowerUp* powerup)  {
	int powerX = powerup->getX(),
		powerDimX = powerup->getDimX(),
		powerY = powerup->getY(),
		powerDimY = powerup->getDimY();

	bool 	b1 = powerX > posX + dimX,
			b2 = powerX + powerDimX < posX,
			b3 = powerY + powerDimY < posY;
	
	return !b1 && !b2 && b3;
}