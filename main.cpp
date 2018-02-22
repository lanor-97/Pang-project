#include "Livello1.h"
#include "Transizione.h"
const int 		SCREEN_W = 640;
const int 		SCREEN_H = 480;

bool Menu(ALLEGRO_DISPLAY*, float[]);

int main(int argc, char **argv)  { 

	int 					vite = 3;
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

	//CREAZIONE DISPLAY
	ALLEGRO_DISPLAY*		display = NULL;

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
   	player->setY(SCREEN_H/1.37 - player->getDim_y());
   	player->posizionaArma();

   	//CREAZIONE LIVELLO
   	Livello1* L1 = new Livello1(SCREEN_W, SCREEN_H, player);

   	play = Menu(display, res_info);
   	while(play && vite > 0)  {

	   	while(vite > 0)  {
	   		if(!L1->Esegui(display, vite, res_info))  {
	   			vite--;
	   			continue;
	   		}
	   		cout << "hai vinto coglione\n";
   		}
   	}

   	delete L1;
   	delete player;
   	al_destroy_display(display);

  	return 0;
}


bool Menu(ALLEGRO_DISPLAY* display, float res_info[])  {

	ALLEGRO_BITMAP*			menu_play=NULL;
	ALLEGRO_BITMAP*			menu_exit=NULL;
	ALLEGRO_EVENT_QUEUE* 	event_queue=NULL;
	ALLEGRO_TRANSFORM 		redimencionamento;
	Transizione             transizione;

	menu_play = al_load_bitmap("images/shrekMenu1.jpg");
	menu_exit = al_load_bitmap("images/shrekMenu2.jpg");
	bool play = true, fullscreen = false;
	bool drawTransition=false;

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_install_keyboard();
	al_register_event_source(event_queue,al_get_keyboard_event_source());

	al_draw_bitmap(menu_play, 0, 0, 0);
	al_flip_display();
	
	while(true)  {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				play = false;
				break;
			}

			if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE || ev.keyboard.keycode==ALLEGRO_KEY_ENTER)  {
				drawTransition=true;
			}

			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT && play)  {
				play = false;
				al_draw_bitmap(menu_exit,0,0,0);
				al_flip_display();
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT && !play)  {
				play = true;
				al_draw_bitmap(menu_play,0,0,0);
				al_flip_display();
			}
			if(ev.keyboard.keycode==ALLEGRO_KEY_F)  {
				fullscreen = !fullscreen;

				if(fullscreen)  {
					res_info[0] = res_info[2] / res_info[4];
					res_info[1] = res_info[3] / res_info[5];
				}
				else  {
					res_info[0] = 1;
					res_info[1] = 1;
				}

				if(drawTransition)
				{
					transizione.setTipo(0);
					if(!transizione.Draw())
					{
						drawTransition=false;
						break;
					}	
				}	
				al_identity_transform(&redimencionamento);
				al_scale_transform(&redimencionamento,res_info[0], res_info[1]);
				al_use_transform(&redimencionamento);
				al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, fullscreen);
				

				if( play)  {
					al_draw_bitmap(menu_play,0,0,0);
					al_flip_display();
				}
				else  {
					al_draw_bitmap(menu_play,0,0,0);
					al_flip_display();
				}
				


			}

		}

	}

	al_destroy_bitmap(menu_play);
	al_destroy_bitmap(menu_exit);
	al_destroy_event_queue(event_queue);
	return play;

	return 0;
}