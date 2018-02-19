#include "Livello1.h"

const int 		SCREEN_W = 640;
const int 		SCREEN_H = 480;

int main(int argc, char **argv)  { 

	int 					vite = 3;
	float 					res_x, res_y, res_monitor_x, res_monitor_y;
	ALLEGRO_TRANSFORM 		redimencionamento;
	ALLEGRO_MONITOR_INFO 	info;

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

	//CREAZIONE DISPLAY
	ALLEGRO_DISPLAY*	display = NULL;

	al_get_monitor_info(0,&info);
	res_monitor_x = info.x2 - info.x1;
	res_monitor_y = info.y2 - info.y1;
	res_x = 1;//res_monitor_x / (float) SCREEN_W;
	res_y = 1;//res_monitor_y / (float) SCREEN_H;
	float res_info[6] = {res_x, res_y, res_monitor_x, res_monitor_y, SCREEN_W, SCREEN_H };
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(SCREEN_W, SCREEN_H);

	al_identity_transform(&redimencionamento);
	al_scale_transform(&redimencionamento,res_x, res_y);
	al_use_transform(&redimencionamento);


	//CREAZIONE GIOCATORE
	Giocatore* player = new Giocatore(60,70,6);

   	player->setX(SCREEN_W/2 - player->getDim_x());
   	player->setY(SCREEN_H - player->getDim_y());
   	player->posizionaArma();

   	//CREAZIONE LIVELLO
   	Livello1 L(SCREEN_W, SCREEN_H, player);

   	while(vite > 0)  {
   		if(!L.Esegui(display, vite, res_info))  {
   			vite--;
   			continue;
   		}
   		cout << "hai vinto coglione\n";
   		break;
   	}

   	al_destroy_display(display);
   	delete player;
  	return 0;
}