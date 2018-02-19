#ifndef LIVELLO1_H
#define LIVELLO1_H

#include "GestorePalle.h"
#include "Sfondo.h"
#include "Giocatore.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class Livello1  {
public:
	Livello1(float, float, Giocatore*);
	bool Esegui(int);

protected:
	Sfondo sfondo;
	Giocatore* player;
	GestorePalle GP;
	float SCREEN_W, SCREEN_H;
};


Livello1::Livello1(float SW, float SH, Giocatore* p): sfondo(0), player(p), SCREEN_W(SW), SCREEN_H(SH)  {
	GP.setSW(SCREEN_W);
	GP.setSY(SCREEN_H);

	GP.aggiungiPalla(SCREEN_W/2, 157, GRA) && GP.aggiungiPalla(0, 157, GRA);
}

bool Livello1::Esegui(int vite)  {
	//DICHIARAZIONE VARIABILI ALLEGRO
	ALLEGRO_TRANSFORM 		redimencionamento;
	ALLEGRO_MONITOR_INFO 	info;
	ALLEGRO_DISPLAY*		display = NULL;
	ALLEGRO_EVENT_QUEUE*	event_queue = NULL;
	ALLEGRO_TIMER*			timer = NULL;
	ALLEGRO_FONT*			font1=NULL;
	ALLEGRO_FONT*			font2=NULL;
	ALLEGRO_BITMAP*			vite_bmp=NULL;

	//DICHIARAZIONE ALTRE VARIABILI 
	bool 	drawShoot=false, caduto=false, shoot=false, colpito=false, sfondo2=false, 
			presa=false, redraw = true, keyRight=false, keyLeft=false, keySpace=false, 
			toLeft=false, MatchOver=false, bitmap_ = true, fullscreen=true;

	int 	punteggio=0, tempo=3600, res_monitor_x, res_monitor_y, currFrame=0, 
			frameCount=0, frameDelay=5;

	float 	res_x, res_y;

	timer = al_create_timer(1.0 / 60);								//60 = FPS

	//AGGIUSTAMENTO E CREAZIONE DISPLAY
	al_get_monitor_info(0,&info);
	res_monitor_x = info.x2 - info.x1;
	res_monitor_y = info.y2 - info.y1;
	res_x = res_monitor_x / (float) SCREEN_W;
	res_y = res_monitor_y / (float) SCREEN_H;
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(res_monitor_x, res_monitor_y);

	al_identity_transform(&redimencionamento);
	al_scale_transform(&redimencionamento,res_x,res_y);
	al_use_transform(&redimencionamento);

	//CARICAMENTO FONT
	font1=al_load_ttf_font("images/SHREK.TTF",40,0);

	font2=al_load_ttf_font("images/SHREK.TTF",25,0);

	//CARICAMENTO BITMAP VITE
	vite_bmp = al_load_bitmap("images/vita.png");

	//CREAZIONE GESTORE PALLE
	/*GestorePalle GP;
	GP.setSW(SCREEN_W);
	GP.setSY(SCREEN_H);
	bitmap_ = GP.aggiungiPalla(SCREEN_W/2, 157, GRA) && GP.aggiungiPalla(0, 157, GRA);*/

	//CREAZIONE CODA EVENTI
  	event_queue = al_create_event_queue();

   	//FUNZIONI REGISTRAZIONE + DRAW
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_install_keyboard();
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	sfondo.Draw();
	GP.Draw();
	player->Draw(currFrame,keyLeft,keyRight,drawShoot,toLeft, caduto);
	al_flip_display();
	al_start_timer(timer);

	//IL GIOCO VERO E PROPRIO
   	while(!MatchOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(shoot==false)  {
			player->posizionaArma();
		}

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			if(drawShoot && !caduto)  {
				frameDelay=7;
				player->setFrames(2);
			}
			else if(caduto)  {		
				player->setFrames(11);
				frameDelay=7;
			}	
			else	
				frameDelay=5;

			if(++frameCount>=frameDelay)  {
				if(++currFrame>=player->getFrames())  {
					drawShoot=false;
					caduto=false;
					currFrame=0;
				}
				frameCount=0;
			}


			GP.Bouncer();

			bool hit = GP.hitByHook(player->getX_arma(), player->getY_arma(), player->getDim_arma(), bitmap_);  //rampino colpisce palla

			if(!bitmap_)  {
				cerr << "failed to initialize some palla.png";
				break;
			}

			if(hit && !presa)  {
				punteggio+=200;
				presa=true;
			}
			if(!hit)
				presa=false;

			if(keyRight && !caduto && !drawShoot)  {
				player->setFrames(6);
				drawShoot=false;
				toLeft=false;
				if(player->getX()+player->getDim_x()+5 <= SCREEN_W)
					player->setX(player->getX()+5);

				else
					player->setX(SCREEN_W-player->getDim_x());
			}
			if(keyLeft && !caduto && !drawShoot)  {
				player->setFrames(6);
				drawShoot=false;
				toLeft=true;
				if(player->getX()-5 >= 0)
					player->setX(player->getX()-5);
				else
					player->setX(0);
			}
			if(keySpace && !caduto)  {
				if(!shoot)
					drawShoot=true;
				shoot=true;
				keySpace=false;
			}

			bool p_hit = GP.playerHit(player->getX(), player->getY(), player->getDim_x());

			if(p_hit && !colpito && !caduto)  {
				//palla colpisce player
				MatchOver = true;
				caduto=true;
				colpito=true;
			}
			if(!p_hit)
				colpito=false;

			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
				break;
			if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE)
				keySpace=true;
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=true;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=true;
			if(ev.keyboard.keycode==ALLEGRO_KEY_F)  {
				if(!fullscreen)  {
					al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
					res_monitor_x = info.x2 - info.x1;
					res_monitor_y = info.y2 - info.y1;
					res_x = res_monitor_x / (float) SCREEN_W;
					res_y = res_monitor_y / (float) SCREEN_H;
				}
				else  {
					al_set_new_display_flags(ALLEGRO_WINDOWED);
					res_monitor_x = 640;
					res_monitor_y = 480;
					res_x = res_monitor_x / (float) SCREEN_W;
					res_y = res_monitor_y / (float) SCREEN_H;
				}		

				al_destroy_display(display);
				display = al_create_display(res_monitor_x,res_monitor_y);
				al_identity_transform(&redimencionamento);
				al_scale_transform(&redimencionamento,res_x,res_y);
				al_use_transform(&redimencionamento);
				fullscreen = !fullscreen;
			}
		}
		else if(ev.type==ALLEGRO_EVENT_KEY_UP)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=false;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			sfondo.Draw();
			if(shoot && player->getY_arma()>0 && !presa)  {
				player->setY_arma(player->getY_arma()-player->getDim_arma()/4);	//il /4 è per rallentarlo
			}
			else  {
				shoot=false;
			}

			if(vite>=1)
				al_draw_bitmap(vite_bmp, 580, 50, 0);
			if(vite>=2)
				al_draw_bitmap(vite_bmp, 540, 50, 0);
			if(vite>=3)
				al_draw_bitmap(vite_bmp, 500, 50, 0);
			if(vite<=0 || tempo<=0)
				MatchOver=true;

			//al_draw_text(font1,al_map_rgb(0,255,0),320,0,ALLEGRO_ALIGN_CENTRE,"Shrek Pang");
			al_draw_textf(font1,al_map_rgb(0,255,0),30,20,ALLEGRO_ALIGN_LEFT,"%d",tempo/60);
			al_draw_textf(font2,al_map_rgb(0,0,255),620,100,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);

			if((caduto || drawShoot) && currFrame>=player->getFrames())
				currFrame=0;

			player->Draw(currFrame,keyLeft,keyRight,drawShoot,toLeft, caduto);
			GP.Draw();
			tempo--;
			al_flip_display();
			redraw = false;
			if(GP.Empty())  {
				
				break;
			}
		}
	}

	//DISTRUGGO TUTTO
	GP.Clear();
	GP.aggiungiPalla(SCREEN_W/2, 157, GRA) && GP.aggiungiPalla(0, 157, GRA);

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_font(font1);
	al_destroy_font(font2);
	al_destroy_bitmap(vite_bmp);
	al_destroy_event_queue(event_queue);

	return !MatchOver;
}



#endif