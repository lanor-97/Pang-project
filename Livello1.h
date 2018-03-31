#ifndef LIVELLO1_H
#define LIVELLO1_H

#include "Animation.h"
#include "GestorePalle.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Transizione.h"
#include "Blocco.h"

enum CASO  { EXIT = 0, LIVELLOSUP, VITAPERSA, MENU };

class Livello1  {
public:
	Livello1();
	Livello1(float, float, Giocatore*, ALLEGRO_DISPLAY*, const int);
	virtual ~Livello1();
	virtual CASO Esegui(int, float[]);
	void Transition(int);
	bool Pausa(bool&, float[]);
	virtual void regolaPalle();
	virtual void Draw(int, int, int, int);
	void  toggleFullscreen(bool&, float[]);

	//funzioni get
	float getSW() const  { return SCREEN_W; }
	float getSH() const  { return SCREEN_H; }
	Giocatore* getPlayer() const  { return player; }
	ALLEGRO_DISPLAY* getDisplay() const  { return display; }
protected:
	ALLEGRO_BITMAP* 		sfondo=NULL;
	ALLEGRO_EVENT_QUEUE* 	event_queue=NULL;
	ALLEGRO_TIMER*			timer=NULL;
	ALLEGRO_FONT*			font1=NULL;
	ALLEGRO_FONT*			font2=NULL;
	ALLEGRO_BITMAP*			vite_bmp=NULL;
	ALLEGRO_DISPLAY* 		display=NULL;
	ALLEGRO_BITMAP*			pausa_play=NULL;
	ALLEGRO_BITMAP*			pausa_exit=NULL;
	ALLEGRO_TRANSFORM 		redimencionamento;
	Giocatore* player = NULL;
	GestorePalle* GP = NULL;
	Transizione transizione;
	float SCREEN_W, SCREEN_H;
	bool shoot, caduto, drawShoot, drawExplosion, MatchOver;
};

Livello1::Livello1()  {
	SCREEN_W = 0; 
	SCREEN_H = 0;
}
Livello1::Livello1(float SW, float SH, Giocatore* p, ALLEGRO_DISPLAY* display1, const int FPS): player(p), SCREEN_W(SW), SCREEN_H(SH)  {
	sfondo = al_load_bitmap("images/sfondo1.jpg");
	GP = new GestorePalle(SW, SH);

	font1=al_load_ttf_font("fonts/SHREK.TTF",30,0);
	font2=al_load_ttf_font("fonts/SHREK.TTF",25,0);
	vite_bmp = al_load_bitmap("images/vita.png");
	pausa_play = al_load_bitmap("images/pausa1.png");
	pausa_exit = al_load_bitmap("images/pausa2.png");

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = display1;


	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

void Livello1::regolaPalle()  {
	GP->aggiungiPalla(SCREEN_W/2, 157, GRA, GREEN, true);
	GP->aggiungiPalla(50, 157, GRA, GREEN, false);
}

Livello1::~Livello1()  {
	if(sfondo)  {
		cerr << "\ndistruggo sfondo_bitmap Liv";
		al_destroy_bitmap(sfondo);
	}
	if(GP)  {
		cerr << "\ndistruggo GestorePalle Liv";
		delete GP;
	}
	if(font1)  {
		cerr << "\ndistruggo font1 Liv";
		al_destroy_font(font1);
	}
	if(font2)  {
		cerr << "\ndistruggo font2 Liv";
		al_destroy_font(font2);
	}
	if(vite_bmp)  {
		cerr << "\ndistruggo vite_bitmap Liv";
		al_destroy_bitmap(vite_bmp);
	}
	if(timer)  {
		cerr << "\ndistruggo timer Liv";
		al_destroy_timer(timer);
	}
	if(event_queue)  {
		cerr << "\ndistruggo event_queue Liv";
		al_destroy_event_queue(event_queue);
	}
	if(pausa_play)  {
		cerr << "\ndistruggo pausa_play_bitmap";
		al_destroy_bitmap(pausa_play);
	}
	if(pausa_exit)  {
		cerr << "\ndistruggo pausa_exit_bitmap";
		al_destroy_bitmap(pausa_exit);
	}
}

bool Livello1::Pausa(bool& fullscreen, float res_info[])  {
	
	bool play = true, pausa=true, inGame=true;
	al_flush_event_queue(event_queue);
	
	while(pausa)  {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				pausa = false;
				break;
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER || ev.keyboard.keycode==ALLEGRO_KEY_SPACE)  {
				if(play)  {
					pausa=false;
					break;
				}
				else  {
					pausa=false;
					inGame=false;
				}	
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN && play)
				play = false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_UP && !play) 
				play = true;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_F)
				toggleFullscreen(fullscreen, res_info);
		}

		al_draw_bitmap(sfondo,0,0,0);
		player->Draw();
		GP->Draw(false);
		if(!play)
			al_draw_bitmap(pausa_exit,0,0,0);
		else
			al_draw_bitmap(pausa_play,0,0,0);

		al_flip_display();
	}
	
	al_flush_event_queue(event_queue);
	return inGame;
}

