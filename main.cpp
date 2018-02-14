#include "Livello1.h"

const float 	FPS = 60;
const int 		SCREEN_W = 640;
const int 		SCREEN_H = 480;

int main(int argc, char **argv)  { 

	//INIZIALIZZAZIONE ALLEGRO E CO
	if(!al_init())  {
    	cerr << "failed to initialize allegro!\n";
    	return -1;
   	}

   	if(!al_init_image_addon())  {
     	cerr<<"failed to initialize allegro_image\n";
		return -1;
   	}


	if(!al_init_ttf_addon())  {
		cerr<<"failed to initialize allegro_ttf\n";
		return -1;
	}

	if(!al_init_font_addon())  {
		cerr<<"failed to initialize allegro_font\n";
		return -1;
	}

	Giocatore* player = new Giocatore(60,70,6);

   	player->setX(SCREEN_W/2 - player->getDim_x());
   	player->setY(SCREEN_H - player->getDim_y());
   	player->posizionaArma();

   	Livello1 L(SCREEN_W, SCREEN_H, player);
   	L.Esegui(FPS);

   	delete player;
  	return 0;
}