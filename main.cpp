#include "Livello1.h"

const int 		SCREEN_W = 640;
const int 		SCREEN_H = 480;

int main(int argc, char **argv)  { 

	int vite = 3;
	//INIZIALIZZAZIONE FUNZIONI ALLEGRO E CO
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

	//CREAZIONE GIOCATORE
	Giocatore* player = new Giocatore(60,70,6);

   	player->setX(SCREEN_W/2 - player->getDim_x());
   	player->setY(SCREEN_H/1.37 - player->getDim_y());
   	player->posizionaArma();

   	//CREAZIONE LIVELLO
   	Livello1 L(SCREEN_W, SCREEN_H, player);

   	while(vite > 0)  {
   		if(!L.Esegui(vite))  {
   			vite--;
   			continue;
   		}
   		cout << "hai vinto coglione\n";
   		break;
   	}

   	delete player;
  	return 0;
}