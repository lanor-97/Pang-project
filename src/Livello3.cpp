#include "headers/Livello3.h"

Livello3::Livello3(Livello1* L1, const int FPS)  {
	sfondo = al_load_bitmap("../images/sfondo3.jpg");
	SCREEN_W = L1->getSW();
	SCREEN_H = L1->getSH();
	GP = new GestorePalle(SCREEN_W, SCREEN_H);
	GP2 = new GestorePalle(SCREEN_W, 340);
	player = L1->getPlayer();

	font1=al_load_ttf_font("../fonts/SHREK.TTF",30,0);
	font2=al_load_ttf_font("../fonts/SHREK.TTF",25,0);
	vite_bmp = al_load_bitmap("../images/vita.png");
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = L1->getDisplay();
	pausa_play = al_load_bitmap("../images/pausa1.png");
	pausa_exit = al_load_bitmap("../images/pausa2.png");

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//Livello 3 stuff
	piat = new Piattaforma(0, 156, true);
	scala1 = new Scala(300, 190, 1);
	scala2 = new Scala(300, 190, 1); //da rimuovere
	farquaad= new Farquaad(SCREEN_W,PLAYER_ALT_PIAT-5);

}

Livello3::~Livello3()  {
	if(GP2) delete GP2;
	if(piat) delete piat;
	if(scala1) delete scala1;
	if(scala2) delete scala2;
}

void Livello3::regolaPalle()  {
	GP->aggiungiPalla(SCREEN_W - 100, 250, MED, RED, true);
	GP2->aggiungiPalla(100, 100, PIC, RED, false);
}

