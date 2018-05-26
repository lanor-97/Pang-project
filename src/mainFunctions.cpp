#include "headers/mainFunctions.h"
bool Menu(ALLEGRO_DISPLAY* display, float res_info[])  {
    ALLEGRO_BITMAP*			menu_play=NULL;
	ALLEGRO_BITMAP*			menu_exit=NULL;
	ALLEGRO_EVENT_QUEUE* 	event_queue=NULL;
	ALLEGRO_TRANSFORM 		redimencionamento;

	

	menu_play = al_load_bitmap("../images/shrekMenu1.jpg");
	menu_exit = al_load_bitmap("../images/shrekMenu2.jpg");
	bool play = true, fullscreen = false, drawTransition=false;

	al_install_keyboard();
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_draw_bitmap(menu_play, 0, 0, 0);
	al_flip_display();
	
    al_reserve_samples(2);
	ALLEGRO_SAMPLE* sound=al_load_sample("audio/menu.wav");
	//SoundEffect* sounds=new SoundEffect();
	//Music* sound=new Music(1);

	while(!drawTransition)  {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			play = false;
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			al_play_sample(sound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				play = false;
				break;
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER || ev.keyboard.keycode==ALLEGRO_KEY_SPACE)  {
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
					al_draw_bitmap(menu_exit,0,0,0);
					al_flip_display();
				}
			}
		}

		if(drawTransition && !play)
			Transition(menu_exit);	
		if(drawTransition && play)
			Transition(menu_play);		
	}
	if(menu_play)  {
		al_destroy_sample(sound);
		al_destroy_bitmap(menu_play);
	}
	if(menu_exit)  {
		
		al_destroy_sample(sound);
		al_destroy_bitmap(menu_exit);
	}
	if(event_queue)  {
		al_destroy_sample(sound);
		al_destroy_event_queue(event_queue);
	}
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
	if(timer)  {
		al_destroy_timer(timer);
	}
}