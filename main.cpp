#include "Livello1.h"
const int 		SCREEN_W = 640;
const int 		SCREEN_H = 480;

bool Menu(ALLEGRO_DISPLAY*, float[]);
void Transition(ALLEGRO_BITMAP*);

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
   	Livello1* L1 = new Livello1(SCREEN_W, SCREEN_H, player, display);

   	play = Menu(display, res_info);
   	while(play && vite > 0)  {

	   	while(vite > 0)  {
	   		int x = L1->Esegui(display, vite, res_info);
	   		if(x < 0)
	   			vite = 0;
	   		else if(x == 0)  {
	   			vite--;
	   			continue;
	   		}
	   		else if(x == 1)  {
	   			cerr << "MA BRAVO TANTI AUGURI";
	   			break;
	   		}
	   		
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

	menu_play = al_load_bitmap("images/shrekMenu1.jpg");
	menu_exit = al_load_bitmap("images/shrekMenu2.jpg");
	bool play = true, fullscreen = false, drawTransition=false;

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_install_keyboard();
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	
	al_draw_bitmap(menu_play, 0, 0, 0);
	al_flip_display();

	while(!drawTransition)  {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				play = false;
				break;
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER)  {
				drawTransition=true;
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT && play)  {
				play = false;
				al_draw_bitmap(menu_exit,0,0,0);
				al_flip_display();
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT && !play)  {
				play = true;
				al_draw_bitmap(menu_play,0,0,0);
				al_flip_display();
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_F)  {
				fullscreen = !fullscreen;

				if(fullscreen)  {
					res_info[0] = res_info[2] / res_info[4];
					res_info[1] = res_info[3] / res_info[5];
				}
				else  {
					res_info[0] = 1;
					res_info[1] = 1;
				}

					
				al_identity_transform(&redimencionamento);
				al_scale_transform(&redimencionamento,res_info[0], res_info[1]);
				al_use_transform(&redimencionamento);
				al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, fullscreen);
					
				if(play)  {
					al_draw_bitmap(menu_play,0,0,0);
					al_flip_display();
				}
				else  {
					al_draw_bitmap(menu_play,0,0,0);
					al_flip_display();
				}
			}
		}

		if(drawTransition && !play)
			Transition(menu_exit);	
		if(drawTransition && play)
			Transition(menu_play);		
	}
	
	al_destroy_bitmap(menu_play);
	al_destroy_bitmap(menu_exit);
	al_destroy_event_queue(event_queue);
	return play;

	return 0;
}

void Transition(ALLEGRO_BITMAP* bmp)  {
	Transizione transizione;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue=NULL;
	timer = al_create_timer(1.0 / 25);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	transizione.setTipo(0);
	al_start_timer(timer);

	while(true)  {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			al_draw_bitmap(bmp,0,0,0);
			if(!transizione.Draw())  {
				return;
			}
							
			al_flip_display();
		}
	}

	al_destroy_timer(timer);
}