CASO Livello3::Esegui(int vite, int& punteggio, float res_info[])  {
	//DICHIARAZIONE ALTRE VARIABILI 
	bool 	colpito=false, sfondo2=false, presa=false, redraw = true, 
			keyRight=false, keyLeft=false, keySpace=false, toLeft=false, 
			bitmap_ = true, fullscreen=false, trans=true, hit=false, hit2=false,
			climbing = false, keyUp= false, keyDown=false, keyUpDown=false,
			throwBall=false, farquaadArrive=true, farquaadEscape=false, GPturn=true;


	drawShoot=false; caduto=false; shoot=false; 
	MatchOver=false; drawExplosion=false; drawExplosion2=false;

	int 	tempo=9000, H_arma=0, ballTimer=400, escapeTimer=900;
	CASO 	return_value = EXIT;

	regolaPalle();
	al_flush_event_queue(event_queue);
	al_start_timer(timer);
	Transition(1);
	player->setY(PLAYER_ALT_NORM);

	//IL GIOCO VERO E PROPRIO

	while(!MatchOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			hit = false;
			hit2 = false;
			if(GPturn)
				GP->bouncerPiattaforma(piat);
			GP2->bouncerPiattaforma(piat);
			if(GPturn)  {
				GP->Bouncer();
				GPturn = false;
			}
			else  {
				GPturn = true;
			}
			GP2->Bouncer();

			if(shoot)  {
				hit = GP->hitByHook(player);
				hit2 = GP2->hitByHook(player);
			}
			else  {
				player->posizionaArma();
			}

			//RAMPINO HA COLPITO PALLA
			if((hit || hit2) && !presa)  {	
				punteggio+=200;
				presa=true;
				if(hit)
					drawExplosion = true;
				else if(hit2)
					drawExplosion2 = true;
			}
			else if(!hit)  {
				presa=false;
			}

			climbing = player->getY() != PLAYER_ALT_NORM && player->getY() != PLAYER_ALT_PIAT;

			//CONTROLLO MOVIMENTI DX/SX GIOCATORE
			if(keyRight && !caduto && !drawShoot && !climbing)  {
				player->setFrames(6);
				drawShoot=false;
				toLeft=false;
				if(player->getY() == PLAYER_ALT_NORM || player->getY() == PLAYER_ALT_PIAT)
					player->muoviSx(false, SCREEN_W);
			}
			if(keyLeft && !caduto && !drawShoot && !climbing)  {
				player->setFrames(6);
				drawShoot=false;
				toLeft=true;
				if(player->getY() == PLAYER_ALT_NORM || player->getY() == PLAYER_ALT_PIAT)
					player->muoviSx(true, 0);
			}
			if(keySpace && !caduto && !climbing)  {
				if(!shoot)
					drawShoot=true;
				shoot=true;
				keySpace=false;
			}
			if(keyUp && player->getY() > PLAYER_ALT_PIAT)  {
				climbing = true;
				if(scala1->playerHere(player))
					player->setX(scala1->getX());
				else if(scala2->playerHere(player))
					player->setX(scala2->getX());
				else
					climbing = false;
				if(climbing)
					player->muoviUp(true, PLAYER_ALT_PIAT);
			}
			else if(keyDown && player->getY() < PLAYER_ALT_NORM)  {
				climbing = true;
				if(scala1->playerHere(player))
					player->setX(scala1->getX());
				else if(scala2->playerHere(player))
					player->setX(scala2->getX());
				else
					climbing = false;
				if(climbing)
					player->muoviUp(false, PLAYER_ALT_NORM);
			}

			//IF PALLA COLPISCE GIOCATORE
			bool p_hit = GP->playerHit(player) || GP2->playerHit(player);

			if(p_hit && !colpito && !caduto)  {
				return_value = VITAPERSA;
				caduto=true;
				colpito=true;
			}
			
			if(!p_hit)
				colpito=false;

			bool hook_colp = false;
			if(player->getY() == PLAYER_ALT_NORM) 
				hook_colp = piat->hitByHook(player);
			if(shoot && player->getArmaY()>0 && !presa && !hook_colp)  {
				player->setArmaY(player->getArmaY() - 3);
				H_arma += 3;
			}
			else  {
				H_arma = 0;
				shoot=false;
			}
			
			if(!farquaadArrive)  {
				if(ballTimer==0 || (ballTimer==150 && (player->getX()>=farquaad->getX()-30 && 
				player->getY()==farquaad->getY()) && !caduto && escapeTimer!=0 && !farquaadEscape))  {
					if(farquaad->getY() > 200)  {
						GP->aggiungiPalla(farquaad->getX(), farquaad->getY()+30, PIC, RED, false);
					}
					else  {
						GP2->aggiungiPalla(farquaad->getX(), farquaad->getY()+30, PIC, RED, false);
					}
					throwBall=true;
					ballTimer=400;
				}

				if(escapeTimer==0){
					farquaadEscape=true;
					escapeTimer=900;
				}	

				ballTimer--;

				if(!farquaadEscape)
					escapeTimer--;
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

			if(ev.keyboard.keycode==ALLEGRO_KEY_UP)  {
				keyUp = true;
				keyUpDown=true;
			}	
			else if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN)  {
				keyDown = true;
				keyUpDown=true;
			}	
			if(ev.keyboard.keycode==ALLEGRO_KEY_F)
				toggleFullscreen(fullscreen, res_info);
		}
		else if(ev.type==ALLEGRO_EVENT_KEY_UP)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=false;

			if(ev.keyboard.keycode==ALLEGRO_KEY_UP)  {
				keyUp = false;
				keyUpDown=false;
			}	
			else if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN)  {
				keyDown = false;
				keyUpDown= false;
			}	
		}
		if(redraw && al_is_event_queue_empty(event_queue)) {
			player->setDraw(keyLeft,keyRight,drawShoot,toLeft, caduto,climbing, keyUpDown);
			Draw(vite, tempo, punteggio, H_arma);

			if(tempo/60<=145)  {
				if(farquaad->getX()<=580)  {
					farquaadArrive=false;
				}
				if(!farquaad->Draw(farquaadEscape,throwBall,farquaadArrive))  {
					throwBall=false;
				}
				if(farquaadEscape && farquaad->getX()==640)  {
					farquaadEscape=false;
					farquaadArrive=true;
					if(farquaad->getY()==PLAYER_ALT_NORM-5)
						farquaad->setY(PLAYER_ALT_PIAT-5);
					else
						farquaad->setY(PLAYER_ALT_NORM-5);
				}	
			}	
			al_flip_display();
			tempo--;
			redraw = false;

			//CONTROLLO VITTORIA
			if(GP->Empty() && GP2->Empty())  {
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
	GP2->Clear();

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

	al_draw_textf(font1,al_map_rgb(255,255,0),SCREEN_W/4.7,SCREEN_H/1.16,ALLEGRO_ALIGN_RIGHT,"%d",tempo/60);
	al_draw_textf(font2,al_map_rgb(0,0,255),SCREEN_W/1.06,SCREEN_H/1.14,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);

	if(shoot)
		player->ArmaDraw(H_arma);
	
	piat->Draw();
	scala1->Draw();
	scala2->Draw();
	if(!player->Draw())  {
		if(caduto)  {
			caduto=false;
			MatchOver=true;
		}	
		drawShoot=false;
	}
		
	if(!GP->Draw(drawExplosion))
		drawExplosion=false;
	
	if(!GP2->Draw(drawExplosion2))
		drawExplosion2 = false;
}