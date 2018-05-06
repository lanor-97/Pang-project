#ifndef LIVELLO3_H
#define LIVELLO3_H

#include "Livello2.h"

class Livello3: public Livello1  {
public:
	Livello3()  { Livello1(); }
	Livello3(float, float, Giocatore*, ALLEGRO_DISPLAY*, const int);
	Livello3(Livello1*, const int);
	virtual ~Livello3();
	virtual void regolaPalle();
	virtual CASO Esegui(int, float[]);
	virtual void Draw(int, int, int, int);

protected:
	Scala* scala1 = NULL;
	Scala* scala2 = NULL;
	Piattaforma* piat = NULL;
	const int PLAYER_ALT_PIAT = 105;
	const int PLAYER_ALT_NORM = 285;
};

Livello3::Livello3(Livello1* L1, const int FPS)  {
	sfondo = al_load_bitmap("images/sfondo3.jpg");
	SCREEN_W = L1->getSW();
	SCREEN_H = L1->getSH();
	GP = new GestorePalle(SCREEN_W, SCREEN_H);
	player = L1->getPlayer();

	font1=al_load_ttf_font("fonts/SHREK.TTF",30,0);
	font2=al_load_ttf_font("fonts/SHREK.TTF",25,0);
	vite_bmp = al_load_bitmap("images/vita.png");
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = L1->getDisplay();
	pausa_play = al_load_bitmap("images/pausa1.png");
	pausa_exit = al_load_bitmap("images/pausa2.png");

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//Livello 3 stuff
	piat = new Piattaforma(0, 156, true);
	scala1 = new Scala(140, 190, 1);
	scala2 = new Scala(500, 190, 1);
}

Livello3::~Livello3()  {
	if(piat) delete piat;
	if(scala1) delete scala1;
	if(scala2) delete scala2;
}

void Livello3::regolaPalle()  {
	GP->aggiungiPalla(SCREEN_W - 100, 157, MED, RED, true);
	GP->aggiungiPalla(100, 157, PIC, RED, false);
}

CASO Livello3::Esegui(int vite, float res_info[])  {
	//DICHIARAZIONE ALTRE VARIABILI 
	bool 	colpito=false, sfondo2=false, presa=false, redraw = true, 
			keyRight=false, keyLeft=false, keySpace=false, toLeft=false, 
			bitmap_ = true, fullscreen=false, trans=true, hit=false;

	drawShoot=false; caduto=false; shoot=false; 
	MatchOver=false; drawExplosion=false;

	int 	punteggio=0, tempo=9000, H_arma=0;
	CASO 	return_value = EXIT;

	regolaPalle();
	al_flush_event_queue(event_queue);
	al_start_timer(timer);
	Transition(1);
	player->setY(PLAYER_ALT_PIAT);

	//IL GIOCO VERO E PROPRIO

	while(!MatchOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			hit = false;
			GP->bouncerPiattaforma(piat);
			GP->Bouncer();

			if(shoot)
				hit = GP->hitByHook(player);
			else
				player->posizionaArma();

			//RAMPINO HA COLPITO PALLA
			if(hit && !presa)  {	
				punteggio+=200;
				presa=true;
				drawExplosion=true;
			}

			if(!hit)
				presa=false;

			//CONTROLLO MOVIMENTI DX/SX GIOCATORE
			if(keyRight && !caduto && !drawShoot)  {
				player->setFrames(6);
				drawShoot=false;
				toLeft=false;
				player->muoviSx(false, SCREEN_W);
			}
			if(keyLeft && !caduto && !drawShoot)  {
				player->setFrames(6);
				drawShoot=false;
				toLeft=true;
				player->muoviSx(true, 0);
			}
			if(keySpace && !caduto)  {
				if(!shoot)
					drawShoot=true;
				shoot=true;
				keySpace=false;
			}

			//IF PALLA COLPISCE GIOCATORE
			bool p_hit = GP->playerHit(player);

			if(p_hit && !colpito && !caduto)  {
				return_value = VITAPERSA;
				caduto=true;
				colpito=true;
			}
			if(!p_hit)
				colpito=false;

			bool hook_colp = false;
			if(player->getY() == PLAYER_ALT_NORM) piat->hitByHook(player);
			if(shoot && player->getArmaY()>0 && !presa && !hook_colp)  {
				player->setArmaY(player->getArmaY() - 6);
				H_arma += 6;
			}
			else  {
				H_arma = 0;
				shoot=false;
			}

			redraw = true;
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return_value = EXIT;
			break;
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				al_stop_timer(timer);
				keyLeft = false;
				keyRight = false;
				if(!Pausa(fullscreen, res_info))  {	
					return_value = MENU;
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
			if(ev.keyboard.keycode==ALLEGRO_KEY_F)
				toggleFullscreen(fullscreen, res_info);
		}
		else if(ev.type==ALLEGRO_EVENT_KEY_UP)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=false;
		}
		if(redraw && al_is_event_queue_empty(event_queue)) {
			player->setDraw(keyLeft,keyRight,drawShoot,toLeft, caduto,false, false);
			Draw(vite, tempo, punteggio, H_arma);
			tempo--;

			redraw = false;

			//CONTROLLO VITTORIA
			if(GP->Empty())  {
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
				return_value = LIVELLOSUP;
				break;
			}
		
		}					
	}
	
	//DISTRUGGO TUTTO
	player->setX(SCREEN_W/2 - player->getDimX());
   	player->setY(SCREEN_H/1.37 - player->getDimY());
	GP->Clear();

	return return_value;
}

void Livello3::Draw(int vite, int tempo, int punteggio, int H_arma)  {
	al_draw_bitmap(sfondo,0,0,0);

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
		player->ArmaDraw(H_arma);
	
	piat->Draw();

	if(!player->Draw())  {
		if(caduto)  {
			caduto=false;
			MatchOver=true;
		}	
		drawShoot=false;
	}
	scala1->Draw();
	scala2->Draw();
		
	if(!GP->Draw(drawExplosion))
		drawExplosion=false;

	al_flip_display();
}



#endif