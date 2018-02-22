#ifndef LIVELLO1_H
#define LIVELLO1_H
#include "Animation.h"
#include "GestorePalle.h"
#include "Giocatore.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class Livello1  {
public:
	Livello1(float, float, Giocatore*);
	~Livello1()  { al_destroy_bitmap(sfondo); }
	bool Esegui(ALLEGRO_DISPLAY*, int, float[]);
protected:
	ALLEGRO_BITMAP* sfondo=NULL;
	Giocatore* player;
	GestorePalle GP;
	float SCREEN_W, SCREEN_H;
};


Livello1::Livello1(float SW, float SH, Giocatore* p): player(p), SCREEN_W(SW), SCREEN_H(SH)  {
	sfondo = al_load_bitmap("images/sfondo1.jpg");
	GP.setSW(SCREEN_W);
	GP.setSY(SCREEN_H);

	GP.aggiungiPalla(SCREEN_W/2, 157, GRA) && GP.aggiungiPalla(0, 157, GRA);
}

bool Livello1::Esegui(ALLEGRO_DISPLAY* display, int vite, float res_info[])  {
	//DICHIARAZIONE VARIABILI ALLEGRO
	ALLEGRO_FONT*			font1=NULL;
	ALLEGRO_FONT*			font2=NULL;
	ALLEGRO_BITMAP*			vite_bmp=NULL;
	ALLEGRO_TRANSFORM 		redimencionamento;
	ALLEGRO_EVENT_QUEUE* 	event_queue=NULL;
	ALLEGRO_TIMER*			timer=NULL;

	//DICHIARAZIONE ALTRE VARIABILI 
	bool 	drawShoot=false, caduto=false, shoot=false, colpito=false, sfondo2=false, 
			presa=false, redraw = true, keyRight=false, keyLeft=false, keySpace=false, 
			toLeft=false, MatchOver=false, bitmap_ = true, fullscreen=false,
			drawExplosion=false;

	int 	punteggio=0, tempo=9000, currFrame=0, 
			frameCount=0, frameDelay=5;


	//CARICAMENTO FONT
	font1=al_load_ttf_font("images/SHREK.TTF",30,0);
	font2=al_load_ttf_font("images/SHREK.TTF",25,0);

	//CARICAMENTO BITMAP VITE
	vite_bmp = al_load_bitmap("images/vita.png");
	timer = al_create_timer(1.0 / 60);
	event_queue = al_create_event_queue();
   	//FUNZIONI DRAW
   	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_draw_bitmap(sfondo,0,0,0);
	GP.Draw(drawExplosion);
	player->Draw(keyLeft,keyRight,drawShoot,toLeft, caduto);
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

			GP.Bouncer();

			bool hit = GP.hitByHook(player->getX_arma(), player->getY_arma(), player->getDim_arma(), bitmap_);  //rampino colpisce palla

			if(!bitmap_)  {
				cerr << "failed to initialize some palla.png";
				break;
			}

			if(hit && !presa)  {
				punteggio+=200;
				presa=true;
				drawExplosion=true;
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
			}
		}
		else if(ev.type==ALLEGRO_EVENT_KEY_UP)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=false;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			al_draw_bitmap(sfondo,0,0,0);
			if(shoot && player->getY_arma()>0 && !presa)  {
				player->setY_arma(player->getY_arma()-player->getDim_arma()/4);	//il /4 è per rallentarlo
			}
			else  {
				shoot=false;
			}

			if(vite>=1)
				al_draw_bitmap(vite_bmp, SCREEN_W/25, SCREEN_H/11, 0);
			if(vite>=2)
				al_draw_bitmap(vite_bmp, SCREEN_W/11, SCREEN_H/11, 0);
			if(vite>=3)
				al_draw_bitmap(vite_bmp, SCREEN_W/7, SCREEN_H/11, 0);
			if(vite<=0 || tempo<=0)
				MatchOver=true;

			//al_draw_text(font1,al_map_rgb(0,255,0),320,0,ALLEGRO_ALIGN_CENTRE,"Shrek Pang");
			al_draw_textf(font1,al_map_rgb(255,255,0),SCREEN_W/4.7,SCREEN_H/1.16,ALLEGRO_ALIGN_RIGHT,"%d",tempo/60);
			al_draw_textf(font2,al_map_rgb(0,0,255),SCREEN_W/1.06,SCREEN_H/1.14,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);

			

			if(!player->Draw(keyLeft,keyRight,drawShoot,toLeft, caduto))
				{
					caduto=false;
					drawShoot=false;
				}	
			
			if(!GP.Draw(drawExplosion))
			drawExplosion=false;

			tempo--;
			al_flip_display();
			redraw = false;
			if(GP.Empty())  {
				
				break;
			}
		}
	}

	//DISTRUGGO TUTTO
	player->setX(SCREEN_W/2 - player->getDim_x());
   	player->setY(SCREEN_H/1.37 - player->getDim_y());
	GP.Clear();
	GP.aggiungiPalla(SCREEN_W/2, 157, GRA) && GP.aggiungiPalla(0, 157, GRA);

	al_destroy_font(font1);
	al_destroy_font(font2);
	al_destroy_bitmap(vite_bmp);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return !MatchOver;
}



#endif