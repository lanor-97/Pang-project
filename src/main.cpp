//to compile (in src folder)
//g++ *cpp -o main -lallegro -lallegro_main -lallegro_ttf -lallegro_image -lallegro_font -lallegro_audio -lallegro_acodec  -std=c++11

//capire perchè seg fault sempre

#include "headers/mainFunctions.h"

const int 		SCREEN_W = 640;
const int 		SCREEN_H = 480;
const int 		FPS = 60;

int main(int argc, char **argv)  { 

	int 					vite = 3, livello = 1, punteggio = 0;
	float 					res_x, res_y, res_monitor_x, res_monitor_y;
	bool					play = true;
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

	if(!al_install_keyboard())  {
		cerr <<"failed to install keyboard\n";
		return -1;
	}

	//CREAZIONE DISPLAY + aggiustamento con transform
	ALLEGRO_DISPLAY*		display = NULL;

	al_get_monitor_info(0,&info);
	res_monitor_x = info.x2 - info.x1;
	res_monitor_y = info.y2 - info.y1;
	res_x = 1;		//res_monitor_x / (float) SCREEN_W;
	res_y = 1;		//res_monitor_y / (float) SCREEN_H;
	float res_info[6] = {res_x, res_y, res_monitor_x, res_monitor_y, SCREEN_W, SCREEN_H };
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(SCREEN_W, SCREEN_H);

	al_identity_transform(&redimencionamento);
	al_scale_transform(&redimencionamento,res_x, res_y);
	al_use_transform(&redimencionamento);

	//CREAZIONE GIOCATORE
	Giocatore* player = new Giocatore(6);

   	player->setX(SCREEN_W/2 - player->getDimX());
   	player->setY(285);
   	player->posizionaArma();

   	//CREAZIONE LIVELLI
   	Livello1* L1 = new Livello1(SCREEN_W, SCREEN_H, player, display, FPS);
   	Livello2* L2 = new Livello2(L1, FPS);
	Livello3* L3 = new Livello3(L1, FPS);

   	Livello1* current_level = L1;

   	play = Menu(display, res_info);
   	while(play && vite > 0)  {

	   	while(vite > 0)  {
	   		CASO c = current_level->Esegui(vite, punteggio, res_info);
	   		if(c == EXIT)
	   			vite = 0;
	   		else if(c == VITAPERSA)  {
	   			vite--;
	   			continue;
	   		}
	   		else if(c == LIVELLOSUP)  {	
				cerr << punteggio << endl;
	   			if(livello == 1)  {
				   current_level = L2;
				   livello++;
				}
				else if(livello == 2)
					current_level = L3;
	   		}
	   		else if(c == MENU)
	   			break;
	   	}
	   	if(vite > 0)
	   		play = Menu(display, res_info);
   	}

   	if(L1)  {
   		delete L1;
   	}   	
   	if(L2)  {
   		delete L2;
   	}
	if(L3)  {
		delete L3;
	}
   	if(player)  {
   		delete player;
   	}
   	if(display)  {
   		al_destroy_display(display);
   	}
   	cerr << "\n";
  	return 0;
}