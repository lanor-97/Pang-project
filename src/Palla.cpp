#include "headers/Palla.h"

Palla::Palla(float x, float c, SIZE s, COLOR col, bool dir)  {
	size = s;
	colore = col;
	float a = rand();
	srand(time(0)+a);
	switch(s)  {
		case PIC:		dim = 20;
						h_max = 2;

						if(col == GREEN)
							bitmap = al_load_bitmap("../images/palla_pic.png");
						else if(col == RED)
							bitmap = al_load_bitmap("../images/palla_pic2.png");
						else
							bitmap = al_load_bitmap("../images/palla_pic3.png");

						bouncerY = 3.3 + (rand()%5+1)*0.12;
		break;
		
		case MED: 		dim = 40;
						h_max = 1.8;

						if(col == GREEN)
							bitmap = al_load_bitmap("../images/palla_med.png");
						else if(col == RED)
							bitmap = al_load_bitmap("../images/palla_med2.png");
						else
							bitmap = al_load_bitmap("../images/palla_med3.png");
					
						bouncerY = 2.35 + (rand()%5+1)*0.1;
		break;
		
		case GRA: 		dim = 70;
						h_max = 1.5;

						if(col == GREEN)
							bitmap = al_load_bitmap("../images/palla_gra.png");
						else if(col == RED)
							bitmap = al_load_bitmap("../images/palla_gra2.png");
						else
							bitmap = al_load_bitmap("../images/palla_gra3.png");
						
						bouncerY = 1.9 + (rand()%5 +1)*0.06;
		break;
	}
	posX = x;
	posY = 0;
	if(dir)  {
		bouncerX = 2;
		direzioneX = RIGHT;
	}
	else  {
		bouncerX = -2;
		direzioneX = LEFT;
	}
	cont = c;
	processatoX = false;
	processatoY = false;
	direzioneY = DOWN;
	lastPosY = posY;
	canY = 0;
}

Palla::~Palla()  {
	if(bitmap)  {
		al_destroy_bitmap(bitmap);
	}
}

void Palla::calculateY(int SY)  { 
	SY = SY - dim;
	if(cont > 314 || cont < -314)
		cont = 1;

	float sen = sin(cont/100);
	lastPosY = posY;
	posY = SY - (120 + abs((sen*(SY/h_max))));
	cont += bouncerY;
	processatoY = true;

	if(posY > lastPosY)
		direzioneY = DOWN;
	else
		direzioneY = UP;

}

void Palla::toggleDirezioneX()  {
	if(direzioneX == RIGHT)
		direzioneX = LEFT;
	else
		direzioneX = RIGHT;
}

void Palla::toggleDirezioneY()  {
	if(direzioneY == UP)
		direzioneY = DOWN;
	else
		direzioneY = UP;
}