CASO Livello1::Esegui(int vite, float res_info[])  {
	//DICHIARAZIONE ALTRE VARIABILI 
	bool 	colpito=false, sfondo2=false, presa=false, redraw = true, 
			keyRight=false, keyLeft=false, keySpace=false, toLeft=false, 
			bitmap_ = true, fullscreen=false, trans=true, hit=false,
			next[4] = {false};

	drawShoot=false; caduto=false; shoot=false; 
	MatchOver=false; drawExplosion=false;

	int 	punteggio=0, tempo=9000, H_arma=0;
	CASO 	return_value = EXIT;

	regolaPalle();
	al_flush_event_queue(event_queue);
	al_start_timer(timer);
	Transition(1);

	//IL GIOCO VERO E PROPRIO

	while(!MatchOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			hit = false;
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

			if(shoot && player->getY_arma()>0 && !presa)  {
				player->setY_arma(player->getY_arma() - 6);
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
			if(ev.keyboard.keycode == ALLEGRO_KEY_N)
				next[0] = true;
			if(ev.keyboard.keycode == ALLEGRO_KEY_E)  {
				if(next[0])
					next[1] = true;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_X)  {
				if(next[0] && next[1])
					next[2] = true;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_T)  {
				if(next[0] && next[1] && next[2])
					next[3] = true;
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
		if(next[3] && next[2] && next[1] && next[0])  {
			return_value = LIVELLOSUP;
			break;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			player->setDraw(keyLeft,keyRight,drawShoot,toLeft, caduto,false);
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
	player->setX(SCREEN_W/2 - player->getDim_x());
   	player->setY(SCREEN_H/1.37 - player->getDim_y());
	GP->Clear();

	return return_value;
}


void Livello1::Transition(int x)
{
	bool trans=true;
	double speed = al_get_timer_speed(timer);

	al_flush_event_queue(event_queue);
	transizione.setTipo(x);
	player->setDraw(false,false,false,false, false,false);
	al_set_timer_speed(timer, 1.0 / 10);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	while(trans)  {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			if(x==1)
			{
				al_draw_bitmap(sfondo,0,0,0);
				GP->Draw(false);
				player->Draw();
			}
			if(x==2 || x==3)
			{
				player->DrawVictory();
			}	
			if(!transizione.Draw())  {
				trans = false;
				al_set_timer_speed(timer, speed);
			}
							
			al_flip_display();
		}
	}
}

void Livello1::Draw(int vite, int tempo, int punteggio, int H_arma)  {
	al_draw_bitmap(sfondo,0,0,0);

	if(vite>=1)
		al_draw_bitmap(vite_bmp, SCREEN_W/25, SCREEN_H/11, 0);
	if(vite>=2)
		al_draw_bitmap(vite_bmp, SCREEN_W/11, SCREEN_H/11, 0);
	if(vite>=3)
		al_draw_bitmap(vite_bmp, SCREEN_W/7, SCREEN_H/11, 0);
	if(vite<=0 || tempo<=0)
		caduto=true;

	al_draw_text(font1,al_map_rgb(0,255,0),320,0,ALLEGRO_ALIGN_CENTRE,"Shrek Pang");
	al_draw_textf(font1,al_map_rgb(255,255,0),SCREEN_W/4.7,SCREEN_H/1.16,ALLEGRO_ALIGN_RIGHT,"%d",tempo/60);
	al_draw_textf(font2,al_map_rgb(0,0,255),SCREEN_W/1.06,SCREEN_H/1.14,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);

	if(shoot)
		player->Draw_arma(H_arma);

	if(!player->Draw())  {
		if(caduto)  {
			caduto=false;
			MatchOver=true;
		}	
		drawShoot=false;
	}
		
	if(!GP->Draw(drawExplosion))
		drawExplosion=false;

	al_flip_display();
}

void Livello1::toggleFullscreen(bool &fullscreen, float res_info[])  {
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


#endif