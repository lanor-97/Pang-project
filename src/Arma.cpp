#include "headers/Arma.h"

Arma::Arma(int d, int x, int y)  {
	dim = d;
	posX = x;
	posY = y;
	bitmap = al_load_bitmap("../images/arpione1.png");
}

Arma::~Arma()  {
	if(bitmap)  {
		al_destroy_bitmap(bitmap);
	}
}