#ifndef LIVELLO2_H
#define LIVELLO2_H

#include "Livello1.h"

class Livello2: public Livello1  {
public:
	Livello2()  { Livello1(); }
	Livello2(float, float, Giocatore*, ALLEGRO_DISPLAY*, const int);
	Livello2(Livello1*, const int);
	~Livello2();
	void regolaPalle();
	int Esegui(int, float[]);

protected:

};


Livello2::Livello2(float SW, float SH, Giocatore* p, ALLEGRO_DISPLAY* d1, const int FPS)  {
	Livello1(SW, SH, p, d1, FPS);
}

Livello2::Livello2(Livello1* L1, const int FPS)  {
	sfondo = al_load_bitmap("images/sfondo2.jpg");

	player = L1->getPlayer();
	SCREEN_W = L1->getSW();
	SCREEN_H = L1->getSH();

	GP.setSW(SCREEN_W);
	GP.setSY(SCREEN_H);

	font1=al_load_ttf_font("images/SHREK.TTF",30,0);
	font2=al_load_ttf_font("images/SHREK.TTF",25,0);
	vite_bmp = al_load_bitmap("images/vita.png");

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = L1->getDisplay();


	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Livello2::~Livello2()  {
	al_destroy_bitmap(sfondo); 
	al_destroy_font(font1);
	al_destroy_font(font2);
	al_destroy_bitmap(vite_bmp);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
}

void Livello2::regolaPalle()  {
	GP.aggiungiPalla(SCREEN_W/2, 157, GRA);
	GP.aggiungiPalla(0, 157, GRA);
}

int Livello2::Esegui(int vite, float res_info[])  {
	//DICHIARAZIONE VARIABILI ALLEGRO
	ALLEGRO_TRANSFORM 		redimencionamento;

	//DICHIARAZIONE ALTRE VARIABILI 
	bool 	drawShoot=false, caduto=false, shoot=false, colpito=false, sfondo2=false, 
			presa=false, redraw = true, keyRight=false, keyLeft=false, keySpace=false, 
			toLeft=false, MatchOver=false, bitmap_ = true, fullscreen=false,
			drawExplosion=false, trans=true;

	int 	punteggio=0, tempo=9000, H_arma=0, return_value;

	regolaPalle();
	al_flush_event_queue(event_queue);
	al_start_timer(timer);
	Transition(1);

	//IL GIOCO VERO E PROPRIO

	while(!MatchOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			bool hit = false;
			GP.Bouncer();
			if(shoot)
				hit = GP.hitByHook(player->getX_arma(), player->getY_arma(), player->getDim_arma(), bitmap_);

			if(shoot==false)
				player->posizionaArma();

			if(hit && !presa)  {	//rampino colpisce palla
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
				return_value = 0;
				caduto=true;
				colpito=true;
			}
			if(!p_hit)
				colpito=false;

			redraw = true;
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return_value = -1;
			break;
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				al_stop_timer(timer);
				keyLeft = false;
				keyRight = false;
				if(!Pausa(res_info))  {	
					return_value = 2;
					break;
				}
				al_start_timer(timer);
			}	
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
				player->setY_arma(player->getY_arma() - 6);
				H_arma += 6;
			}
			else  {
				H_arma = 0;
				shoot=false;
			}

			if(vite>=1)
				al_draw_bitmap(vite_bmp, SCREEN_W/25, SCREEN_H/11, 0);
			if(vite>=2)
				al_draw_bitmap(vite_bmp, SCREEN_W/11, SCREEN_H/11, 0);
			if(vite>=3)
				al_draw_bitmap(vite_bmp, SCREEN_W/7, SCREEN_H/11, 0);
			if(vite<=0 || tempo<=0)
				caduto=true;

			//al_draw_text(font1,al_map_rgb(0,255,0),320,0,ALLEGRO_ALIGN_CENTRE,"Shrek Pang");
			al_draw_textf(font1,al_map_rgb(255,255,0),SCREEN_W/4.7,SCREEN_H/1.16,ALLEGRO_ALIGN_RIGHT,"%d",tempo/60);
			al_draw_textf(font2,al_map_rgb(0,0,255),SCREEN_W/1.06,SCREEN_H/1.14,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);

			if(shoot)
				player->Draw_arma(H_arma);

			player->setDraw(keyLeft,keyRight,drawShoot,toLeft, caduto,false);
			if(!player->Draw())  {
				if(caduto)  {
					caduto=false;
					MatchOver=true;
				}	
				drawShoot=false;
			}
			
			if(!GP.Draw(drawExplosion))
				drawExplosion=false;

			tempo--;
			al_flip_display();
			redraw = false;
			if(GP.Empty())  {
				Transition(2);
				al_flush_event_queue(event_queue);
				while(true)  {
					al_wait_for_event(event_queue, &ev);
					if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
						Transition(3);
						al_rest(2);
						break;
					}
				}
				return_value = 1;
				break;
			}
		
		}					
	}
	
	//DISTRUGGO TUTTO
	player->setX(SCREEN_W/2 - player->getDim_x());
   	player->setY(SCREEN_H/1.37 - player->getDim_y());
	GP.Clear();

	return return_value;
}


#endif